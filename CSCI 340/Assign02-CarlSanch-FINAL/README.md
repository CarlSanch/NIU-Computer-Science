## CSCI 340 - Matrix Multiplication

For this computer assignment, you are to write and implement a C++ program to implement the matrix multiplication on randomly generated integers stored in data files.

Put the implementations of your subroutines (described below) in your source file **sub02.cc**. **NOTE:** You will need to create this file, you will need to do a `git add sub02.cc`, once you create it in your local repository and it will then be added to your GitHub repostority after you do a `git commit` and `git push`. **NOTE:** The repository as is will not compile to an executable at the start due to missing functions.

- `void open_files(ifstream &is1, ifstream &is2)`: Opens two data files for reading and creates the input streams `is1` and `is2`. If either file fails to open, it prints an error message on stderr and aborts the program with a non-zero exit value. The names of the input files are `assignment02a.dat` and `assignment02b.dat`, whose full path names are defined as `FILE1` and `FILE2` in the header file `assignment02.h` all included within starter repository.

- `void read_data(ifstream &is, vector<vector<int>> &m)`: Reads the input values from the input stream is and stores them in matrix `m`, which is defined as a two-dimensional vector of integers. The number of rows and columns of `m` are the pair of values given at the beginning of the corresponding data file and they are captured in the source file `assignment02.cc` (driver program) that is in the same directory with `assignment02.h`.

- `void print_data(const vector<vector<int>> &m)`: Prints the contents of on stdout by allocating `ITEM_W` spaces for each integer value, which is defined in the header file `assignment02.h`. The number of values printed in a single line equals to the number of columns of `m` and the number of lines on stdout equals to the number of rows of `m`.

- `void gen_data(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C)`: It multiples the values in the matrices `A` and `B` and stores the results in the matrix `C`. 
    - If `C(i, j)` is the value of `C` in row `i` and `j` of `C`, then `C(i, j) += A(i, k) * B(k, j)` for all index values of `k`, where `A(i, k)` is the value of `A` in row `i` and column `k` of `A`, and `B(k, j)` is the value of `B` in row `k` and column `j` of `B`. 
    - For a vector container use `C[i][j]` for `C(i, j)`, where `i = 0, 1, ..., size(C) – 1` and `j = 0, 1, ..., C[i].size() – 1`, and it’s the same for `A` and `B`.

**Programming Notes:**

- Do not change existing implementation in `assignment02.cc`, but you need to include any necessary headers and add necessary global constants.

- The header file assignment02.h is provided. To include the header file in your program, insert the statement: `#include “assignment02.h”` at the top of your source file `sub02.cc`. 

- Correct output is found in results02.out based the matrix values in data files assignment02a.dat and assignment02b.dat, these are just example. They can be changed, so do not design your program for the specific values in the data files. Your program is supposed to work for any matrix values in those files. 

- You are not allowed to use any I/O functions from the C library, such as `scanf` or `printf`. Instead, use the I/O functions from the C++ library, such as `cin` or `cout`.

- Add documentation to your source file (e.g. https://google.github.io/styleguide/cppguide.html#Comments).

- We have included a `Makefile` for your reference, in future assignments you will need to build your own. To compile your code just type `make` in the project directory. To test your program, execute `./assignment02.exe &> assignment02.out`, which will put the output (including any error messages) in file `assignment01.out`. You can find the correct output of this program in file `results02.out`, you can compare the two files by using `diff` on turing or hopper, `diff assignment02.out results02.out`, if the files are the same there will be no output from `diff`.

This semester you will need to make at least **three commits** to your local repository and at least one push to your master repository for each assignment. This will show the evolution of your assignments over time and the thought process behind the code. You will need to make sure your final **push** to your master repository is completed before the assignment is due (the system time stamps actions), if the assignment is late the TA will mark off points.

When your program is ready for grading, follow _**Assignment Submission Instructions**_. 
