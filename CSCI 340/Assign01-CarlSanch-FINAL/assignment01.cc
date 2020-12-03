// Carlo Sanchez
// z1729554
// Course340 Section003
//
// I certify that this is my own work and where appropriate an extension of the starter code provided for the assignment.

#include "assignment01.h"

using namespace std;
// Add needed constants
const int LOW = 1;
const int HIGH = 10000;
const int VEC_SIZE = 200;
// Add code for genRndNums
void genRndNums(vector<int> v)
{
  srand (1); //Initialized random number seed generator with seed	
  for (unsigned int i = 0; i < VEC_SIZE; i++)
  {
	  int random = rand() % LOW + HIGH; //Initialized an integer to assign random numbers to
	  v.push_back(random); // Adding the random numbers into the vector v
  }
}
// Add code for printVec
void printVec(const vector<int> v)
{
  for(unsigned int i = 0; i < v.size(); i++)
  {
	  cout << v[i] << " " ; // Prints all numbers in the vector starting from the first position
  }
}

int 
main() 
{
// Declare vector v
vector<int> v;
// Generate random numbers to fill vector v	
genRndNums(v);
// Using STL sort sort v
sort (v.begin(), v.end());
// Print vector of sorted random numbers
printVec(v);
    return 1;
}


