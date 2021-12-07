////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assignment #5	Semester: Spring 2021
//
//	Due: Tuesday, March 23, 2021
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "memory.h" 		 
#include "registerfile.h"	  
#include "rv32i_hart.h"		  
#include "cpu_single_hart.h"  

#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <cassert>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using std::cerr;
using std::endl;
using std::cout;
using std::setfill;
using std::setw;
using std::dec;
using std::istringstream;
using std::stoul;

typedef hex hexCall;
typedef rv32i_decode decodeCall;

static void usage()
{
    cerr << "Usage: rv32i [-d] [-i] [-r] [-z] [-l exec-limit ] [-m hex-mem-size] infile" << endl;
    cerr << "    -d show disassembly before program execution" << endl;
    cerr << "    -i show instruction printing during execution" << endl;
    cerr << "    -l maximum number of instructions to exec" << endl;
    cerr << "    -m specify memory size (default = 0 x100)" << endl;
    cerr << "    -r show register printing during execution" << endl;
    cerr << "    -z show a dump of the regs & memory after simulation" << endl;
    exit (1);
}

static void disassemble(const memory &mem)
{
	for (u_int pc = 0; pc < mem.get_size();)
	{
        cout << hexCall::to_hex32(pc) << ": " << hex::to_hex32(mem.get32(pc)) << "  ";
	    cout << decodeCall::decode(pc,mem.get32(pc)) << endl;
        pc += 4; 
	}
}

int main(int argc, char **argv){

    uint32_t memory_limit = 0x100;
    int64_t insn_limit = 0;
    bool show_instructions = false;
    bool show_registers = false;
    bool dflag = false;
    bool zflag = false;
    int opt;

    while ((opt = getopt(argc, argv, "m:dirzl:")) != -1) 
    {
        switch (opt) 
        {
		case 'm':
			{
				istringstream iss(optarg);
				iss >> std::hex >> memory_limit;
			}
			break;
        case 'l':
			{
				istringstream iss(optarg);
				iss >> std::hex >> insn_limit;
			}
			break;
            case 'r':
                show_registers = true; 
                break;
            case 'd':
                dflag = true; 
                break;
            case 'i':
                show_instructions = true; 
                break;
            case 'z':
                zflag = true; 
                break;
            default: usage();
        }
    }

    memory mem(memory_limit);
    cpu_single_hart cpu(mem);
    cpu.reset();
    cpu.set_show_instructions(show_instructions); 
    cpu.set_show_registers(show_registers);

    if(optind >= argc)
    {
        usage();
    }

    if(!mem.load_file(argv[optind]))
    {
        usage(); 
    }

    if(dflag) 
    { 
        disassemble(mem); 
    }

    cpu.run(insn_limit);

    if(zflag) 
    {
        cpu.dump(); 
        mem.dump(); 
    }
    return 0;
}