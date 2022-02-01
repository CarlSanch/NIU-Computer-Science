////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assignment #6	Semester: Spring 2021
//
//	Due: Friday, April 9, 2021
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <thread>
#include <mutex>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <math.h>

using std::cout;
using std::endl;
using std::mutex;
using std::vector;
using std::thread;
using std::cerr;
using std::dec;
using std::istringstream;

constexpr int rows = 1000; 	    /// < the number of rows in the work matrix
constexpr int cols = 100; 	    /// < the number of cols in the work matrix
mutex stdout_lock ; 		    /// < for serializing access to stdout
mutex counter_lock ; 		    /// < for dynamic balancing only
volatile int counter = rows ; 	    /// < for dynamic balancing only
vector <int> tcount ; 	            /// < count of rows summed for each thread
vector <uint64_t> sum ; 	    /// < the calculated sum from each thread
int work [rows][cols]; 	            /// < the matrix to be summed

/**
* @brief		   This function sums the rows of the matrix by using static 
*			   load balancing to determine which rows will be processed by
*			   each thread that is used.
*
* @param tid		   thread ID. helps determine the first row for each thread
* @param num_threads	   number of threads activated. default is 2. 
*************************************************************************************/
void sum_static(int tid, int num_threads)
{
    	int staticCount = tid;

	stdout_lock.lock();
	cout << "Thread " << tid << " starting" << endl;
	stdout_lock.unlock();

	while(staticCount < rows)
	{
		for(int i = 0; i < cols; i++)
		{
			sum[tid] = sum[tid] + work[staticCount][i];
		}

		staticCount = staticCount + num_threads;
		++tcount[tid];

	}

	stdout_lock.lock();
	cout << "Thread " << tid << " ending tcount=" << tcount[tid] << " sum=" << sum[tid] << endl;
	stdout_lock.unlock();
}

/**
* @brief		   This function sums the rows of the matrix by using dynamic 
*			   load balancing to determine which rows will be processed by
*			   each thread that is used.
*
* @param tid		   thread ID. helps determine the first row for each thread
***************************************************************************************/
void sum_dynamic(int tid)
{
	bool done = false;
	int dynCount;

	stdout_lock.lock();
	cout << "Thread " << tid << " starting" << endl;
	stdout_lock.unlock();

	while(!done)
	{
		counter_lock.lock();
		{
			if(counter > 0)
			{
                		--counter;
			}
			else 
			{
				done = true;
			}
		dynCount = counter;
		}

		counter_lock.unlock();
		if(!done)
		{
			++tcount[tid];
			for(int i = 0; i < cols; i++)
			{
				sum[tid] = sum[tid] + work[dynCount][i];
			}

		}

	}

	stdout_lock.lock();
	cout << "Thread " << tid << " ending tcount=" << tcount[tid] << " sum=" << sum[tid] << endl;
	stdout_lock.unlock();
}

/**
* @brief		This function calls check_illegal() and stores value into
*			address if it is valid.
*******************************************************************************/
static void usage()
{
    cerr << "Usage: rv32i [-d] [-t num]" << endl;
    cerr << "      -d Use dynamic load-balancing. (By default, uses static load balancing.)" << endl;
    cerr << "      -t Specifies the number of threads to use (By default, starts two threads.)" << endl;
    exit(1);
}

/**
* @brief		This main accepts command line parameters to see whether to use
*			static or dynamic functions, as well as the amount of threads
*			to use. Throws usage if a wrong command line is used
*
* @param argc		argument count. checks amount of arguments passed
* @param argv		argument vector. array of character pointers that lists arguments
*******************************************************************************/
int main(int argc, char **argv)
{
    uint64_t total_work = 0;
	uint64_t total_sum = 0;
    bool dynSum = false;
	int size = 2; 
	int opt;

	srand(0x1234);
	cout << thread::hardware_concurrency() << " concurrent threads supported."<< endl;
	for(int i=0; i < rows ; i++)
	{
		for(int j=0; j < cols; j++)
		{
			work[i][j] = rand();
		}
	}

	while ((opt = getopt(argc, argv, "t:d")) != -1) 
    {
		switch (opt) 
		{
			case 'd':
			{
				dynSum = true;
			}
			break;
			case 't':
			{
				istringstream iss(optarg);
                		iss >> dec >> size;
                		if(size > (int)thread::hardware_concurrency()) 
                		{
                    			size = (int)thread::hardware_concurrency();
                		}
			}
			break;
			default: usage();
		}
    }

	vector<std::thread*> threads;
	tcount.resize(size,0);
	sum.resize(size,0);

	for(int i = 0; i < size; i++)
	{
		if(dynSum)
		{
			threads.push_back(new std::thread(sum_dynamic,i));
		}
		else 
		{
			threads.push_back(new std::thread(sum_static,i,size));
		}
	}

	for (int i = 0; i < size; ++i)
	{
		threads.at(i)->join();
		delete threads.at(i);
		total_sum = total_sum + sum.at(i);
		total_work = total_work + tcount.at(i);
	}

	cout << "main() exiting, total_work=" << total_work << " gross_sum =" << total_sum << endl;
}
