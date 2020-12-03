/*
  _______________________________________________________________
 /                                                               \
||  Course: CSCI-330      Assignment #: 8    Semester: Fall2020  ||
||                                                               ||
||  Name: Carlos Sanchez     Z-ID: z172955                       ||
||                                                               ||
||  TA's Name: Gude Venkata Sai Haswanth                         ||
||                                                               ||
||  Due: Friday, 11/20/20 by 11:59PM                             ||
 \_______________________________________________________________/
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

void sendFile(char*, int);
void chomp(char*);
bool inExist(const char*);
bool isFile(const char*);

int main(int argc, char **argv)
{

   //Making sure all arguments are here before starting
   if (argc != 3)
   {
      cerr << "Invalid command!\nUsage: portnumber directory\n";
      cerr << "Exiting..";
      exit(1);
   }


   DIR * gdir;
   int succh;
   int newsockfd;
   char buffer[256];
   socklen_t serverlen = sizeof(sockaddr_in);
   socklen_t clientlen = sizeof(sockaddr_in);
   ssize_t received;
   char * comansp[2];
   char * webDir = argv[2];


   //Creating a new socket, then checking to see if socket fails
   int sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
   {
      cerr << "Failed to create socket\n";
      cerr << "Exiting..";
      exit(1);
   }

   struct sockaddr_in server;
   struct sockaddr_in client;

   //Setting values for the server as default
   memset(&server, 0, sizeof(server));
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = htons(atoi(argv[1]));

   serverlen = sizeof(server);

   //Proceeding to bind soicket, checking to see if it fails
   succh = bind(sockfd, (struct sockaddr*) &server, serverlen);
   if (succh < 0)
   {
      cerr << "Could not bind\n";
      cerr << "Exiting..";
      exit(1);
   }

   //Proceeding to listen to socket, then checking to see if it fails
   succh = listen(sockfd, 128);
   if (succh < 0)
   {
      cerr << "Could not listen\n";
      cerr << "Exiting..";
      exit(1);
   }
   
   
   clientlen = sizeof(client);
   
   //Proceeding until it breaks
   while (true)
   {
      //Accepting new connections
      newsockfd = accept(sockfd, (struct sockaddr*) &client, &clientlen);
      
      //check to see if the connection failed
      if (newsockfd < 0)
      {
          cerr << "Could not accept\n";
	  cerr << "Exiting..";
	  exit(1);
      }
      
      
      //Splitting connections, then allowing parent to accept new request
      //Child will handle the request
      if (fork()) //Parent
      {
      
         close(newsockfd);
	 
      }
       else //Child
      {
         //Read what is being read, then check to see if read fails
	 received = read(newsockfd, buffer, 256);
         if (received < 0)
         {
            cerr << "Could not get message\n";
	    cerr << "Exiting..";
	    exit(1);
         }
	 
	 cout << buffer;
         //check to see if GET was recived as a command
         comansp[0] = strtok(buffer, " ");
         if (strcmp(comansp[0], "GET") == 0)
         {
            comansp[1] = strtok(NULL, " \n");
	    
	    //check to see if msg began with a '/'
	    if (comansp[1][0] != '/')
	    {
	       char errorMsg[] = "GET Request must begin with a '/'!\n";
	       write(newsockfd, errorMsg, strlen(errorMsg));
	       exit(1);
	    }
	    
	    //check to see if msg contained '..'
	    if (strstr(comansp[1], "..") != NULL)
	    {
	       char errorMsg[] = "GET Request cannot contain \"..\"\n";
	       write(newsockfd, errorMsg, strlen(errorMsg));
	       exit (1);
	    }
	    
	    
	    chomp(comansp[1]);
	    strcat(webDir, comansp[1]);
	    
	    //check if the last character in the path is a '/'
	    if (webDir[strlen(webDir)-1] != '/')
	    {
	       //double check to see if the path is a file
	       if (isFile(webDir))
	       {
	          sendFile(webDir, newsockfd);
	          close(newsockfd);
	          exit(1);
	       }
	    }
	    else //path refers to a directory
	    {
	       char indexPath[128];
	       char indexName[] = "index.html";
	       strcpy(indexPath, webDir);
	       strcat(indexPath, indexName);
	       chomp(indexPath);
	       
	       //check to see if the directory contains 'index.html'
	       if (inExist(indexPath))
	       {
	          sendFile(indexPath, newsockfd);
		  sleep(10);
	          close(newsockfd);
	          exit(1);
	       }
	    }
	    
	    //attempt to open requested directory
	    gdir = opendir((const char*) webDir);
	    if (gdir == NULL)
	    {
	       char errorMsg[] = "File or directory does not exist\n";
	       write(newsockfd, errorMsg, strlen(errorMsg));
	       exit(1);
	    } 
	    
            struct dirent* thedir;
	    
	    //redirect everything that would be outputted on to cout
	    //and output it to the client
            if (dup2(newsockfd, 1) < 0)
	    {
	       cerr << "Socket dup2 has failed\n";
	       cerr << "Exiting..";
	       exit(1);
	    }
	    
	    //read the contents of a directory and print the name
	    //of each file/directory
	    while ((thedir = readdir(gdir)) != NULL)
	    {
	       if (thedir->d_name[0] != '.')
	       {
	          cout << thedir->d_name << endl;
	       }
	    }
	 
	 }
	 else //request didn't start with 'GET'
	 {
	    char errorMsg[] = "Any request must start with 'GET'!\n";
	    write(newsockfd, errorMsg, strlen(errorMsg));
	 }
	 
         close(newsockfd);
	 exit(1);
      }
      
      //Null out the buffer
      memset(buffer, 0, sizeof(buffer));
   }
   
   
  close(sockfd);
   return 0;
}

//sendFile Function
//Sends contents of requested file to a set
//file descriptor
void sendFile(char* pName, int fdSock)
{
   int openFd;
   char buffer[256];
   ssize_t bytesr;
   char errmsg[] = "File does not exist\n";

   openFd = open(pName, O_RDWR);

   if (openFd < 0)
   {
      write(fdSock, errmsg, strlen(errmsg));
      exit(1);
   }

   bytesr = read(openFd, (char*) buffer, 256);
   write(fdSock, buffer, (size_t) bytesr);
   while ((int) bytesr >= 256)
   {
      bytesr = read(openFd, (char*) buffer, 256);
      write(fdSock, buffer, (size_t) bytesr);
   }
}

//Exists Function
//Checks to see if file exists
bool inExist(const char* name)
{
   struct stat buffer;
   return (stat(name, &buffer) == 0);
}

//isFile Function
//Checks to see if the requested name is
//an actual file or directory
bool isFile(const char* name)
{
   bool rv = false;
   struct stat buffer;
   stat(name, &buffer);
   if ((buffer.st_mode & S_IFMT) == S_IFREG)
      rv = true;

   return rv;
}

//Chomp Function
//Will remove leading returns and newlines
//will then replace with null characters
void chomp(char *s) {
for (char *p = s + strlen(s)-1; *p == '\r' || *p == '\n'; p--)
   *p = '\0';
}
