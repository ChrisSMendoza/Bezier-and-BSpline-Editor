#include <OpenGL/gl.h>	//note: should use these on mac
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <iostream>
#include <vector>

#include "lineDrawing.h"
#include "casteljau.h"
#include "deBoor.h"
#include "bspline.h"
#include "bezier.h"
#include "readWrite.h"
#include "ui.h"

using namespace std;
void display(); //main window display function

int main(int argc, char *argv[])
{
	read(file); //file set in ui.h
    //buffer declared in lineDrawing.h
	buffer = new float[bufferSize]; //allocate pixel buffer for main window
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	//set main window size to H x W
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_WIDTH); //square screen
	//set window position
	glutInitWindowPosition(100, 100);
	//create and set main window title; declared in ui.h
	mainWindow = glutCreateWindow("Curves");

	glClearColor(0, 0, 0, 0); //clears the OpenGL buffer
	glClear(GL_COLOR_BUFFER_BIT);

	glutDisplayFunc(display); //sets the display function
    
    //keys held down don't keep firing events
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutKeyboardFunc(key);
    glutKeyboardUpFunc(keyUp);
    
    glutMotionFunc(handleMouseInput);

	glutMainLoop(); //displays window until user enters x
	return EXIT_SUCCESS;
}


void display() //continuously called by main loop
{
	glClearColor(0, 0, 0, 0); //clears the OpenGL buffer
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	for (int i = 0; i < bCount; i++)
		beziers[i].draw();
	
	for (int i = 0; i < sCount; i++)
		splines[i].draw();

	glDrawPixels(SCREEN_WIDTH, SCREEN_WIDTH, GL_RGB, GL_FLOAT, buffer);
	glFlush();
}
