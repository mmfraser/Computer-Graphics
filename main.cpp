//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	main.cpp - code main functions for main function and GLUT callback functions
//
// 	Author: Ewan C. Burns,	Marc M. Fraser
//	Date:   04/10/2011
//
//	Parts of this code were taken from Professor Mike Chantler's Example_8_3.cpp file
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include "stdafx.h"
#endif

//Standard Includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Includes for glut
#include <GL/glut.h>

//Personnel header files
#include "defineAndDrawScene.h"
#include "initials.h"

//Prototype for idlePlayCallback
void idlePlayCallback (void) ;

//Define PI
#define PI 3.14159264

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
int stepDraw = 0 ;
int play = 0 ;

//------------------------------------------------------------------------------------------------------------ model motion variables
int jawRotation = 0, kneeRotation = 0, neckTilt = 0 ;
int counterTail = 0 ;
int counterJaw = 0 ;
float tailFlick[8] = {	0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f	} ;

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

void keyAssignments() {
		printf("b	-	Draw B \n");
		printf("c	-	Draw C \n");
		printf("e	-	Draw E \n");
		printf("f	-	Draw F \n");
		printf("h/H	-	Increase/decrease neck rotation\n");
		printf("i	-	Draw all initials model \n");
		printf("j/J	-	Open/Close jaw \n");
		printf("k/K	-	Increase/decrease knee rotation\n");
		printf("L/l	-	Toggle wireframe \n");
		printf("m	-	Draw N \n");
		printf("o	-	Draw origin of initial. \n");
		printf("p	-	Play animation. \n");
		printf("s	-	Draw full model \n");
		printf("x	-	Draw x-axis \n");
		printf("y	-	Draw x-axis \n");
		printf("z	-	Draw x-axis \n");
		printf("/	-	Draw x-axis \n");
}

//-------------------------------------------------------------------------------------------------------- keyboard callback function
void keyboardCallback(unsigned char key, int x, int y)
{
	//Pressed key
	printf("Pressed key %c.\n", key) ;

	//Read key touch
	switch (key)
	{

		//Break when Escape
		case 27  : 	printf("Quit program.") ;	exit(0) ;
		//Define scene to display
		case 's' : 	printf("Drew Model.\n") ;		scene = 0 ;	break ;
		case 'e' : 	printf("Drew E.\n") ;			scene = 1 ;	break ;
		case 'c' : 	printf("Drew C.\n") ;			scene = 2 ;	break ;
		case 'b' : 	printf("Drew B.\n") ;			scene = 3 ;	break ;
		case 'm' : 	printf("Drew M.\n") ;			scene = 4 ;	break ;
		case 'n' : 	printf("Drew N.\n") ;			scene = 5 ;	break ;
		case 'f' : 	printf("Drew F.\n") ;			scene = 6 ;	break ;
		case 'i' : 	printf("Drew all initials.\n") ;	scene = 7 ;	break ;
		case '/' : 	printf("Drew next scene.\n") ;		scene++ ;
						if(scene > 15)		scene = 0 ;	break ;
		//Show origin for initials
		case 'o' : 	printf("Showing origin of initials.\n") ;
				origin++ ;	if(origin > 1)	origin = 0 ;		break ;
		//Define background options
		case 'a' : 	printf("Changed background.\n") ;
				back++ ;	if(back > 1)		back = 0 ;	break ;
		case 'l' :	printf("Draw transparent polygons.\n") ;
			 	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE) ;		break ;
		case 'L' :	printf("Draw filled polygons.\n") ;
			 	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL) ;		break ;
		case 'x' : 	printf("Draw (x,y) axes.\n") ;
				x_y_display++ ;	if(x_y_display > 1)	x_y_display=0; 	break ;
		case 'y' : 	printf("Draw (y,z) axes.\n") ;
				y_z_display++ ;	if(y_z_display > 1)	y_z_display=0;	break ;
		case 'z' : 	printf("Draw (x,z) axes.\n") ;
				x_z_display++ ;	if(x_z_display > 1)	x_z_display=0;	break ;
		//Controled mouvements
		case 'j' : 	printf("Open jaw.\n") ;
				if(jawRotation < 20)		jawRotation++ ;		break ;
		case 'J' : 	printf("Close jaw.\n") ;
				if(jawRotation > 0)		jawRotation-- ;		break ;
		case 'k' : 	printf("Jump up.\n") ;
				if(kneeRotation < 45)		kneeRotation++ ;	break ;
		case 'K' : 	printf("Fall down.\n") ;
				if(kneeRotation > 0)		kneeRotation-- ;	break ;
		case 'h' : 	printf("Bend neck.\n") ;
				if(neckTilt < 45)		neckTilt++ ;		break ;
		case 'H' : 	printf("Straigthen neck.\n") ;
				if(neckTilt > 0)		neckTilt-- ;		break ;
		//Play scene mouvement
		case 'p' :	printf("Starting mouvement.\n") ;
				glutKeyboardFunc(NULL) ;
				glutIdleFunc(idlePlayCallback) ;
				play = 0 ;						break ;
		default :								break ;
	}

	//Further infotmation
	printf("Knee Rotation :\t%d\nJaw Rotation:\t%d\nNeck Tilt :\t%d\n\n",kneeRotation,jawRotation,neckTilt) ;

	//Ask for redisplay
	glutPostRedisplay() ;
}

//---------------------------------------------------------------------------------------------------- mouse motion callback function
void mouseMotionCallback(int x, int y)
{
	//Called when the Mouse is moved with left button down
	G_theta[0] = pitch0 + (y - mouseY0) ;
	G_theta[1] = yaw0 + (x - mouseX0) ;

	//Ask for redislay
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
	//Define tail flick angle
	for(int i = 6; i >= 0; i--) tailFlick[i+1] = tailFlick[i] ;
	tailFlick[0] = 45*sin(2*PI*counterTail/50) ;
	counterTail++ ; counterTail %= 50 ;

	//Ask for redisplay
	glutPostRedisplay() ;
}

//------------------------------------------------------------------------------------------------------------ idle callback function
void idlePlayCallback()
{
	//Setting back to zero
	switch (play)
	{
		case 0 :
			if(kneeRotation > 0)	kneeRotation-- ;
			if(neckTilt > 0)	neckTilt-- ;
			if(jawRotation > 0) 	jawRotation-- ;
			if(kneeRotation == 0 & neckTilt == 0 & jawRotation == 0)	play++ ;
			break ;
		case 1 :
			if(kneeRotation < 20)	kneeRotation++ ;
			if(neckTilt < 30)	neckTilt++ ;
			if(jawRotation < 20) 	jawRotation += 2 ;
			if(kneeRotation == 20 & neckTilt == 30 & jawRotation == 20)	play++ ;
			break ;
		case 2 :
			if(jawRotation > 0)	jawRotation -= 2 ;
			else play++ ;
			break ;
		case 3 :
			if(neckTilt > 0)			neckTilt-- ;
			if(kneeRotation > 0 & neckTilt < 11)	kneeRotation-- ;
			if(kneeRotation == 0 & neckTilt == 0)				play++ ;
			break ;
		case 4 :
			if(counterJaw < 100)	{	counterJaw++ ;	jawRotation = 10 - (int)(10*cos(2*PI*counterJaw/20)) ;	}
			else	{	counterJaw = 0 ;	play++ ;	}
			break ;
		case 5 :
			glutKeyboardFunc(keyboardCallback) ;
			glutIdleFunc(idleCallback) ;
			break ;
		default : 	break ;
	}

	//Define tail flick angle
	for(int i = 6; i >= 0; i--) tailFlick[i+1] = tailFlick[i] ;
	tailFlick[0] = 45*sin(2*PI*counterTail/50) ;
	counterTail++ ; counterTail %= 50 ;

	//Ask for redisplay
	glutPostRedisplay() ;
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
	defineAndDrawScene(scene, origin, kneeRotation, tailFlick,neckTilt, jawRotation) ;

	//Switch buffers to show new image
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
	glutCreateWindow("Computer Graphics project : first view of initials") ;
	glEnable(GL_DEPTH_TEST) ;
	glClearColor(0.f,0.f,0.f,1.f) ;

	//Callback function
	glutMouseFunc(mouseClickCallback) ;
	glutKeyboardFunc(keyboardCallback) ;
	glutMotionFunc(mouseMotionCallback) ;
	glutIdleFunc(idleCallback) ;
	glutDisplayFunc(displayCallback) ;
	glutReshapeFunc(reshapeCallback) ;

	keyAssignments();
	//Start glut loop
	glutMainLoop() ;
	return(0) ;
}
