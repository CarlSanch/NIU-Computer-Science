#include "htable.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters

// Hash function, you may NOT modify this function
int HT::hash(const string &s) {
  int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

  return n % hsize;
}

// You will complete the code below ...
HT::HT(const unsigned &hs)
{
	hTable.resize(hs);
	pTable.resize(hs);
	hsize = TBL_SZ;

	for (unsigned int i = 0; i != hs; i++)
	{
		hTable[i].key = FREE;
	}
}

HT::~HT() {}

void HT::insert(const Entry &e) 
{
	int index = hash(e.key);
	for (unsigned int i = 0; i < hsize; i++)
	{
		if(hTable[(index + i) % hsize].key == FREE)
		{
			cout << "Entry = " << (index + i) % hsize << endl;
			hTable[(index + i) % hsize] = e;
			pTable[i] = &hTable[(index + i) % hsize];
		
			if (hTable[(index + i) % hsize].key == e.key)
			{
				cout << "This is a duplicate key, will not insert" << endl;
			}
		}
		
		if (i == hsize)
			cout << "Table is full, will not insert" << endl;
	}
}

void HT::search(const string &key)
{
	int index = hash(key);
	for (unsigned int i = 0; i < hsize; i++)
	{
		if (hTable[(index + i) % hsize].key == key)
		{
			cout << " -> number:" << setw(4) << hTable[(index + i) % hsize].num
	    		<< " - item: " << hTable[(index + i)%hsize].desc << endl;
		}
	}
	if (hTable[(index + i) % hsize].key != key)
	{
		cout << "Not found in current table" << endl;
	}
}

void HT::hTable_print()
{
	bool last = false;
	for (unsigned int i = 0; i < hsize; i++)
	{
		if (hTable[i].key != FREE)
		{
			if (last)cout << endl;
			cout << setw(4) << i << ":" << hTable[i].key << " - "
			<< setw(5) << hTable[i].num << " - " << hTable[i].desc << endl;

			last = false;
		}
		else
		{
			last = true;
		}
	}
	cout << endl;
}

void HT::pTable_print()
{
	sort(pTable);
	for (unsigned int i = 0; i < pTable.size(); i++)
	{
		cout << pTable[i]->key << " - " << right << setw(5) << pTable[i]->num
		<< " - " << left << pTable[i]->desc << endl;
	}
	cout << endl;
}
