/*	CSCI 330			Assignment3		Fall2020
 *	Name: Carlos Sanchez		zID:z17295544
 *	TA:Gude Venkata SAi Haswanth
 *	Due: 9/18/2020
 */

#include <iomanip>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <cstring>

using namespace std;

/*	Main function, uses argc to check num of parameters passed
 *	argv is an array that checks each character typed
 */

int main(int  argc, char * argv[])
{
	int file;
	string input_line;
	ssize_t reading;
	char inputBuffer[1024];
	char* standInput;

	if (argc == 0)	//if nothing typed in, dont start program
	{
		cout << "No files were listed. Exiting.." << endl;
		exit(1);	
	}

	for (int i = 1; i < argc; i++)	//loop runs through each file passed through
	{
		standInput = argv[i];

		file = open(argv[i], O_RDWR | O_CREAT, 0755);	//opens file
		if (file == -1)	//if could not open file, close program
		{
			perror("opening file");
			exit(1);
		}
		
		if (strcmp(standInput, "-") == 0) //catches - and reads from standard input
		{
			while(cin)
			{
				getline(cin, input_line);//Reads from standard input
				cout << input_line << endl;
			}
		}

		reading = read(file, inputBuffer, 1024);	//initialize count, fill inputBuffer

		inputBuffer[reading] = ' ';
		if (reading == -1) //if file is empty then can't read, throw error
		{
			perror("reading file");
			exit(1);
		}

		cout << inputBuffer << endl; //print out what is on file
		close(file);  //closes file
		
	}

	return 0; 
}
