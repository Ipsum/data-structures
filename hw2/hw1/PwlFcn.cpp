/*-----PwlFcn.cpp-----
by: David Tyler
    16.322 Data Structures
    ECE Dept.
    UMASS Lowell

PURPOSE
This file contains functions related to the PwlFcn class

CHANGES
10-02-13 --- Passed in for homework 2 credit
*/

#include <cstdlib> // For quicksort
#include "PwlFcn.h"

/*-----Get()-----

PURPOSE
Prompt for and read in a set of points from the keyboard
as a piecewise linear function

INPUT
is -- The input stream

OUTPUT
PwlFcn -- the piecewise linear function

RETURN
true if pwlfcn is valid,
false otherwise.                               */

bool PwlFcn::Get(istream &is)
{
    Point p;
    numPts=0;

    cout<<"Enter first point: ";
    do {

        p.Get(is);
        cout<<endl;
        if( p.Defined() && (numPts<MaxPts) )
        {
            pt[numPts].Set(p.X(),p.Y());

            numPts++;

            cout<<"Enter next point: ";
        }

        if(numPts>=MaxPts) //If we exceed max number of points, stop getting points
        {
            numPts = MaxPts;

            //Professor told us input would be in ascending order, but lets sort anyways
            //qsort(pt,numPts,sizeof(double),Compare);

            return true;
        }
    } while(p.Defined());

    //Professor told us input would be in ascending order, but lets sort anyways
    //qsort(pt,numPts,sizeof(double),Compare);

    defined = (numPts>=2); //return false if we don't have 2 points, else return true 
    
    return defined;  
}

/*-----ShowF()-----

PURPOSE
Print a given PwlFcn to the screen

INPUT
os -- The output stream

RETURN
void                             */

void PwlFcn::Show(ostream &os)
{
    for(unsigned i=0;i<numPts;i++)
    {
        pt[i].Show(os);
    }
}

/*-----Interpolate()-----

PURPOSE
Interpolate a y-value based on a piecewise linear
function and a x-value

INPUT
x -- The x-value of the interpolated point

RETURN
double -- The calculated y-value of the interpolated point. */

double PwlFcn::Interpolate(double x)
{
    Point high(0,0);
    Point low(0,0);

    while(x<pt[0].X())
    {
        x+=pt[numPts-1].X(); //A terrible algo to handle negative x coords
    }
    while(x>pt[numPts-1].X())
    {
        x-=pt[numPts-1].X();
    }
    x = fmod(x,pt[numPts-1].X()); //Account for cycles past the first cycle 
                                  //by taking modulus

    //Since the point array is sorted by x ascending, 
    //it is easy to find the sandwich points. 
    //O(n) is good enough for now!
    for(unsigned i=0;i<numPts;i++)
    {
        if(x>pt[i].X())
        {
            low = pt[i];
        }
        if(x<=pt[i].X())
        {
            high = pt[i];
            break;
        }
    }

    //This function doesn't supply a way to return an error status
    //so lets return 0,0 on error
    if(high.X() <= low.X())
    {
        return 0;
    }

    //Compute linear function y=mx+b
    double m = (high.Y()-low.Y())/(high.X()-low.X()); //slope
    double b = (high.Y())-(m*high.X()); //offset

    return (m*x+b); //Compute and return y
}

/*-----overloaded member operators-----

PURPOSE
Make it easier to append points to PwlFcn

OPERATIONS
PwlFcn=PwlFcn+Point                             */

PwlFcn PwlFcn::operator+(Point p)
{
    PwlFcn temp;

    temp.defined = defined;
    temp.numPts = numPts;
    for(unsigned i=0;i<temp.numPts;i++)
    {
        temp.pt[i] = pt[i];
    }

    if(numPts<MaxPts)
    {
        temp.pt[temp.numPts].Set(p.X(),p.Y());
        temp.numPts++;
    }

    return temp;
}
    

       
/*-----overloaded IO operators-----

PURPOSE
Makes doing io on a whole function easier

OPERATIONS
ostream<<PwlFcn
istream>>PwlFcn                                  */

ostream & operator<<(ostream &os,PwlFcn &f)
{

    f.Show(os);

    return os;
}

istream & operator>>(istream &is,PwlFcn &f)
{
    f.Get(is);

    return is;
}

/*-----overloaded comparison operators-----

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
    return p1.X()<p2.X();
}

bool operator==(Point p1, Point p2)
{
    return p1.X()==p2.X();
}

bool operator>(Point p1, Point p2)
{
    return p1.X()>p2.X();
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
  return 0; //compiler complains without default branch
}