1)
Chris Mendoza
912216791
csmendoza@ucdavis.edu

2)
g++ -o p4.out main.cpp -lglut -lGL

Name of executable: p4.out

3.)
starting file is "curves.txt"

the commands are as follows:

[type of curve] [id] [option] [other numbers depending on option]

type of curve:
b - bezier
s - bspline

id:
0 or 1 (since there's 2 curves of each)
//from bottom to top:
//the 1st and 3rd curve are beziers, id = 0,1 respectively
//and the 2nd and 4th are b-splines, id = 0,1 respectively

option:
r - change resolution, followed by: [resolution amount]

dp - delete point, followed by: [index]

cp - change point, followed by: [index] [x-coordinate] [y-coordinate]

ap - add point, followed by: [index] [x-coordinate] [y-coordinate]

ck - change knot, followed by: [index] [knot value]
//the knot value is a float, and it's assumed the user will enter a valid value
//the knot vector is initially [0, 1, ..., n+k]
//so if index entered is 2 then the new knot value can between: (1.0, 3.0)

cd - change degree, followed by: [new k value]

/* To exit and save the program the user must type 'x' and enter */
 
NOTE: As the user types, the command will be continuously printed in the terminal
      with the option to use the backspace to fix the command.

---EXAMPLES---
b 0 r 100
b 0 dp index
b 0 cp index 45 60
b 0 ap index 34 90

s 0 r 100
s 0 dp index
s 0 cp index 45 60
s 0 ap index 34 90
s 0 ck index knotValue
s 0 cd order

x

-----STYLE OF INPUT FILE-----
(coordinate values must be between [0,1.0])

2//number of bezier curves
4 //number of control points in the control polygon
0 0.133556 //x and y world coordinates
0.166945 0.033389
0.250417 0.033389
0.417362 0.133556
50 //number of resolution points
4 //number of control points
0.450751 0.500835
0.48414 0.601002
0.567613 0.617696
0.66778 0.500835
50
2 //number of b spline curves
4 //number of control points
0.033389 0.283806
0.33389 0.350584
0.434057 0.250417
0.66778 0.417362
3 50 //k(degree, order) and number of resolution points
6
0.100167 0.96828
0.233723 0.701169
0.400668 0.701169
0.534224 0.96828
0.701169 0.96828
0.934891 0.651085
3 50