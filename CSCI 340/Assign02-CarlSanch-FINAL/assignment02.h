#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

#ifndef H_PROG2
#define H_PROG2

// data files
#define FILE1 "./assignment02a.dat"
#define FILE2 "./assignment02b.dat"

#define ITEM_W 8 // no of spaces for each printed number

// to open two data files
void open_files(ifstream&, ifstream&);

// to read contents of two data files
void read_data(ifstream&, vector <vector <int> >&);

// to print contents of all matrices
void print_data(const vector <vector<int> >&);

// to generate a matrix by multiplying two input matrices
void gen_data(const vector <vector<int> >&,
    			const vector <vector<int> >&,
    			vector <vector<int> >&);

#endif
