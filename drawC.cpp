////////////////////////////////////////////////////////////////
//
//	drawM.cpp - code for Letter C model
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

void drawC (int origin)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Transformations for cube
	glTranslatef(-0.1,0.f,0.f) ;	/*glRotatef(,,,) ;*/		glScalef(4.f,1.f,1.f) ;	cube() ;

	//Restaure Matrix to function call, and save
	glPopMatrix() ;			glPushMatrix() ;

	//Tranformations for the curve
	glTranslatef(-0.2,0.175,0.f) ;	glRotatef(60.f,0.f,0.f,1.f) ;	/*glScalef(,,) ;*/	draw3Dcurve(0.05,0.15,0.2,0.f,210.f,5.f) ;

	//Pop the function call Matrix
	glPopMatrix() ;
	if(origin)	cube() ;
}
