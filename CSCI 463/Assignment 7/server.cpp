////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assignment #7	Semester: Spring 2021
//
//	Due: Friday, April 23rd, 2021
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <signal.h>

using namespace std;

/**
* @brief		This function will give the user a heads up on what the program
*				requires in order to properly function and work before exiting
*
*******************************************************************************/
static void usage()
{
    cerr << " Usage: server [-l listener-port] " << endl;
    cerr << " -l, The port number to which the server must listen. Default: 0 " << endl;
	assert(" Missing ip-number/port");
}

/**
* @brief			This function will write to the server
*
* @param fd			sock from main
* @param buf		character array buf, contains data from file
* @param buf_len	length of the buf array
*
* @return			Returns length of the character array buf
*******************************************************************************/
static int safe_write(int fd,const char *buf, ssize_t len){
	while (len > 0)
    {
        ssize_t wlen = write(fileno(stdout), buf, len);

        if(wlen == -1) 
		{
			return -1;
		} 

        len = len - wlen;
        buf = buf + wlen;
    }
    return len;
}

/**
* @brief	    	This function will get the size of the file by getting the size 
*                   of the character array buf, which the file contents has been 
*                   imported into
*
* @param buf		character array that contains contents of file
*
* @return		    Returns sum of character array buf, which is just the size
*******************************************************************************/
static int getFileSize(char *buf){
	int sum = 0;

	for (int i = 0; buf[i] != '\0'; i++) 
	{
        sum += sizeof(buf[i]);
    }

    return sum;
}

/**
* @brief			This is the main function, and it reads from standard input
*					to see if there is a specific port to use. Then proceeds to read
*					from file and write to the server
*
* @param argc		argument count. checks amount of arguments passed
* @param argv		argument vector. array of character pointers that lists arguments
*
* @return			Returns 0 when successfully opens socket and writes to server
*******************************************************************************/
int main(int argc,char **argv)
{
	int sock;
	socklen_t from_len;
	struct sockaddr_in from;
	int msgsock;
	char buf[2048];
	int rval;
	int sockNum = 0;

	signal(SIGPIPE, SIG_IGN);
	int opt;
	while ((opt = getopt(argc, argv, "l:")) != -1) 
    {
		switch (opt) 
		{
			case 'l':
			{
				sockNum = atoi(argv[2]);
				break;
			}

			default:
				usage();
				break;
		}
    }
    
	cout << "Socket has port #" << sockNum << endl;
	sock = socket(AF_INET, SOCK_STREAM,0);
	if (sock < 0)
	{
		perror("opening stream socket");
		exit(1);
	}

	from.sin_family = AF_INET;
	from.sin_addr.s_addr = INADDR_ANY;
	from.sin_port = htons(sockNum);

	if(bind(sock, (sockaddr*)&from, sizeof(from)))
	{
		perror("binding stream socket:");
		exit(1);
	}

	listen(sock, 5);
	do
	{
		from_len = sizeof(from);
		msgsock = accept(sock, (struct sockaddr*)&from,&from_len);

    if (sockNum < 1024)
    {
        perror("Permission denied");
        exit(1);
    }
		if (msgsock == -1)
		{
			perror("Accepted");
		}
		else
		{
			inet_ntop(from.sin_family, &from.sin_addr, buf, sizeof(buf));
			printf("Accepted connection from '%s', port %d\n", buf, ntohs(from.sin_port));

			do
			{
				bzero(buf,sizeof(buf));

				if((rval = read(msgsock,buf,sizeof(buf)-1)) < 0)
				{
					perror("reading stream message");
				}

				if(rval == 0)
				{
					printf("Ending connection\n");
				}

				else
				{
					buf[rval] = '\0';
					safe_write(rval,buf,getFileSize(buf));
				}

			}
			while(rval != 0);
			close(msgsock);
		}
	}while(true);
}