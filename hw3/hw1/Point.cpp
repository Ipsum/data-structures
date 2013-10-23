/*-----Point.cpp-----
by: David Tyler
    16.322 Data Structures
    ECE Dept.
    UMASS Lowell

PURPOSE
This file contains functions related to the Point class

CHANGES
10-02-13 --- Passed in for homework 2 credit
*/

#include "Point.h"
#include <iostream>

using namespace std;
/*-----X()-----
PURPOSE
x value accessor function

RETURN
The x coordinate of the point                */

double Point::X() const
{
    return x;
}

/*-----Y()-----
PURPOSE
y value accessor function

RETURN
The y coordinate of the point                */

double Point::Y() const
{
    return y;
}

/*-----GetPoint()-----

PURPOSE
Prompt for and read in a point from the keyboard

OUTPUT
pt -- the (x,y) point read in

RETURN
true if a point was read in,
false otherwise.                               */

void Point::Get(istream &is)
{
    defined = false;

    if (is.peek()!='\n')
    {
        is>>x;
        is>>y;
        defined = true;
    }

    is.ignore(INT_MAX,'\n');

    return;
}

/*-----Point::Set()-----

PURPOSE
Allows the setting of x and y

INPUT
xVal - Input x-value
yVal - Input y-value

OUTPUT
Point.x - The x-value of Point
Point.y - The y-value of Point

RETURN
void                                      */

void Point::Set(double xVal,double yVal)
{
    x = xVal;
    y = yVal;

    defined = true;
    return;
}

/*-----Point::Show()-----

PURPOSE
Displays the Point argument on the screen 
in (x,y) format

OUTPUT
x,y of point to stream

RETURN
void                                      */

void Point::Show(ostream &os)
{
    os<<"("<<x<<", "<<y<<")"<<std::endl;
}

/*----Overloaded IO operators----*/

istream &operator>>(istream &is, Point &p)
{
    p.Get(is);

    return is;
}

ostream & operator<<(ostream &os, Point &p)
{
    p.Show(os);

    return os;
}
