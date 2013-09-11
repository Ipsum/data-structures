bool GetF(char *prompt, PwlFcn &f)
{
    /*Prompt for and read from the keyboard a list of (x, y) points defining a piecewise-linear function.
    prompt The prompt string.
    f The returned function definition.
    Return Value
false No function entered; the user supplied an empty input.
true A valid function was entered and stored in “f.”
*/
}
void ShowF(PwlFcn &f)
{
    /*Display the function defined in “f(x)” as a table of (x, y) pairs.
    f The function definition.*/
}

double Interpolate(PwlFcn &f, double x)
{
    /*Given a piecewise linear function “f,” and an x coordinate “x,” determine the value of f(x). Note that
the function defines only one cycle of the function, but that “x” may lie within any cycle.
Input Parameters
f The function from which from which f(x) is to be obtained.
x The value of the independent variable at which f(x) is to be obtained.
Return Value
The value of the function at “x” (i.e., f(x)).*/
}