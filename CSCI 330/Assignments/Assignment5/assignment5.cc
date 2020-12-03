/*
||  Course: CSCI-330        Assignment #5      Semester: Fall 2020                                                                
||  NAME: Carlos Sanchez    Z-ID: z1729554                                                                         
||  TA's Name: Venkata Sai Haswanth                                                                                                 
||  Due: Friday, 10/23/20 by 11:59PM                                                                                                                                       
*/
#include <iostream>
#include <cstring>
#include <climits>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;

void commands(char * coms[], int count, int fd[]); //just declaring function to avoid error

int main() 
//main function will run a loop to read inputs and split the commands
{  

   //can hold 127 * 5 (+ 1 for null char)
   char cmd[636];
   
   //pointers to commands
   char * comansp[5];
   int count;
   bool quit = false;
   int fd[2];
   
   while (quit == false)
   {
      // reset the counter
      count = 0;
      
      //read in
      cout << "Please enter two-five commands to be piped,"
           << " quit anytime by typing \"quit\" \n";
      cin.getline(cmd, 636);
      
      if (count > 5 || count < 2)
      {
	cout << "Invalid amount of commands, exiting program"
	exit(1);
      }

      //split commands up
      comansp[count] = strtok(cmd," |");
      while (((comansp[count] != nullptr) && (count < 5)))
      {
         count++;
	 comansp[count] = strtok(NULL," |\n");
      }
      
      //function to fork, pipe, exec everything
      commands(comansp, count, fd);
      
      //test to see if "quit" appeared in commands
      quit = (strcmp(cmd, "quit") != 0)? false : true;
   }
   return 0;
}

void commands(char * coms[], int count, int fd[])
// commands function will run all commands. parameters check array of pointers, how many there are
// file descriptor and placeholde for file descriptor
{
   int fdhold = -1;
   
   //starting pipe
   pipe(fd);
      
   for (int i = 0; i < count; ++i)
   {
      
     	 pid_t pid = fork();
     	 if (pid > 0) // Parent
     	 {
     		  int status;
	 
		  //closes fd[1] since waitpid will not end without doing so
       		  close(fd[1]);
	 
		  //closes fdhold (pipe output (read) file descriptor)
        	  close(fdhold);
	 
		  //waits for the child process to end
       		  waitpid(pid, &status, 0);
	 
		  //holds pipe output (read) file descriptor
        	  fdhold = fd[0];
	 
		  //new pipe since fd[1] had to be closed in parent
        	  pipe(fd);
	    
     	  }
	  else if (pid == 0) // child
    	  {
        	  if (i == 0) // first argument
          	  {
	    	  //first argument, no need for stdin
	    	  close(0);
	    
	    	  //copy pipe write to stdout
	    	  dup2(fd[1], 1);
	    
	    	  //close uneeded pipes
	    	  close(fd[0]);
	    	  close(fd[1]);
	    
	    	  //exec with exit if it fails
	    	  execlp(coms[i], coms[i], '\0');
	    	  cout << "not a command!";
	    	  exit(1);
	 }

 	else if (i < count-1)
 	//not first command, not last
	{
	    //nothing is going to be written to stdin, nor stdout
	    //closing each fd
	    close(0);
	    close(1);
	    
	    //fdhold was the old pipe output(read)
	    //so it is used as the input here
	    dup2(fdhold, 0);
	    
	    //copy pipe write to stdout
	    dup2(fd[1], 1);
	    
	    //close old pipes
	    close(fd[1]);
	    close(fd[0]);
	    close(fdhold);
	    
	    //exec with exit if it fails
	    execlp(coms[i], coms[i], '\0');
	    cout << "That was not a command";
	    exit(1);
	 }

 else
 //last command, fd 1 is needed for writing to stdout
	 {
	    //fdhold was the old pipe output(read)
	    //so it is used as the input here
	    dup2(fdhold, 0);
	    
	    //close old/uneeded pipes
	    close(fd[1]);
	    close(fd[0]);
	    close(fdhold);
	    
	    //exec with exit if it fails
	    execlp(coms[i], coms[i], '\0');
	    cout << "not a command!";
	    exit(1);
	 }
    }
 else //failed to fork
     	 {
		 exit(1);
    	 }
   }
   
   close(fd[0]);
   close(fd[1]);
   close(fdhold);
}
