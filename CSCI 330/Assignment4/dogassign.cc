/*
 *  FILE:    DOG Assignment
   AUTHOR:    Carlos Sanchez
   LOGON ID:  Z1729554
   DUE DATE:  10/02/2020

   CSCi 330 

*/

#endif

#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "dogfunctions.h"
extern char * optarg;

using namespace std;

int main (int argc, char * argv[])
{
	int fd;
	int opt;
	char optstring[] = "sncrx";
	dogfunc openfiles;

	while ((opt = getopt(argc, argv, optstring)) != -1)
	{
		
		switch(opt)
		{

			case 's': // change buff size
	  	        openfiles.buffch = true;
	  	        openfiles.buffsize = *optarg;
	 	        break;
	    
			case 'n': //change number of bytes read
	 		openfiles.bytech = true;
	    		openfiles.bytes2read = *optarg; 
	    		break;
	    
	 		case 'c': // Caesar cipher
	    		if (openfiles.rotate == true)
	    			{
	       				cerr << "Cipher cannot be combined with rotate!\n";
	       				exit(-1);
	    			}
		       	else
	    			{
	       				openfiles.cipher = true;
	       				openfiles.shOrRotate = optarg;
	    			}
	    		break; 
	      
         		case 'r': //rotation for data
	    		if (openfiles.cipher == true)
	    			{
	       				cerr << "Rotate cannot be combined with cipher!\n";
	       				exit(-1);
	    			}
		       	else
	    			{
	       				openfiles.rotate = true;
	       				openfiles.shOrRotate = optarg;
	    			}
	    		break;
	    
	 		case 'x': //output data in hex
	    		openfiles.hexch = true;
	    		break;
		}
	}

	for(int i = optind; i < argc; i++)
   	{

         //open files, checks for succession
         fd = open(argv[i], O_RDWR);
         if(fd == -1)
         	{
            		cerr << "Cannot open said file" << endl;
	    		exit(1);
         	}

         	newprint(fd, openfilef);

         	//close each file 
         	close(fd);

   	}
}

