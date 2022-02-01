////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assinment # 3	Semester: Spring 2021
//
//	Due: Friday, February 12, 2021
//
//	Purpose: This program will simulate a computer system memory. It it broken up into several files
//		 Memory.h and Memory.cpp contains functions that create the mem vector, allocate bytes into it, 
//		 and fill the vector with addresses and whatever comes through the load file, if anything
//
//
//	Programmer's Note: I have an issue where I am noit getting the correct addresses showing up in dump.
//			   Must pinpoint where the issue stems from. Suspecting dump or check illegal or
//			   both and I am not doing the output on to_hex0x32 correctly; Must fix!!!
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "memory.h"
#include "hex.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;
using std::ifstream;
using std::noskipws;
using std::cerr;
using std::ios;

//Allocates siz bytes into the mem vector and initialyzes everything to '0xa5'
memory::memory(uint32_t siz)
{
	// Rounds siz so that formatting and aligning in dumnp is made easier
	siz = (siz + 15)&0xfffffff0;  //round the length up, mod-16
	size = siz;
 	mem.resize(size); //allocating the amount of space needed for the vector

	//for loop that makes each element in the mem vector '0xa5'
	for (uint8_t i  = 0; i < siz; i++)
	{
		mem[i] = 0xa5;
	}
}

//Destructor that cleans up anything necessary
memory::~memory()
{
	mem.erase(mem.begin(), mem.end());
}

//Returns true if address is not in the simulated memory. Prints out a warning if it is not there
bool memory::check_illegal(uint32_t i) const
{
	hex hexcall;
	// Loop that checks size to see if is valid
	if (get_size() <= i)
	{
		//hexcall.to_hex0x32(i);
		cout << "WARNING: Address out of range: " << std::hex << hexcall.to_hex0x32(i) << endl;
		return true;
	}
	else
	{
		return false;
	}

}

//Returns the rounded up number of bytes in simulated memory
uint32_t memory::get_size() const
{
	return size;
}

//Checks to see if the value is valid and in our simulated memory
uint8_t memory::get8(uint32_t addr) const
{
	//loop will check the address to see if it is valid by
	//calling the check_illegal function
	//if it is not, returns 0 to caller
	if (check_illegal(addr) == true)
	{
		return 0;
	}
	else
	{
		return mem[addr];
	}
}

//Function creates 16-bit return value by calling get8 twice and then performing
//liitle-endian combination to get the value
uint16_t memory::get16(uint32_t addr) const
{
	//calls get8 twice and stores value in the given variable
	uint8_t x = get8(addr);
	uint8_t y = get8(addr + 1);
	//Little endian combination
	uint16_t z = (y << 8) | x;

	return z;
}

//Similar to get16, calls get16 twice and performs little endian combination 
//to return the value
uint32_t memory::get32(uint32_t addr) const
{
	//calls get16 twice and stores value in the given variable
	uint16_t a = get16(addr);
	uint16_t b = get16(addr + 2);
	//little endian combination
	uint32_t c = (b << 16) | a;

	return c;
}

//Function calls get8 and returns the sign-extended value 
int32_t memory::get8_sx(uint32_t addr) const
{
	return static_cast<int32_t>(get8(addr));
}

//function calls get16 and returns the sign-extended value
int32_t memory::get16_sx(uint32_t addr) const
{
	return static_cast<int32_t>(get16(addr));
}

//function calls get32 and returns value as a signed integer
int32_t memory::get32_sx(uint32_t addr) const
{
	int32_t address = addr;
	return get32(address);
}

//Function sets byte in simulated memory at that address at given val
//if check illegal goes through
void memory::set8(uint32_t addr, uint8_t val)
{
	//for loop that checks if the address is illegal
	//if not, will store value at given address
	//in the mem vector
	if (check_illegal(addr) == false)
	{
		mem[addr] = val;
	}
	else
	{
		return;
	}
}

//function calls set 8 twice and stores the values in 
//little endian combination at the given address
void memory::set16(uint32_t addr, uint16_t val)
{
	uint8_t r = val & 0xff;
	uint8_t s = val >> 8;
	set8(addr, r);
	set8(addr + 1, s);
}

//function calls set16 twice and stores the values in
//little endian order combination starting at the
//given address
void memory::set32(uint32_t addr, uint32_t val)
{
	uint16_t t = val & 0xffff;
	uint16_t u = val >> 16;
	set16(addr, t);
	set16(addr + 2, u);
}

//dumps entirety of the simulated memory in hex with the
//corresponding ASCII characters
void memory::dump() const
{
	hex hexcall;
	char dump[17];
	dump[16] = 0;

	//loop goes through the whole mem vector based on
	//the given size of the vector
	for(uint32_t j = 0; j < size; j++)
	{
		//checks if current mem positin is mod 16 so 
		//it can proceed to dump what was stored
		if(j % 16 == 0)
		{
			//makes sure the dump doesnt start at 0
			if( j != 0)
			{
				cout << " *" << dump << "*" << endl;
			}
			
			cout << hexcall.to_hex32(j) << ":";	
		}	

		uint8_t ch = get8(j);

		cout << (j % 16 == 8 ? "  " : "  ") << hexcall.to_hex8(ch);

		dump[j % 16] = isprint(ch) ? ch : '.';
	}

	cout << " *" << dump << "*" << endl;
}

//opens file named fname in binary, reads contents into memory
bool memory::load_file(const string &fname)
{
        int i = 0;
	char c;

	//opening file in binary mode
	ifstream infile(fname, ios::in|ios::binary);

	//if staement if there is no file found
	if(!infile)
	{
		cout << "Can't open file " << fname << " for reading." << endl;
		return false;
	}

	else
	{
		infile >> noskipws;
		//while loop that reads from file one character at a time
		while(infile.get(c))
		{
			//checks to see if it is illegal before inserting to vector
			if (check_illegal(i) == false) 
			{
				mem[i] = c;
			}
			else
			{
				cerr << "Program too big." << endl;
				infile.close();
				return false;
			}

			i++;
		}

		infile.close();
		return true;

	}		
}

