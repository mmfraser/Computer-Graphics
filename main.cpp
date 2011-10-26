///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	main.cpp - code main functions for main function and GLUT callback functions
//
// 	Author: Ewan C. Burns,	Mark M. Fraser
//	Date:   04/10/2011
//
//	Parts of this code were taken from Professor Mike Chantler's Example_8_3.cpp file
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Includes for glut
#include <GL/glut.h>

//Standard Includes
#include <stdio.h>
#include <stdlib.h>

//Personnel header files
#include "defineAndDrawScene.h"
#include "initials.h"

//===================================================================================================================================
//					GLOBAL VARIABLES
//===================================================================================================================================

//----------------------------------------------------------------------------------------------------------------- window  variables
int height = 800, width = 800 ;
int mainWindow ;

//------------------------------------------------------------------------------------------------------------------- mouse variables
int mouseDown_x = 0, mouseDown_y = 0 ;
float mouseD_x = 0.f, mouseD_y = 0.f, rotate_x = 0.f, rotate_y = 0.f ;
bool MousePressed ;

//------------------------------------------------------------------------------------------------------------------------ draw scene
static float G_theta[3] ;

int x_y_display = 0, y_z_display = 0, x_z_display = 0 ;

float pitch0, yaw0 ;
int mouseX0, mouseY0 ;

int scene = 0, back = 0, origin = 0 ;

//===================================================================================================================================
//					OTHER FUNCTIONS
//===================================================================================================================================

//------------------------------------------------------------------------------------------------------------- view control function
void viewControl()
{
	// Reset matrix
	glLoadIdentity() ;

	//Rotate everything
	glRotatef(G_theta[0], 1.f, 0.f, 0.f) ;
	glRotatef(G_theta[1], 0.f, 1.f, 0.f) ;
	glRotatef(G_theta[2], 0.f, 0.f, 1.f) ;
}

void drawAxesAndGridLines(void)
{
	float offset ;
	int gd ;
	glBegin(GL_LINES) ;
		glColor3f(1.f,0.f,0.f) ;
		glVertex3f(-20.f,0.f,0.f) ;
		glVertex3f(+20.f,0.f,0.f) ;
		glVertex3f(0.f,-20.f,0.f) ;
		glVertex3f(0.f,+20.f,0.f) ;
		glVertex3f(0.f,0.f,-20.f) ;
		glVertex3f(0.f,0.f,+20.f) ;
	glEnd() ;

	glLineStipple(1,0xAAAA) ;			//line style = fine dots
	glEnable(GL_LINE_STIPPLE) ;

	glBegin(GL_LINES) ;

	if (x_y_display)
	{
		glColor3f(0.f,0.7,0.7) ;
		for (offset=-10.f; offset<10.1; offset++)
		{
			//draw lines in x-y plane
			glVertex3f(-10.f,offset,0.f) ;	// Top Left
			glVertex3f(+10.f,offset,0.f) ;	// Top Right
			glVertex3f(offset,-10.f,0.f) ;	// Bottom Right
			glVertex3f(offset,+10.f,0.f) ;	// Bottom Left
		}
	}

	if (y_z_display)
	{
		glColor3f(0.7,0.f,0.7) ;
		for (offset=-10.f; offset<10.1; offset++)
		{
			//draw lines in y-z plane
			glVertex3f(0.f,offset,-10.f) ;
			glVertex3f(0.f,offset,+10.f) ;
			glVertex3f(0.f,-10.f,offset) ;
			glVertex3f(0.f,+10.f,offset) ;
		}
	}

	if (x_z_display)
	{
		glColor3f(0.7,0.7,0.f) ;
		for (offset=-10.f; offset<10.1; offset++)
		{
			//draw lines in x-z plane
			glVertex3f(offset,0.f,-10.f) ;
			glVertex3f(offset,0.f,+10.f) ;
			glVertex3f(-10.f,0.f,offset) ;
			glVertex3f(+10.f,0.f,offset) ;
		}
	}

	glEnd() ;
	glDisable(GL_LINE_STIPPLE) ;
}

//===================================================================================================================================
//					CALLBACK FUNCTIONS
//===================================================================================================================================

//--------------------------------------------------------------------------------------------------------- reshape callback function
void reshapeCallback(int w, int h)
{
	glViewport(0, 0, w, h) ;
	glMatrixMode(GL_PROJECTION) ;
	glLoadIdentity() ;
	if (w == 0 || h ==0) return ;
	if (w <= h)	glOrtho(-3.0,3.0,-3.0*(float)h/(float)w,3.0*(float)h/(float)w,-10.0,10.0) ;
	else		glOrtho(-3.0*(float)w/(float)h,3.0*(float)w/(float)h,-3.0,3.0,-10.0,10.0) ;
	glMatrixMode(GL_MODELVIEW) ;
}

//-------------------------------------------------------------------------------------------------------- keyboard callback function
void keyboardCallback(unsigned char key, int x, int y)
{
	//Read key touch
	switch (key)
	{
		case 27 : exit(0) ;
		case 's' : scene = 0 ;	break ;
		case 'e' : scene = 1 ;	break ;
		case 'c' : scene = 2 ;	break ;
		case 'b' : scene = 3 ;	break ;
		case 'm' : scene = 4 ;	break ;
		case 'n' : scene = 5 ;	break ;
		case 'f' : scene = 6 ;	break ;
		case 'i' : scene = 7 ;	break ;
		case 'p' : scene++ ;		if(scene > 7)		scene = 0 ;	break ;
		case 'o' : origin++ ;		if(origin > 1)		origin = 0 ;	break ;
		case 'a' : back++ ;		if(back > 1)		back = 0 ;	break ;
		case 'l' : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE) ;			break ;
		case 'L' : glPolygonMode(GL_FRONT,GL_FILL) ;				break ;
		case 'x' : x_y_display++ ;	if(x_y_display > 1)	x_y_display=0; 	break ;
		case 'y' : y_z_display++ ;	if(y_z_display > 1)	y_z_display=0;	break ;
		case 'z' : x_z_display++ ;	if(x_z_display > 1)	x_z_display=0;	break ;
		default :		break ;
	}

	//Ask for Redisplay
	glutPostRedisplay() ;
}

//---------------------------------------------------------------------------------------------------- mouse motion callback function
void mouseMotionCallback(int x, int y)
{
	//Called when the Mouse is moved with left button down
	G_theta[0] = pitch0 + (y - mouseY0) ;
	G_theta[1] = yaw0 + (x - mouseX0) ;
	glutPostRedisplay() ;
}

//----------------------------------------------------------------------------------------------------- mouse click callback function
void mouseClickCallback(int btn, int state, int x, int y)
{
	switch (btn)
	{
		case GLUT_RIGHT_BUTTON :
			switch (state)
			{
				case GLUT_DOWN : exit(0) ;
			}
		case GLUT_LEFT_BUTTON :
			switch (state)
			{
				case GLUT_DOWN :
					MousePressed = true ;
					pitch0 = G_theta[0] ;
					yaw0 = G_theta[1] ;
					mouseX0 = x ; mouseY0 = y ;
				break ;
				case GLUT_UP :
					MousePressed = false ;
				break ;
			}
	}
}

//------------------------------------------------------------------------------------------------------------ idle callback function
void idleCallback()
{

}

//--------------------------------------------------------------------------------------------------------- display callback function
void displayCallback()
{
	//Set Drawing Mode
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity() ;

	//Set back color
	switch (back)
	{
		case 0 : glClearColor(0.f,0.f,0.f,1.f) ;	break ;
		case 1 : glClearColor(1.f,1.f,1.f,1.f) ;	break ;
		default : 					break ;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	//Rotate screen
	viewControl() ;

	//Draw axes when needed
	if(back)	drawAxesAndGridLines() ;

	//Draw the Scene
	defineAndDrawScene(scene,origin) ;

	glutSwapBuffers() ;
}

//===================================================================================================================================
//					MAIN FUNCTION
//===================================================================================================================================

int main(int argc, char** argv)
{
	//Initialisation
	glutInit(&argc,argv) ;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;
	glutInitWindowSize(height,width) ;
	mainWindow = glutCreateWindow("Computer Graphics project : first view of initials") ;
	glEnable(GL_DEPTH_TEST) ;
	glClearColor(0.f,0.f,0.f,1.f) ;

	//Callback function
	glutMouseFunc(mouseClickCallback) ;
	glutKeyboardFunc(keyboardCallback) ;
	glutMotionFunc(mouseMotionCallback) ;
	//glutIdleFunc(idleCallback) ;
	glutDisplayFunc(displayCallback) ;
	glutReshapeFunc(reshapeCallback) ;

	//Start glut loop
	glutMainLoop() ;
	return(0) ;
}
