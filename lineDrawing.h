#pragma once
#include <cmath>
#define FLOATS_PER_PIX 3
#define SCREEN_WIDTH 600
#define R 0
#define G 1
#define B 2

float *buffer; //main window screen buffer
int bufferSize = SCREEN_WIDTH * SCREEN_WIDTH * FLOATS_PER_PIX;

void clearBuffer() //clears buffer after changes are made to the drawings
{
	//set every pixel buffer value to black
	for (int i = 0; i < bufferSize; i++)
	{
		buffer[i] = 0.0;
	}
}
//bool red = false removed, declared in raster that way
void makePix(int x, int y, float* buffer, bool red)
{
	int pos = (y * SCREEN_WIDTH + x) * FLOATS_PER_PIX;
	buffer[pos] = 1.0;

	if (!red)
	{
		buffer[pos + 1] = 1.0;
		buffer[pos + 2] = 1.0;
	}
}


void makePix(int x, int y, float *rgbs, float *buffer)
{
	int pos = (y * SCREEN_WIDTH + x) * FLOATS_PER_PIX;

	buffer[pos] = rgbs[R];
	buffer[pos + 1] = rgbs[G];
	buffer[pos + 2] = rgbs[B];
}


void vertical(int ya, int yb, int x, float* buf, bool red) //vertical line
{
	for (int y = ya; y <= yb; y++) //up y axis
		makePix(x, y, buf, red); //same x value
}


void horizontal(int xa, int xb, int y, float *buf, bool red) //horizontal line
{
	for (int x = xa; x <= xb; x++) //right to left on x axis
		makePix(x, y, buf, red); //same y value
}

//where slope is 1 or -1
void diagonal(int xa, int ya, int xb, int yb, float *buf, bool red)
{
	int start = xa, end = xb, incDec = 1, y = ya; //positive slope

	if (xa < xb && ya > yb) //negative slope, (xa,ya) in upper left
	{
		incDec = -1;
	}
	else if (xb < xa) //(xb,yb) comes before (xa,ya)
	{
		start = xb;
		end = xa;
		y = yb;
		if (yb > ya) //negative slope, (xb,yb) in upper left
			incDec = -1;
	}

	for (int x = start; x <= end; x++)
	{
		makePix(x, y, buf, red);
		y += incDec;
	}
}


void bresSteepLine(int xa, int ya, int xb, int yb, float *buf, bool red)
{
	int dx = abs(xa - xb), dy = abs(ya - yb);
	int p = 2 * dy - dx;
	int twoDy = 2 * dx, twoDyDx = 2 * (dx - dy);
	int x = xa, y = ya, yEnd = yb; //for (xa,ya) lower than (xb, yb)
	int incDec = 1; //adds 1 or (-1) depending on y values

	if (ya > yb && xa < xb) //negative slope
	{
		y = yb;
		x = xb;
		yEnd = ya;
		incDec = -1; //to decrement x value as it goes up y axis
	}
	else if (yb > ya && xb < xa) //negative slope
	{
		y = ya; //start at lower y value
		x = xa; //start at farther right x
		yEnd = yb;
		incDec = -1;
	}
	else if (yb < ya && xb < xa)//positive slope, (xb,yb) lower than (xa,ya)
	{
		y = yb;
		x = xb;
		yEnd = ya;
	}
	makePix(x, y, buf, red);

	while (y < yEnd)
	{
		y++;
		if (p < 0)
			p += twoDy;
		else {
			x += incDec;
			p += twoDyDx;
		}
		makePix(x, y, buf, red);
	}
}//bresSteepLine()

//gradual slope
void bresGradLine(int xa, int ya, int xb, int yb, float *buf, bool red)
{
	int dx = abs(xa - xb), dy = abs(ya - yb); //change in x and y
	int p = 2 * dy - dx; //p_1 in recursive formula
	int incDec = 1; //adds 1 or -1 depending on positive or negative slope
	int y = ya; //changes later depending on p value
	int start = xa, end = xb + 1; //goes ->, +1 causes it to stop at xb

	if (xa > xb) //xa comes after xb
	{
		start = xb;
		end = xa + 1;
		y = yb;

		if (ya < yb) //negative slope
		{
			y = ya;
			start = xa;
			end = xb - 1;
			incDec = -1;
		}
	}
	if (ya > yb && xa < xb) //negative slope
	{
		y = yb; //start at lower y endpoint
		start = xb; //start on right side
		end = xa - 1; //-1 to stop at xa
		incDec = -1; //decrement x value to move left on the x axis
	}
	for (int x = start; x != end; x += incDec) //right to left or left to right
	{
		int oldY = y; //save y value for p_i+1 term
		makePix(x, y, buf, red);

		if (p >= 0)
			y++;
		//calculate next term in recursive formula: p_i+1
		p = p + (2 * dy) - (2 * dx * (y - oldY));
	}
}

//uses the Bresenham algorithm to draw in the specified buffer
void bresMakeLine(int x, int y, int x1, int y1, float *buf, bool red = false)
{
	int deltaX = abs(x1 - x), deltaY = abs(y1 - y); //change in x and y 

	if (deltaX == 0) //vertical line
	{
		if (y < y1)
			vertical(y, y1, x, buf, red);
		else
			vertical(y1, y, x, buf, red);
	}
	else if (deltaY == 0) //horizontal line
	{
		if (x < x1)
			horizontal(x, x1, y, buf, red);
		else if (x1 < x)
			horizontal(x1, x, y, buf, red);
	}
	else if (deltaY == deltaX)
		diagonal(x, y, x1, y1, buf, red);
	else if (deltaY < deltaX)
		bresGradLine(x, y, x1, y1, buf, red);
	else if (deltaY > deltaX) // slope < -1 && 1 < slope (steep)
		bresSteepLine(x, y, x1, y1, buf, red);
}//bresMakeLine()



void ddaMakeLine(int x, int y, int x1, int y1, float *buf) //input as (x,y) to (x1, y1)
{
	if (x1 < x) //x must be smaller than x1
		return;
	if (x - x1 == 0) //vertical line
	{
		if (y < y1)
			vertical(y, y1, x, buf, false);
		else
			vertical(y1, y, x, buf, false); //y1's lower, start there
		return; //special case, avoids divide by zero
	}
	float slope = (y - y1) / (x - float(x1)); //calculate the slope
	float b = y - (slope * x); //b term in: y = mx + b

	if (slope == 0) //horizontal line
		horizontal(x, x1, y, buf, false);
	else if (slope == 1)
	{
		for (int currX = x; currX <= x1; currX++)
			makePix(currX, y++, buf, false); //increment y evenly with x
	}
	else if (slope == -1)
	{
		for (int currX = x; currX <= x1; currX++)
			makePix(currX, y--, buf, false); //decrement y evenly with x
	}
	else if ((0 < slope && slope < 1) || (-1 < slope && slope < 0))
	{
		for (int currX = x; currX <= x1; currX++) //walk through x-values
		{
			float newY = slope * currX + b; //calculate exact y values
			makePix(currX, round(newY), buf, false); //create pix at rounded location
		}
	}
	else if (1 < slope)
	{
		for (int currY = y; currY <= y1; currY++) //walk up y-values
		{
			float newX = (currY - b) / slope;
			makePix(round(newX), currY, buf, false);
		}
	}
	else if (slope < -1)
	{
		for (int currY = y; currY >= y1; currY--) //walk down y-values
		{
			float newX = (currY - b) / slope;
			makePix(round(newX), currY, buf, false);
		}
	}
}//ddaMakeLine()