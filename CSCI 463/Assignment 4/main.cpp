////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assinment # 3	Semester: Spring 2021
//
//	Due: Friday, February 12, 2021
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "memory.h"
#include "rv32i_decode.h"

#include <unistd.h>
#include <sstream>
#include <iostream>
#include <iomanip>

using std::cerr;
using std::endl;
using std::cout;
using std::setfill;
using std::setw;
using std::dec;

static void usage()
{
	cerr << "Usage: rv32i [-m hex-mem-size] infile" << endl;
	cerr << "    -m specify memory size (default = 0x100)" << endl;
	exit(1);
}

static void disassemble(const memory &mem)
{
	rv32i_decode decodeCall;
	for (uint32_t pc = 0; pc < mem.get_size();)
	{
		cout << hex::to_hex32(pc) << ": " << std::hex << setfill('0') << setw(8) << (mem.get32(pc)) << "  " << decodeCall.decode(pc, mem.get32(pc)) << dec << endl;
		pc += 4;
	}
}

int main(int argc, char **argv)
{
	uint32_t memory_limit = 0x100; // default memory size = 256 bytes
	int opt;
	while ((opt = getopt(argc, argv, "m:")) != -1)
	{
		switch (opt)
		{
		case 'm':
			{
				std::istringstream iss(optarg);
				iss >> std::hex >> memory_limit;
			}
			break;
		default: /* ’?’ */
			usage();
		}
	}
	if (optind >= argc)
	{
		usage(); // missing filename
	}

	memory mem(memory_limit);

	if (!mem.load_file(argv[optind]))
	{
		usage();
	}

	disassemble(mem);
	mem.dump();
	
	return 0;
}
