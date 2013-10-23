/*-----Prog1.cpp-----

by: David Tyler
    16.322 Data Structures
    ECE Dept.
    UMASS Lowell

PURPOSE
Read in a piecewise linear function, interpolate requested # of points
over a range and display the interpolated points.

CHANGES
09-18-13 v0.0.1 --- Passed in for homework 1 credit

NOTES
The specs for this program used type double in a few places, but this didn't
really make sense since the output was expected to be ints, so I changed it
except when calculating interpolated x values because I needed to round them.
*/

#include <iostream>

using namespace std;

#include "Point.h"
#include "PwlFcn.h"

/*---------------main()---------------*/

void main()
{
    bool validFn; //Checks that user input was valid
    double start,end; //start and end points of the interpolated wave
    unsigned points; //number of points to interpolate

    PwlFcn funct; //Our user-inputted function
    Point pt; //An interpolated point

    cout<<"ENTER A FUNCTION DEFINITION:\n"<<endl;
    validFn = GetF("Enter the next point: ",funct);

    // Exit on invalid user inputted function
    if(!validFn)
    {
        cout<<"No valid function entered!"<<endl;
        return;
    }

    // Print out the function
    cout<<"\nHere is the function definition:"<<endl;
    ShowF(funct);

    cout<<"\nWhat is the start time? ";
    cin>>start;

    cout<<"\nWhat is the end time? ";
    cin>>end;

    cout<<"\nHow many points? ";
    cin>>points;

    // Interpolate and display the requested points
    cout<<"\nHere is the interpolated waveform:"<<endl;

    // Calculate the distance between interp points and use this as i 
    for( int i = (int)start;i<=end;i+=(int)(((end-start)/points) + 0.5) )
    {
        pt.x=i;
        pt.y=Interpolate(funct,pt.x);
        ShowPoint(pt);
    }

    //system("pause"); //commented out to avoid breaking grading scripts
}