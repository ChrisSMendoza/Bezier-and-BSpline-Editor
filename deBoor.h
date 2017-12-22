#pragma once
#include "point.h"
using namespace std;
//include vector in main

void deBoor(vector<Point> *points, vector<float> *knots, Point *pt, int k,
	float u)
{
	Point **matrix = new Point*[points->size()];
	int x = 0, y = 0, firstKnot = 0; //find I such that u within [u_I, u_I+1)

	for (int i = 0; i < points->size(); i++)//allocate each row
		matrix[i] = new Point[points->size()];
	
	//find the knots where u lies in between
	for (int i = 0; i < knots->size(); i++) //domain [U_k-1,U_n+1]
	{
		if (knots->at(i) <= u && u < knots->at(i + 1))
			break;
		else//not in that interval, u must be one ahead in knots
			firstKnot++;
	}
	//first column contains the control points needed to locate c(u)
	for (int i = 0; i < points->size(); i++)
		matrix[i][0] = points->at(i);


	for (int j = 1; j < k; j++) //loop through from generation 1 to (k-1)
	{
		for (int i = firstKnot - (k - 1); i <= (firstKnot - j); i++)
		{
			x = (knots->at(i + k) - u) * matrix[i][j - 1].x /
				(knots->at(i + k) - knots->at(i + j)) +

				(u - knots->at(i + j)) * matrix[i + 1][j - 1].x /
				(knots->at(i + k) - knots->at(i + j));

			y = (knots->at(i + k) - u) * matrix[i][j - 1].y /
				(knots->at(i + k) - knots->at(i + j)) +

				(u - knots->at(i + j)) * matrix[i + 1][j - 1].y /
				(knots->at(i + k) - knots->at(i + j));

			matrix[i][j] = Point(x, y);
		}
	}
	(*pt) = matrix[firstKnot - (k - 1)][k - 1];
	deleteMatrix(matrix, k); //function in casteljau
}//deBoor()