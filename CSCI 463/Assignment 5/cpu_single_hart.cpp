////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assignment #5	Semester: Spring 2021
//
//	Due: Tuesday, March 23, 2021
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "cpu_single_hart.h"
#include "registerfile.h"

#include <sstream>
#include <iostream>     
#include <iomanip>      
#include <cassert>

using std::cout;
using std::endl;

/**
* @brief		    This function sets register 2 to the memory size then 
*                   runs the process
*
* @param limit		number of instructions to be executed
*
*******************************************************************************/
void cpu_single_hart::run(uint64_t limit)
{

    regs.set(2, mem.get_size());
    uint32_t count = 0;

    while (!rv32i_hart::is_halted())
    {
        count++;
        
        if (limit == 0 || rv32i_hart::insn_counter < limit)
        {
            rv32i_hart::tick();
        }
        else
        {
            rv32i_hart::halt = true;
        }
        
    }

    cout << "Execution terminated. Reason: EBREAK instruction" << endl;
    cout << count << " instructions executed" << endl;
}