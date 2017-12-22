#pragma once

class Point
{
public:
	float x;
	float y;

	Point(float xa, float ya)//(int xa, int ya)
	{
		x = xa;
		y = ya;
	}
	Point()
	{
		x = 0.0; y = 0.0;//x = 0; y = 0;
	}
	Point(const Point &p)
	{
		x = p.x;
		y = p.y;
	}
	bool operator==(const Point &p)
	{
		return ((x == p.x) && (y == p.y));
	}
};