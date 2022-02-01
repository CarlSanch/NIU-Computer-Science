////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assinment # 3	Semester: Spring 2021
//
//	Due: Friday, February 12, 2021
//
//	Purpose: This program will simulate a computer system memory. It it broken up into several files
//		 Main.cpp runs the code from memory.cpp and hex.cpp, also caontains usage function.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "hex.h"
#include "memory.h"
#include <unistd.h>
#include <sstream>
#include <iostream>
#include <iomanip>

using std::cerr;
using std::endl;
using std::cout;

//provides usage error message and pattern to cerr and terminates program
static void usage()
{
	cerr << "Usage: rv32i [-m hex-mem-size] infile" << endl;
	cerr << "    -m specify memory size (default = 0x100)" << endl;
	exit(1);
}

int main(int argc, char **argv)
{
	uint32_t memory_limit = 0x100;	// default memory size is 0x100

	int opt;
	//while loop that checks arguments
	while ((opt = getopt(argc, argv, "m:")) != -1)
	{
		//switch that finds m in argument and converts to memory limit
		switch(opt)
		{
		case 'm':
			{
				std::istringstream iss(optarg);
				iss >> std::hex >> memory_limit;
			}
			break;

		//if no m is found then stop program
		default:
			usage();
		}
	}

	//if no filename, stops program
	if (optind >= argc)
		usage();	// missing filename

	//creates vector with the given memory limit found in the argument
	memory mem(memory_limit);
	mem.dump();

	//if file is not found or cannot load, stops program
	if (!mem.load_file(argv[optind]))
		usage();

	//dumps mem vector
	mem.dump();

	//prints memory hexes
	cout << mem.get_size() << endl;
	cout << hex::to_hex32(mem.get8(0)) << endl;
	cout << hex::to_hex32(mem.get16(0)) << endl;
	cout << hex::to_hex32(mem.get32(0)) << endl;
	cout << hex::to_hex0x32(mem.get8(0)) << endl;
	cout << hex::to_hex0x32(mem.get16(0)) << endl;
	cout << hex::to_hex0x32(mem.get32(0)) << endl;
	cout << hex::to_hex8(mem.get8(0)) << endl;
	cout << hex::to_hex8(mem.get16(0)) << endl;
	cout << hex::to_hex8(mem.get32(0)) << endl;

	cout << hex::to_hex0x32(mem.get32(0x1000)) << endl;

	mem.set8(0x10, 0x12);
	mem.set16(0x14, 0x1234);
	mem.set32(0x18, 0x87654321);


	cout << hex::to_hex0x32(mem.get8_sx(0x0f)) << endl;
	cout << hex::to_hex0x32(mem.get8_sx(0x7f)) << endl;
	cout << hex::to_hex0x32(mem.get8_sx(0x80)) << endl;
	cout << hex::to_hex0x32(mem.get8_sx(0xe3)) << endl;

	cout << hex::to_hex0x32(mem.get16_sx(0xe0)) << endl;
	cout << hex::to_hex0x32(mem.get32_sx(0xe0)) << endl;

	//dumps vector 
	mem.dump();

	return 0;
}
