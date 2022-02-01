/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assignment #4	Semester: Spring 2021
//
//	Due: Tuesday, March 2, 2021
//
//	Purpose: This program will simulate a computer system memory. It is broken up into several files.
//		 Hex.h and Hex.cpp are used to format numbers as hex strings for printing.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include <iostream>
#include <string>

// This will prevent any duplications of functions, since hex.h is defined in main.cpp and hex.cpp
#ifndef _HEX_H
#define _HEX_H

class hex
{
public:
	static std::string to_hex8(uint8_t i);
	static std::string to_hex32(uint32_t i);
	static std::string to_hex0x32(uint32_t i);
	static std::string to_hex0x20(uint32_t i);
	static std::string to_hex0x12(uint32_t i);

};
#endif
