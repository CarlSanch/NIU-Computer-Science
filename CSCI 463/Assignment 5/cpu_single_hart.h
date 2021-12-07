////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assignment #5	Semester: Spring 2021
//
//	Due: Tuesday, March 23, 2021
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "rv32i_hart.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#ifndef CPU_HART_H
#define CPU_HART_H

class cpu_single_hart : public rv32i_hart
{
    public:
    cpu_single_hart(memory &mem) : rv32i_hart(mem) { }
    void run(uint64_t exec_limit);
};

#endif