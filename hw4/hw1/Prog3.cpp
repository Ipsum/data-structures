/*--------------- P r o g 3 . c p p ---------------

by:   David Tyler
      16.322 Data Structures
      ECE Department
      UMASS Lowell

PURPOSE
This is an interactive arbitrary function generator. A piecewise linear function
defining one cycle of a periodic waveform may be entered from either the keyboard
or from a text file. Then, upon command, the program will generate the periodic
waveform from tStart to tEnd using numPts equally spaced points.

DEMONSTRATES
Doubly Linked Lists

CHANGES
09-30-2013 gpc -  Distribute for 16.322    
10-09-2013 - finished interp, del, and print for hw3
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

#include "Point.h"
#include "DblLinkedList.h"

//----- c o n s t a n t    d e f i n i t i o n s -----

// Command Letters
const char BackwardCmd ='B';  // Move the current item back one entry.
const char ClearCmd =   'C';  // Make the pwlFcn empty
const char DeleteCmd =  'D';  // Delete the current point from the pwlFcn.
const char ForwardCmd = 'F';  // Move the current item forward one entry.
const char GenerateCmd ='G';  // Generate the waveform
const char InsertCmd =  'I';  // Insert a new point in the pwlFcn.
const char OpenCmd =    'O';  // Read in a pwlFcn from a file.
const char PrintCmd =   'P';  // Show the pwlFcn on the display.
const char QuitCmd =    'Q';  // Quit
const char RewindCmd =  'R';  // Rewind the current point to the first point in the function definition.
const char SaveAsCmd =  'S';  // Write the pwlFcn to a file.
const char ExecuteCmd = 'X';  // Execute command file.

//----- f u n c t i o n    p r o t o t y p e s -----

void DoExecute(const string cmdLine, DblLinkedList &pwlFcn);
string GetCmd(istream &cmdStream, DblLinkedList &pwlFcn);
void InsertPoint(const string cmdLine, DblLinkedList &pwlFcn);
void ClearPwlFcn(DblLinkedList &pwlFcn);
void Generate(string cmdLine, DblLinkedList &pwlFcn);
string GetFileName(string cmdLine);
void ReadPwlFcnFile(string cmdLine, DblLinkedList &pwlFcn);
void WritePwlFcnFile(string cmdLine, DblLinkedList &pwlFcn);
void DisplayPwlFcn(DblLinkedList &pwlFcn);
void Execute(istream &cmdStream, DblLinkedList &pwlFcn);
double Interpolate(DblLinkedList &pwlFcn, double x);

//--------------- m a i n ( ) ---------------

int main()
{
  DblLinkedList  pwlFcn;            // The pwlFcn list

  // Execute commands from the stream cin.
  Execute(cin, pwlFcn);

  return 0;
}

/*--------------- E x e c u t e ( ) ---------------

PURPOSE
Execute a command stream, either from cin of
from a command file

INPUT PARAMETERS
cmdStream --  the stream from which commands are to be read
pwlFcn     -- the pwlFcn list.
*/
void Execute(istream &cmdStream, DblLinkedList &pwlFcn)
{
  string cmdLine; // The current command line

  // Repeatedly get a command from the keyboard and
  // execute it.
  do
    {
    cmdLine = GetCmd(cmdStream, pwlFcn);

    if (cmdLine.length() != 0)
      {
      switch (toupper(cmdLine[0]))
        {
        // Execute a command file.
        case ExecuteCmd:
          DoExecute(cmdLine, pwlFcn);
          break;
        // Determine which command to execute.
        case InsertCmd:        // Insert a new point.
          InsertPoint(cmdLine, pwlFcn);
          break;
        case ClearCmd:      // Clear the pwlFcn.
          ClearPwlFcn(pwlFcn);
          break;
        case DeleteCmd:     // Delete the current point.
          if (!pwlFcn.AtEnd())
            pwlFcn.DeleteItem();
          if (pwlFcn.Empty())
            cout << "The pwlFcn is empty." << endl;
          break;
        case PrintCmd:       // Display the pwlFcn.
          DisplayPwlFcn(pwlFcn);
          break;
        case OpenCmd:       // Read in a pwlFcn file.
          ReadPwlFcnFile(cmdLine, pwlFcn);
          break;
        case SaveAsCmd:      // Write out a pwlFcn file.
          WritePwlFcnFile(cmdLine, pwlFcn);
          break;
        case ForwardCmd:       // Advance to the next point.
          if (!pwlFcn.AtEnd())
            pwlFcn.Forward();
          if (pwlFcn.AtEnd())
            cout << "The pwlFcn is at the end." << endl;
          break;
        case BackwardCmd:       // Go back to the previous point.
          pwlFcn.Backward();
          break;
        case RewindCmd:
          pwlFcn.Rewind();
          break;
        case GenerateCmd:     // Generate waveform.
          Generate(cmdLine, pwlFcn);
          break;
        case QuitCmd:       // Terminate execution.
          break;
        default:            // Bad command
          cout << "*** Error: Unknown Command" << endl;
          break;
        }
      }
    }
  while (toupper(cmdLine[0]) != QuitCmd);
}

/*--------------- D o E x c u t e ( ) ---------------

PURPOSE
Get a command file name and execute the file.

INPUT PARAMETERS
cmdLine -- the execute command command line.
pwlFcn   -- the pwlFcn list.
*/
void DoExecute(const string cmdLine, DblLinkedList & pwlFcn)
{
  // Get the file name from the execute command.
  string cmdFileName = GetFileName(cmdLine);

  // If empty, cancel command.
  if (cmdFileName.length() == 0)
    return;

  // Associate a command stream with the command file.
  ifstream cmdStream(cmdFileName.c_str());

  // If the file exists, execute it; otherwise give
  // an error message.
  if (cmdStream.is_open())
    Execute(cmdStream, pwlFcn);
  else
    cout << "***ERROR: No such file " << cmdFileName << endl;
}

/*--------------- G e t C m d ( ) ---------------

PURPOSE
Accept a command from the keyboard.

INPUT PARAMETERS
cmdStream   -- the stream from which commands are to be read
pwlFcn      -- the pwlFcn list.

RETURN VALUE
The command letter.
*/
string GetCmd(istream &cmdStream, DblLinkedList &pwlFcn)
{
  // Display the current point before accepting each command.
  if (!pwlFcn.AtEnd() && cmdStream == cin)
    {
    // Display the current item.
    cout << "\nCURRENT ITEM" << endl;
  
    cout << pwlFcn.CurrentItem();

    cout << endl;
    }

  // Prompt for a new command.
  cout << "\n>";

  string cmdLine;    // Command line

  // Quit at end of a command file.
  if (cmdStream.peek() == EOF)
    {
    cmdLine = QuitCmd;

    return cmdLine;
    }

  // Get the next command and return it.
  getline(cmdStream, cmdLine);

  if (cmdStream != cin)
    cout << cmdLine << endl;

  return cmdLine;
}

/*--------------- I n s e r t P o i n t ( ) ---------------

PURPOSE
Insert a new point in the pwlFcn before the current point.

INPUT PARAMETERS
cmdLine -- the execute command command line.
pwlFcn  -- the pwlFcn list.
*/
void InsertPoint(string cmdLine, DblLinkedList &pwlFcn)
{
  const unsigned  MinCmdSize = 2; // To check for an empty insert command

  Point             point;                // New pwlFcn point
  
  istringstream     cmdStream(cmdLine.erase(0,1));   // Command stream

  // Ignore if empty add parameters.
  if (cmdLine.length() < MinCmdSize)
    return;
      
  // Read the new point and insert it into the pwlFcn.
  cmdStream >> point;

  pwlFcn.InsertItem(point);
}


/*--------------- G e n e r a t e ( ) ---------------

PURPOSE
Generate the periodic function.

INPUT PARAMETERS
cmdLine -- the execute command command line.
pwlFcn  -- the pwlFcn list.
*/
void Generate(string cmdLine, DblLinkedList &pwlFcn)
{
   // Make sure the function is defined.
   if (pwlFcn.Empty())
      {
      cout << "The pwlFcn is empty." << endl;
      return;
      }

   Point testPoint;   // The point to test

   const unsigned  MinCmdSize = 2; // To check for an empty test command

   istringstream   cmdStream(cmdLine.erase(0,1)); // Command stream

   // Ignore if empty test parameters.
   if (cmdLine.length() < MinCmdSize)
      return;
      
   // Read the sample spacing and number of repetitions.

   double tStart;
   double tEnd;
   unsigned numPts;

   cmdStream >> tStart >> tEnd >> numPts;
   
   double dt = (tEnd - tStart) / (numPts - 1);

   // Generate the waveform starting at t = 0.
   double t = tStart;
   
   pwlFcn.Rewind();
   
   for (unsigned i=0; i<numPts; i++)
      {
      Point pt = Point(t, Interpolate(pwlFcn, t));
      
      cout << pt << endl;
      
      t += dt;
      }
   
   pwlFcn.Rewind();
}  

/*--------------- G e t F i l e N a m e ( ) ---------------

PURPOSE
Read a file name from the keyboard.

INPUT PARAMETERS
cmdLine -- the execute command command line.

RETURN VALUE
the file name or empty string if cancelled.
*/
string GetFileName(string cmdLine)
{
  string        fileName;           // The file name
  istringstream cmdStream(cmdLine.erase(0,1)); // Make a command stream.

  // Ignore empty file name
  if (cmdLine.length() == 0)
    return "";

  // Advance over whitespace.
  while (isspace(cmdStream.peek()))
    cmdStream.get();

  // Get the file name and return it.
  getline(cmdStream, fileName);

  return fileName;
}

/*--------------- R e a d P w l F c n F i l e ( ) ---------------

PURPOSE
Read in a pwlFcn file.

INPUT PARAMETERS
cmdLine -- the execute command command line.
pwlFcn  -- the pwlFcn list.
*/
void ReadPwlFcnFile(string cmdLine, DblLinkedList &pwlFcn)
{
  ifstream  pwlFcnStream;  // The input stream
  string    pwlFcnFile;    // The input file name

  // Ask for the file name and then open the file.
  pwlFcnFile = GetFileName(cmdLine);
  if (pwlFcnFile.length() == 0)
    return;

  pwlFcnStream.open(pwlFcnFile.c_str());
  if (!pwlFcnStream.is_open())
    {
    cout << "*** ERROR: No such file " << pwlFcnFile << endl;
    return;
    }

  // Read in the entire pwlFcn file.
  while (pwlFcnStream.peek() != EOF)
    {
    Point point; // Next input point

    pwlFcnStream >> point;
    pwlFcn.InsertItem(point);
    }
  pwlFcnStream.close();
   
  pwlFcn.Rewind();
}


/*--------------- W r i t e P w l F c n F i l e ( ) ---------------

PURPOSE
Write out a pwlFcn file.

INPUT PARAMETERS
cmdLine -- the execute command command line.
pwlFcn  -- the pwlFcn list.
*/
void WritePwlFcnFile(string cmdLine, DblLinkedList &pwlFcn)
{
  ofstream  pwlFcnStream;  // The output stream
  string    pwlFcnFile;    // The output file name

  // Ask for the file name and then open the file.
  pwlFcnFile = GetFileName(cmdLine);

  if (pwlFcnFile.length() == 0)
    return;

  pwlFcnStream.open(pwlFcnFile.c_str());

  if (!pwlFcnStream.is_open())
    {
    cout << "*** ERROR: Failed to open file " << pwlFcnFile << endl;
    return;
    }

  // Write out the entire pwlFcn.
  pwlFcn.Rewind();
  while (!pwlFcn.AtEnd())
    {
    pwlFcnStream << pwlFcn.CurrentItem().X() <<" " << pwlFcn.CurrentItem().Y() << endl;
    pwlFcn.Forward();
    }
      
  pwlFcnStream.close();
   
  pwlFcn.Rewind();
}

/*--------------- D i s p l a y P w l F c n ( ) ---------------

PURPOSE
Display a pwlFcn from beginning to end.

INPUT PARAMETERS
pwlFcn  -- the pwlFcn to be displayed.
*/
void DisplayPwlFcn(DblLinkedList &pwlFcn)
{
    double x;
    double y;

    //Check if empty
    if(pwlFcn.Empty())
    {
        cout<<"The pwlFcn is empty."<<endl;
        return;
    }

    //Start at the beginning and print everything
    pwlFcn.Rewind();
    while(!pwlFcn.AtEnd())
    {
        x = pwlFcn.CurrentItem().X();
        y = pwlFcn.CurrentItem().Y();
        cout<<"("<<x<<","<<y<<")"<<endl;
        pwlFcn.Forward();
    }
    //Reset to beginning
    pwlFcn.Rewind();
}

/*--------------- C l e a r P w l F c n ( ) ---------------

PURPOSE
Make the pwlFcn empty.

INPUT PARAMETERS
pwlFcn  -- the pwlFcn list.
*/
void ClearPwlFcn(DblLinkedList &pwlFcn)
{
    pwlFcn.Rewind();
    while(!pwlFcn.Empty())
    {
        pwlFcn.DeleteItem();
    }
}

/*--------------- I n t e r p o l a t e ( ) ---------------

PURPOSE
Determine the value of the waveform at time t by linear interpolation.

INPUT PARAMETERS
pwlFcn  -- the pwlFcn list
t       -- the time at which the waveform value is to be obtained
*/
double Interpolate(DblLinkedList &pwlFcn, double t)
{
    double lowerBound;
    double upperBound;

    Point low;
    Point high;

    lowerBound = pwlFcn.FirstItem().X();
    upperBound = pwlFcn.LastItem().X();

    //modulate t to be in the period of the wave
    while(t<lowerBound)
    {
        t+=upperBound;
    }
    while(t>upperBound)
    {
        t-=upperBound;
    }
    t=fmod(t,upperBound);

    //find the upper and lower points to use to interp
    pwlFcn.Rewind();
    while(!pwlFcn.AtEnd())
    {
        if(t>pwlFcn.CurrentItem().X())
        {
            low = pwlFcn.CurrentItem();
        }
        else
        {
            high = pwlFcn.CurrentItem();
            break;
        }
        pwlFcn.Forward();
    }

    //calculate line
    double m = (high.Y()-low.Y())/(high.X()-low.X()); //slope
    double b = (high.Y())-(m*high.X()); //offset

    return (m*t+b); //Compute and return y
}
