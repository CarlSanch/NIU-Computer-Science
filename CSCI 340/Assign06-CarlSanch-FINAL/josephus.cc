#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include <iomanip>
#include "josephus.h"

using namespace std;

const int TAGS_LINE = 12;

int main()
{
    args josephusArgs; 
    list<string> josephusList; 
    unsigned cnt = 1; 
    cout << "\nNumber of people? 41";
    josephusArgs.N = 41;
    cout << "\nIndex for emlination? 3";
    josephusArgs.M = 3;
    cout << "\nIndex for printing? 7 \n";
    josephusArgs.K = 7;

    init_vals(josephusList, josephusArgs); //Filling the list
    print_list(josephusList, cnt); //prints list before altering elims
    josephusArgs.M -= 1; //fixing elims
    auto indexIt = josephusArgs.M % josephusList.size(); //iterator for elims

    while(josephusList.size() >1)
    {
  	auto listIter = josephusList.begin();
        advance(listIter, indexIt);  
	josephusList.erase(listIter);     
    	indexIt += josephusArgs.M;     
    	indexIt %= josephusList.size();

        if( (cnt % josephusArgs.K == 0 && cnt != 0) || josephusList.size() == 1) //prints out list with the header every Kth time
            print_list(josephusList, cnt);

        cnt++; 
    }

    cout << endl;
    return 0;
}


void init_vals(list<string>& list, args& in) {
    list.resize(in.N);
    generate(list.begin(), list.end(), SEQ(in.N));
}

void print_list(const list<string>& list, const unsigned& cnt)
{
    
    int itemCnt = 0; 

    if(cnt < 2) { //prints out the intial group header
        cout << "\n Initial group of people \n"
             << "-------------------------" << endl;
    }
    else { //prints out after elimation group header
        cout <<"\n After emliminating " << cnt << "th soldier" << endl
             << "------------------------------------" << endl;
    }

    for(auto listIt = list.begin(); listIt != list.end(); listIt++) 
    { 	   
	if(itemCnt % TAGS_LINE == 0 && itemCnt != 0) //prints a new line 
	cout << endl;
        cout << *listIt << " ";
        itemCnt++;
    }
    cout << endl;
}
