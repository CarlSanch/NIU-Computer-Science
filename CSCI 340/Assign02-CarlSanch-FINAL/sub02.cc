#include "assignment02.h"

using namespace std;
// to open two data files
void open_files(ifstream &is1, ifstream &is2)
{
	is1.open(FILE1);	//Opens file for reading
	is2.open(FILE2);	//opens file for reading

	if (!is1.is_open() || !is2.is_open())	//If either is1 or is2 cannot open, abort
	{
		cerr << "Could not find one or more files. Ending program" << endl;
		exit(1);
	}	
}

// to read contents of two data files
void read_data(ifstream &is, vector<vector<int>> &m)
{
	int row = m.size();
	int col = m[0].size();
	while (!is.eof())	//while the file has not reached the end of the file contents
	{
		for (int i = 0; i < row; i++)	//loop to go through the rows
		{
			for (int j = 0; j < col; j++)	//loop to go through the columns
			{
				is >> m[i][j];	//inserting the val into the designated location
			}
		}
	}
}

// to print contents of all matrices
void print_data(const vector<vector<int>> &m)
{
	int row = m.size();	//identifying the amount of rows in the matrix
	int col = m[0].size();	//identifying the columns in the matrix
	int temp = 0;		//temp int to see when we need to create a new line based on rows

	cout << row << " x " << col;
	cout << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << setw(8);

	for (int i = 0; i < row; i++) //for loop to traverse rows
	{
		for (int j = 0; j < col; j++)	//for loop to traverse columns
		{
			if (i > temp)
			{
				cout << endl; //if i is greater than temp, we started a new row. so wee need to print a new line
			}

			cout << m[i][j] << setw(8); //printing out the contents of the matrix
			temp = i;	//setting temp to i to see if we start a new row or not
		}
	}
}

// to generate a matrix by multiplying two input matrices
void gen_data(const vector<vector<int>> &a, const vector<vector<int>> &b, vector<vector<int>> &c)
{
	for (unsigned int k = 0; k < b.size(); k++)	//for loop to traverse rows            b[i].size()
	{
		for (unsigned int i = 0; i < c.size(); i++)	//for loop to traverse columns                  c.size()
		{	
			for (unsigned int j = 0; j < c[i].size(); j++)	//for loop to traverse row/columns of a and b          c[i].size()
			{ 
				 c[i][j] += a[i][k] * b[k][j];	//multipplies a and b to get c
			}
		}
	}
}

