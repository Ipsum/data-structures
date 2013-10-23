/*-----PwlFcn.h-----
by: David Tyler
    16.322 Data Structures
    ECE Dept.
    UMASS Lowell

PURPOSE
Provides the interface to PwlFcn.cpp

CHANGES
09-18-13 v0.0.1 --- Passed in for homework 1 credit
*/

#ifndef __pwlfcn__
#define __pwlfcn__

#include "Point.h"

//-----constant definition(s)-----//

const unsigned MaxPts = 10; // Maxiumum points in a function definition

//-----type definition-----//

// Type "PwlFcn" represents a series of points that define a piecewise //
//                       linear function                               //

typedef struct {
    unsigned numPts;
    Point pt[MaxPts];
} PwlFcn;

//-----function prototypes-----//

bool GetF(char *prompt, PwlFcn &f);
void ShowF(PwlFcn &f);
int Interpolate(PwlFcn &f, int x);
int Compare (const void * a, const void * b);

//-----overloaded operators-----//

bool operator<(Point p1, Point p2);
bool operator==(Point p1, Point p2);
bool operator>(Point p1, Point p2);

#endif