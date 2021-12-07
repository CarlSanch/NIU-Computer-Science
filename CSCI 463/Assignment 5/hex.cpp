////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assignment #5	Semester: Spring 2021
//
//	Due: Tuesday, March 23, 2021
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "hex.h"            
#include "memory.h"
#include "rv32i_decode.h"

#include <string>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::ostringstream;
using std::dec;
using std::setw;
using std::setfill;
using std::left;

typedef hex hexCall;

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
	os << std::hex << setfill('0') << setw(8) << static_cast<uint32_t>(i);
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

