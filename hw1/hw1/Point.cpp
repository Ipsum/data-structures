/*-----Point.cpp-----
by: David Tyler
    16.322 Data Structures
    ECE Dept.
    UMASS Lowell

PURPOSE
This file contains functions related to the Point struct

CHANGES
09-18-13 v0.0.1 --- Passed in for homework 1 credit
*/

#include "Point.h"
#include <iostream>

/*-----GetPoint()-----

PURPOSE
Prompt for and read in a point from the keyboard

OUTPUT
pt -- the (x,y) point read in

RETURN
true if a point was read in,
false otherwise.                               */

bool GetPoint(char *prompt, Point &pt)
{
    bool gotPt = false;

    std::cout<<prompt;

    if (std::cin.peek()!='\n')
    {
        std::cin>>pt.x>>pt.y;
        gotPt=true;
    }

    std::cin.ignore(INT_MAX,'\n');

    return gotPt;
}
/*-----ShowPoint()-----

PURPOSE
Displays the Point argument on the screen 
in (x,y) format

OUTPUT
pt -- the point displayed

RETURN
void                                      */

void ShowPoint(Point pt)
{
    std::cout<<"("<<pt.x<<", "<<pt.y<<")"<<std::endl;
}