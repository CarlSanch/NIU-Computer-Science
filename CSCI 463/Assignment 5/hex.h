////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assignment #5	Semester: Spring 2021
//
//	Due: Tuesday, March 23, 2021
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

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