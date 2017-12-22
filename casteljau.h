#pragma once
#include "point.h"
using namespace std;
//include vector in main

void deleteMatrix(Point **points, int vSize)
{
	for (int i = 0; i < vSize; i++)
		delete points[i];

	delete points;
}

//takes in the control points and the desired location on the curves
void casteljau(vector<Point> *vector, Point* point, float t)
{
	float x = 0.0, y = 0.0; //floats store the new coordinate values
	//initialize first column of pointers
	Point **points = new Point*[vector->size()]; 

	for (int i = 0; i < vector->size(); i++) //allocate each row
		points[i] = new Point[vector->size()];

	//first column contains the control points
	for (int i = 0; i < vector->size(); i++)
		points[i][0] = vector->at(i);
	
	//loop through points, calculate next points, store them and use those
	for(int j = 1; j < vector->size(); j++)
		for (int i = 0; i < (vector->size() - j); i++)
		{
			x = (1 - t) * (points[i][j - 1].x) + t * (points[i + 1][j - 1].x);
			y = (1 - t) * (points[i][j - 1].y) + t * (points[i + 1][j - 1].y);
			points[i][j] = Point(x, y);
		}

	(*point) = points[0][vector->size() - 1]; //copy desired point
	deleteMatrix(points, vector->size());
}//casteljua()