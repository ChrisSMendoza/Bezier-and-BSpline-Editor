#pragma once
#include <fstream>
using namespace std;

BCurve *beziers; //global arrays to hold the curves
BSpline *splines;
int bCount, sCount; //number of bezier curves and b splines

void normalize(Point *p)
{
	p->x *= (SCREEN_WIDTH - 1);
	p->y *= (SCREEN_WIDTH - 1);
}


void unnormalize(Point *p)
{
	p->x /= (SCREEN_WIDTH - 1);
	p->y /= (SCREEN_WIDTH - 1);
}


void read(char *filename)
{
	ifstream inf(filename);
	int numOfPoints = 0;
	Point point; //temp point to copy into curve control points

	inf >> bCount; //the number of bezier curves to be stored
	beziers = new BCurve[bCount];

	for (int i = 0; i < bCount; i++)
	{
		inf >> numOfPoints;

		for (int p = 0; p < numOfPoints; p++)
		{
			inf >> point.x >> point.y; //store coordinates
			normalize(&point);
			beziers[i].points->push_back(point); //add to control points
		}

		inf >> beziers[i].resolution; //get the number of resolution points
		beziers[i].setIncrement();
	}

	inf >> sCount; //the number of bsplines to be stored
	splines = new BSpline[sCount]; 

	for (int i = 0; i < sCount; i++)
	{
		inf >> numOfPoints;

		for (int p = 0; p < numOfPoints; p++)
		{
			inf >> point.x >> point.y; //add the points
			normalize(&point);
			splines[i].points->push_back(point);
		}
		//set the degree and the number of resolution points
		inf >> splines[i].k >> splines[i].resolution; 
		splines[i].setKnots(); //set the knots vector for the current spline
	}
}//read()

void write(char *filename)
{
	ofstream onf(filename);
	int numOfPoints = 0;
	onf << bCount << endl; //the number of bezier curves to be stored

	for (int i = 0; i < bCount; i++)
	{
		numOfPoints = beziers[i].points->size();
		onf << numOfPoints << endl;

		for (int p = 0; p < numOfPoints; p++)
		{
			unnormalize(&beziers[i].points->at(p));

			onf << beziers[i].points->at(p).x << " " //save the coordinates
				<< beziers[i].points->at(p).y << endl;
		}

		onf << beziers[i].resolution << endl; //save the number of resolution points
	}

	onf << sCount << endl; //the number of bsplines to be saved in file

	for (int i = 0; i < sCount; i++)
	{
		numOfPoints = splines[i].points->size();
		onf << numOfPoints << endl;

		for (int p = 0; p < numOfPoints; p++)
		{
			unnormalize(&splines[i].points->at(p));

			onf << splines[i].points->at(p).x << " " //save the coordinates
				<< splines[i].points->at(p).y << endl;
		}
		//save the degree and the number of resolution points
		onf << splines[i].k << " " << splines[i].resolution << endl;
	}
}//write()