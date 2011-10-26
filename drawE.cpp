////////////////////////////////////////////////////////////////
//
//	drawM.cpp - code for Letter E model
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

void drawE (int origin)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Tranformations for the first cube, and draw
	glTranslatef(-0.1,0.f,0.f) ;		/*glRotatef(,,,) ;*/		glScalef(4.f,1.f,1.f) ;	cube() ;

	//Restaure Matrix to center and save
	glPopMatrix() ;				glPushMatrix() ;

	//Tranformations for the first curve, and draw
	glTranslatef(-0.2,0.0875,0.f) ;		glRotatef(90,0.f,0.f,1.f) ;	/*glScalef(,,) ;*/	draw3Dcurve(0.05,0.0625,0.1125,0.f,180.f,5.f) ;

	//Restaure Matrix to center and save
	glPopMatrix() ;				glPushMatrix() ;

	//Tranformations for the second cube
	glTranslatef(-0.2,0.175,0.f) ;		/*glRotatef(,,,) ;*/		glScalef(2.f,1.f,1.f) ;	cube() ;

	//Restaure Matrix to center and save
	glPopMatrix() ;				glPushMatrix() ;

	//Tranformations for the second curve, and draw
	glTranslatef(-0.2,0.2625,0.f) ;		glRotatef(90,0.f,0.f,1.f) ;	/*glScalef(,,) ;*/	draw3Dcurve(0.05,0.0625,0.1125,0.f,180.f,5.f) ;

	//Restaure Matrix to center and save
	glPopMatrix() ;				glPushMatrix() ;

	//Tranformations for the third cube
	glTranslatef(-0.1,0.35,0.f) ;		/*glRotatef(,,,) ;*/		glScalef(4.f,1.f,1.f) ;	cube() ;

	//Restaure Matrix to center then function call
	glPopMatrix() ;
	if(origin)	cube() ;
}
