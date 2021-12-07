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
#include "hex.h"

#include <iostream>
#include <stdint.h>
#include <sstream>
#include <vector>
#include <fstream>

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;
using std::ifstream;
using std::noskipws;
using std::cerr;
using std::ios;

typedef hex hexCall;

/**
* @brief		    This function will allocate bytes into the vector and initialyzes
*			        every byte/element to 0xa5
*
* @param siz		size of vector
*******************************************************************************/
memory::memory(uint32_t siz)
{
    // Rounds siz so that formatting and aligning in dumnp is made easier 
    size = (siz + 15)&0xfffffff0; 

    //allocating the amount of space needed for the vector
    mem.resize(size, 0xa5);

}

/**
* @brief		    This function is a destructor that will clean up anything necessary
*******************************************************************************/
memory::~memory()
{

}

/**
* @brief		    This function will check to see if the address is in our
*			        simulated memory or not
*
* @param i		    Address of simulated memory
*
* @return		    Returns true if address is NOT in our memory. False if it is
*******************************************************************************/
bool memory::check_illegal(uint32_t i) const
{
	// Loop that checks size to see if is valid
	if (get_size() <= i)
	{
		cout << "WARNING: Address out of range: " << std::hex << hexCall::to_hex0x32(i) << endl;
		return true;
	}
	else
	{
		return false;
	}

}

/**
* @brief		    This function will round up the number of bytes in our memory
*
* @return		    Returns (rounded up) size of bytes
*******************************************************************************/
uint32_t memory::get_size() const
{
	return size;
}

/**
* @brief		    This function will check to see if the address is valid in our
*			        simulated memory by calling check_illegal()
*
* @param addr		address of simulated memory
*
* @return		    Returns 0 if address is illegal/not in our simulated memory.
*			        Returns the value of the byte in our simulated memory otherwise
*******************************************************************************/
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
		return mem.at(addr);
	}
}

/**
* @brief		    This function creates a 16-bit return value by calling get8 
*			        twice and then performing little-endian order to get the value
*
* @param addr		address of simulated memory
*
* @return		    Returns little-endian 16-bit value
*******************************************************************************/
uint16_t memory::get16(uint32_t addr) const
{
	//calls get8 twice and stores value in the given variable
	uint8_t x = get8(addr);
	uint8_t y = get8(addr + 1);
	//Little endian combination
	uint16_t z = (y << 8) | x;

	return z;
}

/**
* @brief		    This function is similar to get16. Calls get16 twice and performs
*			        little-endian order to return a 32-bit value
*
* @param addr		address of simulated memory
*
* @return		    Returns little-endian 32-bit value
*******************************************************************************/
uint32_t memory::get32(uint32_t addr) const
{
	//calls get16 twice and stores value in the given variable
	uint16_t a = get16(addr);
	uint16_t b = get16(addr + 2);
	//little endian combination
	uint32_t c = (b << 16) | a;

	return c;
}

/**
* @brief		    This function will call get8 and return a sign extended value
*
* @param addr		address of simulated memory
*
* @return		    Returns sign-extended value as a 32-bit signed int
*******************************************************************************/
int32_t memory::get8_sx(uint32_t addr) const
{
    return static_cast<int32_t>(get8(addr));
}

/**
* @brief		    This function calls get16 and returns the sign extended value
*
* @param addr		address of simulated memory
*
* @return		    Returns sign-extended value of the 16-bit value as a 32-bit signed int
*******************************************************************************/
int32_t memory::get16_sx(uint32_t addr) const
{
    return static_cast<int32_t>(get16(addr));
}

/**
* @brief		    This function calls get32 and returns value as a signed integer
*
* @param addr		Address of simulated memory
*
* @return		    Returns value as a 32-bit signed integer
*******************************************************************************/
int32_t memory::get32_sx(uint32_t addr) const
{
	int32_t address = addr;
	return get32(address);
}

/**
* @brief		    This function calls check_illegal() and stores value into
*			        address if it is valid.
*
* @param addr		address of simulated memory
* @param val		value for given address
*
* @return		    Returns nothing if address is not valid
*******************************************************************************/
void memory::set8(uint32_t addr, uint8_t val)
{
	//for loop that checks if the address is illegal
	//if not, will store value at given address
	//in the mem vector
	if (check_illegal(addr))
	{
		mem.at(addr) = val;
	}
	else
	{
		return;
	}
}

/**
* @brief		    This function calls set8 twice and stores the values in	
*			        little-endian order at the given address
*
* @param addr		address of simulated memory
* @param val		value for given address
*******************************************************************************/
void memory::set16(uint32_t addr, uint16_t val)
{
	uint8_t x = val & 0xff;
	uint8_t y = val >> 8;
	set8(addr, x);
	set8(addr + 1, y);
}

/**
* @brief		    This function calls set16 twice and stores the values in
*			        little-endian order at the given address
*
* @param addr		address of simulated memory
* @param val		value for given address
*******************************************************************************/
void memory::set32(uint32_t addr, uint32_t val)
{
	uint16_t x = val & 0xffff;
	uint16_t y = val >> 16;
	set16(addr, x);
	set16(addr + 2, y);
}

/**
* @brief		    This function dumps the entirety of the simulated memory
*			        in hex with the corresponding ASCII characters		
*******************************************************************************/
void memory::dump() const
{
    char dump[17];
    dump[16] = 0;

	//loop goes through the whole mem vector based on
	//the given size of the vector
    for(uint32_t j = 0; j < size; j++)
    {
        //checks if current mem position is mod 16 so 
		//it can proceed to dump what was stored
        if(j % 16 == 0)
        {
            //makes sure the dump doesnt start at 0
            if(j != 0)
            {
                cout << " *" << dump << "*" << endl;
            }
            
            cout << hexCall::to_hex32(j) << ":";
            
        }

        uint8_t ch = get8(j);
        cout << (j % 16 == 8?"  ":" ") << hexCall::to_hex8(ch);
        dump[j % 16] = isprint(ch)?ch:'.';

    }

    cout << " *" << dump << "*" << endl;

}

/**
* @brief		    This function opens up file the fname file in binary, and
*			        proceeds to read the contents and store them into memory
*
* @param fname		name of the file to be opened
*
* @return		    Returns false if the file cannot be opened or if the file
*			        is too big, otherwise returns true
*******************************************************************************/
bool memory::load_file(const std::string &fname)
{
    char c;
    int i = 0; 

    ifstream infile(fname, ios::in|ios::binary);

    if (!infile)
    {
        cout << "Can't open file '" << fname << "' for reading" << endl;
        return false;
    }

    else 
    {
        infile >> noskipws;
        while(infile.get(c))
        {
            if(check_illegal(i) == false)
            {
                mem.at(i) = c;
            }

            else
            {
                cerr << "Program too big!" << endl;
                infile.close();
                return false;
            }

            i++;
        }   

        infile.close();
        return true;
    }

}