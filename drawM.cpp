////////////////////////////////////////////////////////////////
//
//	drawM.cpp - code for Letter M model
// 
//	Author: Marc M. Fraser
//	Date:   28/09/2011
//
////////////////////////////////////////////////////////////////

//Includes for glut
#include <GL/glut.h>

//Include 3DCurve function
#include "3DCurve.h"

//Include cube function
#include "cube.h"

void drawM (int origin)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Tranformations for the first cube
	glTranslatef(0.f,0.2,0.f) ;	/*glRotatef(,,,) ;*/		glScalef(1.f,8.f,1.f) ;		cube() ;

	//Restaure Matrix to function call, and save) ;	
	glPopMatrix() ;			glPushMatrix() ;

	//Transformations for the curve
	glTranslatef(0.1,0.4,0.f) ;	glRotatef(180.f,0.f,0.f,1.f) ;	/*glScalef(,,)*/		draw3Dcurve(0.05,0.075,0.125,0.f,180.f,5.f) ;

	//Restaure Matrix to function call, and save) ;	
	glPopMatrix() ;			glPushMatrix() ;

	//Tranformations for the first cube
	glTranslatef(0.2,0.2,0.f) ;	/*glRotatef(,,,) ;*/		glScalef(1.f,8.f,1.f) ;		cube() ;

	//Restaure Matrix to function call
	glPopMatrix() ;
	if(origin)	cube() ;
}
