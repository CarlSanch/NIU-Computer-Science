#ifndef H_JOSEPHUS
#define H_JOSEPHUS

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

#define NO_LETS  26    // no of letters in English alphabet
#define NO_ITEMS 12    // no of items printed on single line

// struct for input arguments

struct args {
    unsigned N,       // no of initial people   
             M,       // count to eliminate person
             K;       // frequency of printouts
};

// class to generate name tags for people

class SEQ {
private:
    string id;         // name tag for person
    unsigned size, nd; // no of people, no of digits in name tags

    // returns no of digits in name tags
    unsigned find_nd ( const double& sz ) {
        if ( ( sz / NO_LETS ) <= 1 ) return 2;
        else return ( find_nd ( sz / NO_LETS ) + 1 );
    }

public:
    // constructor for name-tag generator
    SEQ ( const unsigned& s = 1 ) : size ( s ) {
        double sz = ( double ) size / 9; nd = find_nd ( sz );
        id = string ( nd, 'A' ); id [ nd - 1 ] = '1'; 
    }

    // returns next name tag in sequence
    string operator ( ) ( ) {
        string tmp = id; int i = nd - 1;
        if ( id [ i ] < '9' ) id [ i ]++;
        else {
            id [ i ] = '1'; bool flag = true;
            for ( i--; i >= 0 && flag; i-- )
                if ( id [ i ] < 'Z' ) { id [ i ]++; flag = false; }
                else id [ i ] = 'A';
        } 
        return tmp;
    }
};

// reads and initializes all input arguments
void init_vals(list<string> &, args &);

// prints all name tags for remaining people after elimination
void print_list ( const list < string >&, const unsigned& );

#endif
