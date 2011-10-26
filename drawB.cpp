////////////////////////////////////////////////////////////////
//
//	drawB.cpp - code for Letter B model
// 
//	Author: Ewan C. Burns
//	Date:   04/10/2011
//
////////////////////////////////////////////////////////////////

//Includes for glut
#include <GL/glut.h>

//Include 3DCurve function
#include "3DCurve.h"

//Include cube function
#include "cube.h"

void drawB (int origin )
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Translate to center of axe and save
	glTranslatef(0.f,0.075,0.f) ;	glPushMatrix() ;

	//Tranformations for the cube
	glTranslatef(0.025,0.f,0.f) ;	/*glRotatef(,,,) ;*/		glScalef(1.f,8.f,1.f) ;		cube() ;

	//Restaure Matrix to center of cube, and save
	glPopMatrix() ;			glPushMatrix() ;

	//Transformations for first curve
	glTranslatef(0.05,0.1,0.f) ;	glRotatef(-90.f,0.f,0.f,1.f) ;	glScalef(1.f,1.25,1.f) ;	draw3Dcurve(0.05,0.05,0.1,0.f,180.f,5.f) ;

	//Restaure Matrix to center of cube, and save
	glPopMatrix() ;			glPushMatrix() ;

	//Transformations for second curve
	glTranslatef(0.05,-0.075,0.f) ;	glRotatef(-90.f,0.f,0.f,1.f) ;	glScalef(1.f,1.25,1.f) ;	draw3Dcurve(0.05,0.075,0.125,0.f,180.f,5.f) ;

	//Restaure Matrix to center then function call
	glPopMatrix() ;			glPopMatrix() ;
	if(origin)	cube() ;
}
