////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assinment # 3	Semester: Spring 2021
//
//	Due: Tuesday, March 2  2021
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

/**
* @brief		This function will convert the 8 bit argument into
*			a string that is 2 hex digits
*
* @param i		value at given address in mem	
*
* @return		Returns string that is 2 hex digits
*******************************************************************************/
string hex::to_hex8 (uint8_t i)
{
	//Formats an 8 bit integer (i) into a 2-character hex string with leading zeroes
	ostringstream os;
	//Static cast is used to prevent insertion operator from misprinting the 8-bit int
	os << std::hex << setfill('0') << setw(2) << static_cast<uint16_t>(i);
	return os.str();
}

/**
* @brief		This function will convert the 32 bit integer into 8 hex digits 
*
* @param i		value at given address in mem
*
* @return		Returns string that is 8 hex digits
*******************************************************************************/
string hex::to_hex32(uint32_t i)
{
	//Formats the 32 bit integer (i) into an 8-character hex string with leading zeroes
	ostringstream os;
	os << std::hex << setfill('0') << setw(8) << i;
	return os.str();
	
}

/**
* @brief		This function will call to_hex32 and adds '0x' to the front
*
* @param i		value at given address in mem
*
* @return		Returns string that is 8 hex digits, beginning with '0x'
*******************************************************************************/
string hex::to_hex0x32(uint32_t i)
{
	//Concatenates '0x' to the output of the to_hex32() function
	return string("0x") + to_hex32(i);
}

/**
* @brief		This function will add '0x' in front of the 5 hex digits that
*			represent the 20 bits of the argument
*
* @param i		value at given address in mem
*
* @return		Returns string that is 5 hex digits, beginning with '0x'
*******************************************************************************/
string hex::to_hex0x20(uint32_t i)
{
	ostringstream os;
	os << std::hex << setfill('0') << setw(5) << i;
	return string("0x") + os.str();
}

/**
* @brief		This function will add '0x' in front of the 3hex digits that
*			represent the 12 bits of the argument
*
* @param i		value at given address in mem
*
* @return		Returns string that is 3 hex digits, beginning with '0x'
*******************************************************************************/
string hex::to_hex0x12(uint32_t i)
{
	ostringstream os;
	os << std::hex << setfill('0') << setw(3) << (i & 0x00000fff);
	return string("0x") + os.str();
}

