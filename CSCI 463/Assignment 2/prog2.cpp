////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Carlos Sanchez	z-id: z1729554
//
//	Course: CSCI - 463	Assignment # 2	Semester: Spring 2021
//
//	Due: Friday, January 29th, 2021
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <cstdint>

using namespace std;

/**
* @brief		    This function extracts and shows the sign, exponent and
*					significand from the 32 bit value passed in
*
* @param x  		user inputed value that will be converted
*
*******************************************************************************/
void printBinFloat(uint32_t x)
{
	uint32_t origVal = 0x80000000; 
	int32_t temp = 0x00400000; 				   
	bool sign = x & 0x80000000;
	int32_t exp = ((x & 0x7f800000) >> 23) - 127; 
	uint32_t sig = x & 0x007fffff; 

	cout << "0x" << setfill('0') << hex << setw(8) << x << " =";

	for (size_t i = 0; i < 32; ++i)
	{

		if (i % 4 == 0)
		{
			cout << " ";
		}

		cout << (x & origVal ? '1' : '0');
		origVal = (origVal >> 1);

	}
	
	cout << endl;
	cout << "sign: " << sign << endl;
	cout << " exp: 0x" << setfill('0') << setw(8) << hex << exp << dec << " (" << exp << ")" << endl;
	cout << " sig: 0x" << setfill('0') << setw(8) << hex << sig << endl;
	
	if (( exp == 0x00000080 ) && (sign == 0 ))
	{
		cout << "+" << "inf";
	}

	else if ((exp == 0x00000080) && (sign == 1))
	{
		cout << "-" << "inf";
	}

	else
	{
		if ((uint32_t(exp) == 0xffffff81) && (sign == 0))
		{
			cout << "+" << "0";
		}

		else if ((uint32_t(exp) == 0xffffff81) && (sign == 1))
		{
			cout << "-" << "0";
		}

		else
		{
			if (sign == true)
			{
				if (exp > 0)
				{
					cout << "-" << "1";

					for (int i = 0; i < 23; ++i)
					{
						cout << (sig & temp ? '1' : '0');						
						temp = (temp >> 1); 
					}

					for (int i = 0; i < (exp - 23); ++i)
					{
						cout << "0";
					}

					cout << ".0";
				}

				else if (exp < 0)
				{

					int32_t expcounter = ((exp + 1) * -1);

					cout << "-";
					cout << "0.";

					for (int i = 0; i < (expcounter); ++i)
					{
						cout << "0";
					}

					cout << "1";

					for (int i = 0; i < 23; ++i)
					{
						cout << (sig & temp ? '1' : '0');
						temp = (temp << 1);
					}

				}
				else if (exp == 0)
				{
					cout << "-" << "1.";

					int32_t expcounter = exp;

					for (int i = 0; i < 23; ++i)
					{
						cout << (sig & temp ? '1' : '0');
						temp = (temp >> 1);
					}

					for (int i = 0; i < expcounter; ++i)
					{
						cout << "0";
					}

				}
				else
				{
					cout << "The exponent is not a number";
				}
			}
			else if (sign == false)
			{ 
				if (exp > 0)
				{
					cout << "+1";

					for (int i = 0; i < 23; ++i)
					{
						cout << (sig & temp ? '1' : '0');
						temp = (temp >> 1);
					}

					for (int i = 0; i < (exp - 23); ++i)
					{
						cout << "0";
					}

					cout << ".0";
				}
				else if (exp < 0)
				{
					
					int32_t expcounter = ((exp + 1) * -1);

					cout << "+";
					cout << "0.";

					for (int i = 0; i < (expcounter); ++i)
					{
						cout << "0";
					}

					cout << "1";

					for (int i = 0; i < 23; ++i)
					{
						cout << (sig & temp ? '1' : '0');
						temp = (temp << 1);
					}

				}
				else if (exp == 0)
				{
					cout << "+" << "1.";
					int expcounter = exp;

					for (int i = 0; i < 23; ++i)
					{
						cout << (sig & temp ? '1' : '0');
						temp = (temp >> 1);
					}

					for (int i = 0; i < expcounter; ++i)
					{
						cout << "0";
					}

				}
				else
				{
					cout << "The exponent is not a number";
				}
				
			}
			else
			{
				cout << "Signed bit is not 1 or 0";
			}
		}
	}
}

/**
* @brief		    This main function accepts input from user, converts to hex 
*                   then calls printBinFloat with said value(s)
*******************************************************************************/
int main()
{
	uint32_t x = 0x3d200000;

	while(cin >> hex >> x)
	{
		printBinFloat(x);
		cout << endl;
	}

	return 0;
}