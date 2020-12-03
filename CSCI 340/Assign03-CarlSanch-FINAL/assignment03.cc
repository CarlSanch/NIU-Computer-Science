//Carlos Sanchez
//z1729554
//CSCI340 - 003
//
//I ceritfy that this is my own work and where appropriate an extension of the starter code provided for the assignment

#include <iostream>
#include <set>
#include <iomanip>

using std::set;
using namespace std;

void sieve(set<int>& s, int n)
{

	//loop inserts numbers from 1 to n into the set
	for(int i = 1; i <= n; i++)
	{
		s.insert(i);
	}

	//loop begins finding primes, and weeding out all multiples of primes
	for(int k = 2; k < *s.rbegin(); k++)
	{
		for (int g = k; g <= n; g++)
		{
			s.erase(k * g);
		}
	}	
}

void print_primes(const set<int>& s)
{
	int rowmax = 16;
	int newline = 1;
	cout << "All Primes: " << endl;

	//Printing out all primes, starts at the beginning and keeps going till it hits the end
	for(auto it = s.begin(); it != s.end(); ++it)
	{
		cout << setw(5);
		cout << " " << *it;
		//trying to sort all the printed primes into rows of 16 and creates a new line if at 16
		if(newline == rowmax)
		{
			cout << endl;
			newline = 0;
		}
		newline++;
	}
}

int main()
{	
	//declaring set and int to store value given by the user
	set<int> Set;
	int i;
	cout << "Upper limit for the set of primes: ";
	cin >> i;
	sieve(Set, i);
	print_primes(Set);
	
	return 0;
}
