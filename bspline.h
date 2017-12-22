#pragma once
#define ADJUST .0001 //subtracted from upper bound to ensure within knot domain
using namespace std;

class BSpline
{
public:
	vector<Point> *points; 	//control points
	vector<float> *knots; 	//knot sequence/vector
	float increment; 		//the amount 'u' changes when passed into de boor
	int resolution;			//number of points on the curve to calculate
	int k; 					//degree of the polynomial

	BSpline();
	void changeKnot(float newKnotValue, short index);
	void changePoint(int x, int y, short index);
	void addPoint(Point point, short index);
	void changeResolution(int res);
	void deletePoint(short index);
	void changeOrder(int order);
	void addKnots(int amount);
	void setIncrement();
	void setKnots();
	void draw();
};

BSpline::BSpline()
{
	points = new vector<Point>;
}


void BSpline::addKnots(int amount) //adds passed in amount of knots at the end
{
	int newKnotValue = round(knots->back()); //start at the last knot value

	for (int i = 0; i < amount; i++) //add 1 to each new knot
		knots->push_back(++newKnotValue);
}


void BSpline::addPoint(Point point, short index)
{
	points->insert(points->begin() + index, point);
	addKnots(1); //add a knot at the end
	setIncrement(); //update increment
}


void BSpline::changeKnot(float newKnotValue, short index)
{
	knots->at(index) = newKnotValue;
	//knot within the domain is changed then the increment is altered too
	setIncrement();  
}


void BSpline::changeOrder(int order)
{
	if (k < order) //increasing the order, add knots
	{
		addKnots(order - k);
		k = order; //update the order
		setIncrement(); //increment depends on k
	}
	else if (k > order) //decreasing the order, remove knots
	{
		for (int i = 0; i < k - order; i++) //delete the last knots
			knots->pop_back();

		k = order; //update both k and increment
		setIncrement(); 
	}
}


void BSpline::changePoint(int x, int y, short index)
{
	points->at(index).x = x;
	points->at(index).y = y;
}//changePoint()


void BSpline::changeResolution(int res)
{
	resolution = res;
	setIncrement();
}


void BSpline::deletePoint(short index)
{
	points->erase(points->begin() + index); //erase the point at the index
	knots->pop_back(); //get rid of the last knot
	setIncrement(); //update the increment
}//deletePoint()


void BSpline::draw()
{
	float u = knots->at(k - 1); //u starts at the beginning of the knot domain
	vector<Point>draw; //holds the points on the curve to be drawn
	Point point; //current calculated point on the curve
	int i;

	for (i = 0; i <= resolution; i++) //get the points on the curve
	{
		deBoor(points, knots, &point, k, u);
		draw.push_back(point);
		u += increment;
		//to ensure u is always below the domain
		if (u > knots->at(points->size())) 
			u = knots->at(points->size()) - ADJUST;
	}

	for (i = 0; i < (points->size() - 1); i++) //draw control polygon
		bresMakeLine(points->at(i).x, points->at(i).y,
			points->at(i + 1).x, points->at(i + 1).y, buffer, true);

	for (i = 0; i < (draw.size() - 1); i++) //draw curve
		bresMakeLine(draw.at(i).x, draw.at(i).y,
			draw.at(i + 1).x, draw.at(i + 1).y, buffer);
}//draw()


 //call when knot vector or resolution is set or changed
void BSpline::setIncrement() 
{
	//total domain space divided by the number of resolution points
	//(U_n+1 - U_k-1) / number of resolution points
	increment = (knots->at(points->size()) - knots->at(k - 1)) / resolution;
}


void BSpline::setKnots()
{
	knots = new vector<float>;
	//knot vector is initially [0.0, 1.0, ... , n+k]
	for (int i = 0; i < points->size() + k; i++)
		knots->push_back(float(i));

	setIncrement();
}//setKnots()
