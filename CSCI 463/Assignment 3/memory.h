////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assinment # 3	Semester: Spring 2021
//
//	Due: Friday, February 12, 2021
//
//	Purpose: This program will simulate a computer system memory. It it broken up into several files
//		 Memory.h and Memory.cpp contains functions that create the mem vector, allocate bytes to it, 
//		 and fill the vector with addresses and whatever comes through the load file, if anything
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

//This will prevent duplication of functions since memory.h is used in main.cpp and memory.cpp
#ifndef _MEM_H
#define _MEM_H

class memory
{
public:
	memory(uint32_t s);
	~memory();

	bool check_illegal(uint32_t addr) const;
	uint32_t get_size() const;
	uint8_t get8(uint32_t addr) const;
	uint16_t get16(uint32_t addr) const;
	uint32_t get32(uint32_t add) const;

	int32_t get8_sx(uint32_t addr) const;
	int32_t get16_sx(uint32_t addr) const;
	int32_t get32_sx(uint32_t addr) const;

	void set8(uint32_t addr, uint8_t val);
	void set16(uint32_t addr, uint16_t val);
	void set32(uint32_t addr, uint32_t val);

	void dump() const;

	bool load_file(const std::string &fname);

private:
	std::vector <uint8_t> mem;
	uint32_t size;
};

#endif
