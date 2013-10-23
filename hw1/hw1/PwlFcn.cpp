/*-----PwlFcn.cpp-----
by: David Tyler
    16.322 Data Structures
    ECE Dept.
    UMASS Lowell

PURPOSE
This file contains functions related to the PwlFcn struct

CHANGES
09-18-13 v0.0.1 --- Passed in for homework 1 credit
*/

#include <cstdlib> // For quicksort
#include "PwlFcn.h"

/*-----GetF()-----

PURPOSE
Prompt for and read in a set of points from the keyboard
as a piecewise linear function

INPUT
prompt -- The string to prompt the user with

OUTPUT
f -- the piecewise linear function

RETURN
true if pwlfcn is valid,
false otherwise.                               */

bool GetF(char *prompt, PwlFcn &f)
{
    bool run=true;
    Point pt;

    f.numPts=0;

    while(run)
    {
        run = GetPoint(prompt,pt);

        if( run && (f.numPts<MaxPts) )
        {
            f.pt[f.numPts].x = pt.x;
            f.pt[f.numPts].y = pt.y;

            f.numPts++;
        }

        if(f.numPts>=MaxPts) //If we exceed max number of points, stop getting points
        {
            f.numPts = MaxPts;

            //Professor told us input would be in ascending order, but lets sort anyways (quickly!)
            qsort(f.pt,f.numPts,sizeof(double),Compare);

            return true;
        }
    }

    //Professor told us input would be in ascending order, but lets sort anyways (quickly!)
    qsort(f.pt,f.numPts,sizeof(double),Compare);

    return (f.numPts>=2); //return false if we don't have 2 points, else return true    
}

/*-----ShowF()-----

PURPOSE
Print a given PwlFcn to the screen

INPUT
f -- The PwlFcn to print

RETURN
void                             */

void ShowF(PwlFcn &f)
{
    for(unsigned i=0;i<f.numPts;i++)
    {
        ShowPoint(f.pt[i]);
    }
}

/*-----Interpolate()-----

PURPOSE
Interpolate a y-value based on a piecewise linear
function and a x-value

INPUT
f -- A piecewise linear function.
x -- The x-value of the interpolated point

RETURN
int -- The calculated y-value of the interpolated point. */

int Interpolate(PwlFcn &f, int x)
{
    Point high;
    Point low;

    high.x = 0;
    low.x = 0;

    while(x<0)
    {
        x+=f.pt[f.numPts-1].x; //A terrible algo to handle negative x coords
    }

    x = x % (f.pt[f.numPts-1].x); //Account for cycles past the first cycle by taking modulus

    //Since the point array is sorted by x ascending, it is easy to find the sandwich points. 
    //O(n) is good enough for now!
    for(unsigned i=0;i<f.numPts;i++)
    {
        if(x>f.pt[i].x)
        {
            low = f.pt[i];
        }
        if(x<=f.pt[i].x)
        {
            high = f.pt[i];
            break;
        }
    }

    //This function doesn't supply a way to return an error status so lets return 0,0 on error
    if(high.x <= low.x)
    {
        return 0;
    }

    //Compute linear function y=mx+b
    int m = (high.y-low.y)/(high.x-low.x); //slope
    int b = (high.y)-(m*high.x); //offset

    return (m*x+b); //Compute and return y
}

/*-----overloaded operators-----

PURPOSE
Enables the easy sorting of an array of Points
using qsort(). 
Compares the x-values of type "Point".

OPERATIONS
Point<Point
Point==Point
Point>Point
                                                  */

bool operator<(Point p1, Point p2)
{
    return p1.x<p2.x;
}

bool operator==(Point p1, Point p2)
{
    return p1.x==p2.x;
}

bool operator>(Point p1, Point p2)
{
    return p1.x>p2.x;
}

/*-----Compare()-----

PURPOSE
Provides a way for qsort() to compare 2 values 
of type Point

INPUT
a -- The value of type Point to the left
b -- The value of type Point to the right

RETURN
int -- -1 if the x-value of a < the x-value of b
        0 if the x-value of a == the x-value of b
        1 if the x-value of a > the x-value of b
                                                 */

int Compare (const void * a, const void * b)
{
  if ( *(Point*)a <  *(Point*)b ) return -1;
  if ( *(Point*)a == *(Point*)b ) return 0;
  if ( *(Point*)a >  *(Point*)b ) return 1;
  return 0; //compiler complains without obvious default branch
}