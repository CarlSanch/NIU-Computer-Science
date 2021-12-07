////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assignment #5	Semester: Spring 2021
//
//	Due: Tuesday, March 23, 2021
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <vector>

#ifndef _REG_H
#define _REG_H

using std::vector;

class registerfile 
{
	public :
		registerfile ();

		void reset();
		void set(uint32_t r, int32_t val);
		int32_t get(uint32_t r) const;
		void dump(const std::string &hdr) const;

	private :
		vector<int32_t> registers;
};
#endif