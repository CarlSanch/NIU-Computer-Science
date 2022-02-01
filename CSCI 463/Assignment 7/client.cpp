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
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

/**
* @brief		This function will give the user a heads up on what the program
*				requires in order to properly function and work before exiting
*
*******************************************************************************/
static void usage()
{
    cerr << " Usage: client [-s server-ip] server-port " << endl;
    cerr << " -s, Specify the server’s IPv4 number in dotted-quad format. Default: 127.0.0.1 " << endl;
    cerr << " server-port, The server port number to which the client must connect." << endl;
	assert("Missing ip-number/port");
}

/**
* @brief			This function will load the file and put the data from the file
*					into the character array buf 
*
* @param buf		pointer to character array called buf. Used to load in data
*
* @return			Returns true when the file is done loading in
*******************************************************************************/
bool load_file (char *buf)
{
	char c;
	int i = 0;

	while (cin.get(c))
	{
        buf[i] = c;
        i++;
	}
	return true;
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
static ssize_t safe_write(int fd, char *buf, size_t buf_len)
{
	while (buf_len > 0)
    {
        ssize_t wlen = write(fileno(stdout), buf, buf_len);

        if(wlen == -1) 
        {
            return -1;
        } 

        buf_len = buf_len - wlen;
        buf = buf + wlen;
    }
    return buf_len;
}

/**
* @brief		This function will convert the 32 bit integer into 8 hex digits 
*
* @param fd		sock from main
*
* @return		Returns 0 when the function is done printing. -1 when there 
*				is an error
*******************************************************************************/
static int print_reponse(int fd)
{
    char buf[2048];
    int rval = 1;
    while(rval>0)
    {
        if((rval = read(fd,buf,sizeof(buf)-1)) == -1)
        {
            perror("reading stream message");
            return -1;
        }
        else if(rval > 0)
        {
            buf[rval] = '\0';
            cout << "--- read " << rval << "bytes --->>>" << buf << "<<" << endl;
        }
    }
    return 0;
}

/**
* @brief			This is the main function, and it reads from standard input
*					to see if there is a specific ip address to use. Then proceeds to read
*					from file and write to the server
*
* @param argc		argument count. checks amount of arguments passed
* @param argv		argument vector. array of character pointers that lists arguments
*
* @return			Returns 0 when successfully opens socket and writes to server
*******************************************************************************/
int main(int argc,char *argv[])
{
	char buf[2048];
	load_file(buf);
	int sock;
	struct sockaddr_in server;
	const char *ip_addr = "127.0.0.1";
	int opt;

	while ((opt = getopt(argc, argv, "s:")) != -1) 
    {
		switch (opt) 
		{
			case 's':
            {
				ip_addr = argv[2];
				break;
			}

			default:
				usage();
				break;
		}
    }

	sock = socket(AF_INET, SOCK_STREAM,0);

	if(sock < 0)
    {
		perror("opening stream socket");
		exit(1);
	}

	server.sin_family = AF_INET;

	if(inet_pton(AF_INET, ip_addr, &server.sin_addr)<=0)
    {
		fprintf(stderr, "%s : invalied address/format\n",ip_addr);
		usage();
		exit(2); 
	}

	if (argc < 3)
    {
		server.sin_port = htons(atoi(argv[1]));
	}
    else
    {
		server.sin_port = htons(atoi(argv[3]));
	}

	if (connect(sock,(sockaddr*)&server, sizeof(server)) < 0)
	{
        perror("Connecting Stream Socket");
        exit(1);
	}

    cout << argv[2] << endl;

	if (safe_write(sock, buf, sizeof(buf)) < 0)
	{
        perror("Writing on stream socket");
        shutdown(sock, SHUT_WR);
        print_reponse(sock);
        close(sock);
	}

	return 0;
}