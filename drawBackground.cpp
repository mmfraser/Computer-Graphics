////////////////////////////////////////////////////////////////
//
//	drawBackground.cpp - code for drawing the different elements of the scene's background
//
//	Author: Ewan C. Burns,	Mark M. Fraser
//	Date:   08/10/2011
//
////////////////////////////////////////////////////////////////

//Includes for glut
#include <GL/glut.h>

//Include for maths functions
#include <math.h>

#define PI 3.14159264

//------------------------------------------------------------------------------------------------------------ draw cylinder function
void drawCylinder (float width, float height)
{
	//Save Matrix from function call
	glPushMatrix() ;


	//Transformations for tree trunc
	/*glTranslatef(,,) ;*/	/*glRotatef(,,,) ;*/	glScalef(width,1.f,width) ;

	//Draw quads
	glBegin(GL_QUAD_STRIP) ;
		for(float i = 0; i <= 40; i++)
		{
			glVertex3f(cos(2*i*PI/40),0.f,sin(2*i*PI/40)) ;	glVertex3f(cos(2*i*PI/40),height,sin(2*i*PI/40)) ;
		}
		
	glEnd() ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//---------------------------------------------------------------------------------------------------------------- draw tree function
void drawTree (void)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Draw trunc
	glColor3f(0.6,0.3,0.1) ;	drawCylinder(0.1,3.f) ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//--------------------------------------------------------------------------------------------------------------- draw floor function
void drawFloor (void)
{
	//Set color of floor
	glColor3f(0.f,1.f,0.f) ;

	//Set Vertices
	glBegin(GL_QUADS) ;
		glVertex3f(-3.f,0.f,3.f) ;	glVertex3f(3.f,0.f,3.f) ;
		glVertex3f(3.f,0.f,-3.f) ;	glVertex3f(-3.f,0.f,-3.f) ;
	glEnd() ;
}

//--------------------------------------------------------------------------------------------------------------- draw floor function
void drawBack (void)
{
	//Set color of floor
	glColor3f(0.f,0.f,1.f) ;

	//Set Vertices
	glBegin(GL_QUADS) ;
		glVertex3f(-3.f,0.f,-3.f) ;	glVertex3f(3.f,0.f,-3.f) ;
		glVertex3f(3.f,4.f,-3.f) ;	glVertex3f(-3.f,4.f,-3.f) ;
	glEnd() ;
}

//--------------------------------------------------------------------------------------------------------------- draw floor function
void drawBackground (void)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Draw floor and back
	drawFloor() ;	drawBack() ;

	//Transformations and draw Tree
	glTranslatef(-2.5,0.f,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,)*/	drawTree() ;

	//Pop Matrix from function call
	glPopMatrix() ;
}
