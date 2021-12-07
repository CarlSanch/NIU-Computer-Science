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
#include "registerfile.h"   

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cassert>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::setw;
using std::setfill;
using std::left;
using std::right;
using std::ostream;
using std::to_string;

typedef hex hexCall;

/**
* @brief		This function initializes the registers in the hart to 
*	            0xf0f0f0f0 except for register x0 which is always 0		
*
*******************************************************************************/

registerfile::registerfile()
{
    reset();
}

/**
* @brief		This function initializes register x0 to zero, and 
*		        all other registers to 0xf0f0f0f0.	
*
*******************************************************************************/

void registerfile::reset()
{
    registers = vector<int32_t>(32, 0xf0f0f0f0);
    registers[0] = 0;
}

/**
* @brief		This function assigns register r from parameter the given val. 
*			    If r is zero then do nothing.
*
* @param r		register location
* @param val    value to be inserted at register r
*	
*******************************************************************************/

void registerfile::set(uint32_t r, int32_t val)
{
    if(r > 0 && r <= 32) 
    {
        registers[r] = val;
    }
}

/**
* @brief		This function gets the value of register r. 
*               If r is zero then return zero.
*
* @param r	    register location
*
* @return		Returns nothing if register r is outside of vector
*******************************************************************************/

int32_t registerfile::get(uint32_t r) const
{
    if(r > 0 && r <= 32) 
    {
        return registers[r];
    }
    return 0;
}

/**
* @brief		This function dumps all the registers, and uses hdr to create
*               the appropriate header
*
* @param hdr	string that prints at the beginning of each output line
*
*******************************************************************************/

void registerfile::dump(const std::string &hdr="") const 
{
    for(int32_t i = 0; i < 32; i+=1)
    {
        if(i % 8 == 0)
        {
            cout << hdr << setfill(' ') << setw(3) << right << ("x" + to_string(i)) << " ";
        }
        else if(i % 4 == 0)
        {
            cout << " ";
        }

        cout << hdr << hexCall::to_hex32(registers[i]) << " ";

        if(i % 8 == 7 and i != 0)
        {
            cout << endl;
        }
    }
}