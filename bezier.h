#pragma once
using namespace std;

class BCurve
{
public:
	vector<Point> *points;		//holds the control point
	float increment;		//change in @t as it's passed into bezier algorithm
	int resolution;			//number of resolution points

	BCurve();
	
	void changePoint(int x, int y, short index);
	void addPoint(Point point, short index);
	void changeResolution(int res);
	void deletePoint(short index);
	void setIncrement();
	void draw();
};

BCurve::BCurve()
{
	points = new vector<Point>;
}


void BCurve::addPoint(Point point, short index)
{
	points->insert(points->begin() + index, point);
	setIncrement(); //update increment
}


void BCurve::changePoint(int x, int y, short index)
{
	points->at(index).x = x;
	points->at(index).y = y;
}//changePoint()


void BCurve::changeResolution(int res)
{
	resolution = res;
	setIncrement();
}//changeResolution()


void BCurve::deletePoint(short index)
{
	points->erase(points->begin() + index); //erase the point at the index
	setIncrement(); //update the increment
}//deletePoint()


void BCurve::draw()
{
	vector<Point>draw; //holds the points on the curve to be drawn
	Point point; //current calculated point on the curve
	float t = 0; //t within [0, 1]
	int i;

	for (i = 0; i <= resolution; i++) //get the points on the curve
	{
		casteljau(points, &point, t); //use control points to get each point on the curve
		draw.push_back(point); //add each point to draw later
		t += increment; //casteljau algorithm uses this value in each calculation
	}

	for (i = 0; i < (points->size() - 1); i++) //draw control polygon
		bresMakeLine(points->at(i).x, points->at(i).y,
			points->at(i + 1).x, points->at(i + 1).y, buffer, true);

	for (i = 0; i < (draw.size() - 1); i++) //draw curve
		bresMakeLine(draw.at(i).x, draw.at(i).y,
			draw.at(i + 1).x, draw.at(i + 1).y, buffer);
}//draw()


void BCurve::setIncrement()
{
	increment = 1 / float(resolution);
}
