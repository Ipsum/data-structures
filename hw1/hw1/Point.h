/*-----Point.h-----
by: David Tyler
    16.322 Data Structures
    ECE Dept.
    UMASS Lowell

PURPOSE
Provides the interface to Point.cpp

CHANGES
09-18-13 v0.0.1 --- Passed in for homework 1 credit
*/

#ifndef __point__
#define __point__

//-----type definition-----//

// Type "Point" represents location of a point in x,y format. //

typedef struct {
    int x;
    int y;
} Point;

//-----function prototypes-----//

bool GetPoint(char *prompt, Point &pt);
void ShowPoint(Point pt);

#endif