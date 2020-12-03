/* FILE:      DOG ASSIGNMENT
   AUTHOR:    Carlos Sanchez
   LOGON ID:  z1729554
   DUE DATE:  10/20/2020

   CSCi 330
*/

#ifndef dogfunctions
#define dogfunctions

/*
 * struct that holds flags for command line. would be much cxleaner if I wrote a header rather than oput them in main*/

struct dogflags
{
   bool buffch;
   int buffsize;
   bool bytech;
   int bytes2read;
   bool cipher;
   bool rotate;
   char *shOrRotate = NULL;
   bool hexch;
   dogflags();
};

//function
void hexch(int);
char hexselect(int);
void byte2r(int);
void buffch(int);
void cipher(int);
void rotate(int);
void newprint(int, dogflags&);
#endif
