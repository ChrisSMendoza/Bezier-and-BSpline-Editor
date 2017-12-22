#pragma once
#include <iostream>
#include <sstream>
#include <string>
#define BACKSPACE 8
#define ENTER 13
using namespace std;

string command = ""; 
int mainWindow;
char file[] = { "curves.txt" };

void key(unsigned char key, int x, int y)
{
	if(key != BACKSPACE)
		command += key; //add entered key to the overall command string

	if (key == ENTER)
	{
		stringstream stream(command);
		string type, option; //type of curve
		Point point; //temp point to be added into control points
		int id; //the curves index
		stream >> type >> id >> option;

		if (type == "x") //close window and save
		{
			glutDestroyWindow(mainWindow);
			write(file);
		}

		else if (type == "b") //bezier curve change
		{
			if (option == "r")
			{
				int res; stream >> res;
				beziers[id].changeResolution(res);
			}
			else if (option == "dp")
			{
				int index; stream >> index;
				beziers[id].deletePoint(index);
			}
			else if (option == "cp")
			{
				int index, x, y; stream >> index >> x >> y;
				beziers[id].changePoint(x, y, index);
			}
			else if (option == "ap") //add point
			{
				int index; stream >> index;
				stream >> point.x >> point.y;
				beziers[id].addPoint(point, index);
			}
		} //bezier curve changes

		else if (type == "s") //spline curve change
		{
			if (option == "r")
			{
				int res; stream >> res;
				splines[id].changeResolution(res);
			}
			else if (option == "dp")
			{
				int index; stream >> index;
				splines[id].deletePoint(index);
			}
			else if (option == "cp")
			{
				int index, x, y; stream >> index >> x >> y;
				splines[id].changePoint(x, y, index);
			}
			else if (option == "ap") //add point
			{
				int index; stream >> index;
				stream >> point.x >> point.y;
				splines[id].addPoint(point, index);
			}
			else if (option == "cd") //change degree
			{
				int order; stream >> order;
				splines[id].changeOrder(order);
			}
			else if (option == "ck") //change knot
			{
				int index; float newKnot;
				stream >> index >> newKnot;
				splines[id].changeKnot(newKnot, index);
			}
		} //spline changes
		clearBuffer();
		glutPostRedisplay();
		command = ""; //empty the string
	}//enter key pressed

	if (key == BACKSPACE)
	{
		if (command.size() > 0)
			command.pop_back();
	}
	cout << command << endl;
}
