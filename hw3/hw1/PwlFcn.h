/*-----PwlFcn.h-----
by: David Tyler
    16.322 Data Structures
    ECE Dept.
    UMASS Lowell

PURPOSE
Provides the interface to PwlFcn.cpp

CHANGES
10-02-13 --- Passed in for homework 2 credit
*/

#ifndef __pwlfcn__
#define __pwlfcn__

#include "Point.h"

//-----constant definitions-----//
const unsigned MaxPts = 10;

//-----class definition-----//

// Type "PwlFcn" represents a series of points that//
// define a piecewise linear function              //

class PwlFcn
{
public:
    //Constructor
    PwlFcn() : numPts(0) { }
    //Accessors
    unsigned NumPts() { return numPts; }
    Point Pt(unsigned i) { return pt[i]; }
    bool Defined() { return defined; }
    //I/O functions
    bool Get(istream &is);
    void Show(ostream &os);
    //Interpolate fcn
    double Interpolate(double x);
    //Overloaded operator(s)
    PwlFcn operator+(Point p);
private:
    bool defined;
    unsigned numPts;
    Point pt[MaxPts];
};

//-----overloaded operators-----//
ostream & operator<<(ostream &os,PwlFcn &f);
istream & operator>>(istream &is,PwlFcn &f);

bool operator<(Point p1, Point p2);
bool operator==(Point p1, Point p2);
bool operator>(Point p1, Point p2);

//----compare function for qsort-----//
int Compare (const void * a, const void * b);

#endif