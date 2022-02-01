////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assinment # 3	Semester: Spring 2021
//
//	Due: Friday, February 12, 2021
//
//	Purpose: This program will simulate a computer system memory. It it broken up into several files
//		 Hex.h and Hex.cpp are meant to format numbers as hex strings for printing.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "hex.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

//This function returns a string that is 2 hex digits, and it represents the 8 bits in
//the i argument that is passed through
string hex::to_hex8 (uint8_t i)
{
	//Formats an 8 bit integer (i) into a 2-character hex string with leading zeroes
	ostringstream os;
	//Static cast is used to prevent insertion operator from misprinting the 8-bit int
	os << std::hex << setfill('0') << setw(2) << static_cast<uint16_t>(i);
	return os.str();
}

//This function returns a string with 8 hex digits that represent the 32 bits of the 
//i argument thta is passed through 
string hex::to_hex32(uint32_t i)
{
	//Formats the 32 bit integer (i) into an 8-character hex string with leading zeroes
	ostringstream os;
	os << std::hex << setfill('0') << setw(8) << uint32_t(i);
	return os.str();
	
}

//This function returns a string beginning with '0x' followed by the 8 hex digits that represent
//the 32 bits of the i argument
string hex::to_hex0x32(uint32_t i)
{
	//Concatenates '0x' to the output of the to_hex32() function
	return string("0x") + to_hex32(i);
}
