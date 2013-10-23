/*-----Point.h-----
by: David Tyler
    16.322 Data Structures
    ECE Dept.
    UMASS Lowell

PURPOSE
Provides the interface to Point.cpp

CHANGES
10-02-13 --- Passed in for homework 2 credit
*/

#ifndef __point__
#define __point__

#include <iostream>
using namespace std;

//-----class definition-----//

// Class "Point" represents location of a point in x,y format. //

class Point
{
public:
    //Constructors
    Point() : defined(false) { }
    Point(double xVal,double yVal) : 
        x(xVal), y(yVal), defined(true) { }
    //Accessors
    double X() const; //Returns x
    double Y() const; //Returns y
    bool Defined() { return defined; } //Returns defined
    //Mutator
    void Set(double xVal,double yVal); //Sets x,y
    void Show(ostream &os=cout);
    void Get(istream &is=cin);
private:
    bool defined; //true if point exists
    double x;
    double y;
};

//io operators
istream & operator>>(istream &is, Point &p);
ostream & operator<<(ostream &os, Point &p);

#endif