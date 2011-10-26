////////////////////////////////////////////////////////////////
//
//	drawModel.cpp - code for drawing the different elements of the model
//
//	Author: Ewan C. Burns,	Mark M. Fraser
//	Date:   08/10/2011
//
////////////////////////////////////////////////////////////////

//Includes for glut
#include <GL/glut.h>

//Includes for initials
#include "initials.h"

//===================================================================================================================================
//					MULTIPLE USE FUNCTIONS
//===================================================================================================================================

//-------------------------------------------------------------------------- dray leg function
void drawLeg (int side)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Transformations, and draw leg
	glTranslatef(0.f,0.f,side*0.2) ;	glRotatef(180.f,0.f,0.f,1.f) ;	glScalef(2.f,1.f,1.f) ;	drawF(0) ;

	//Push Matrix from function call
	glPopMatrix() ;
}

//--------------------------------------------------- draw top of legs and front legs function
void drawTopOfAndFrontLeg (int side)
{
	//Save Matrix on function call
	glPushMatrix() ;

	//Transformation for top of leg (part 1)
	glTranslatef(0.f,0.f,side*0.2) ;	glRotatef(180.f,0.f,1.f,0.f) ;	glRotatef(-90.f,0.f,0.f,1.f) ;	glScalef(1.f,2.f,1.f) ;	drawE(0) ;

	//Pop Matrix for function call, and save
	glPopMatrix () ;	glPushMatrix() ;

	//Transformation for top of leg (part 2)
	glTranslatef(-0.2,0.3,side*0.2) ;	glRotatef(90.f,0.f,0.f,1.f) ;	glScalef(2.f,2.f,1.f) ;	drawB(0) ;

	//Pop Matrix for function call, and save
	glPopMatrix () ;	glPushMatrix() ;

	//Transformation for top of leg (part 3)
	glTranslatef(-0.55,0.25,side*0.2) ;	glRotatef(side*-90.f,1.f,0.f,0.f) ;	glScalef(2.f,0.5,1.f) ;	drawM(0) ;

	//Pop Matrix for function call, and save
	glPopMatrix () ;	glPushMatrix() ;

	//Transformation and draw leg
	glTranslatef(-0.7,0.f,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,) ;*/	drawLeg(side) ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//------------------------------------------------------------------------- draw tail function
void drawTail (void)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Transformation, and and draw components
	glTranslatef(0.25,0.2,0.f) ;	glRotatef(180.f,0.f,1.f,0.f) ;	glRotatef(180.f,0.f,0.f,1.f) ;	glScalef(1.f,0.75,1.f) ;

	//Draw tail components
	drawF(0) ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//===================================================================================================================================
//					FUNCTIONS FROM SCENE GRAPH (from last to first)
//===================================================================================================================================

//---------------------------------------------------------- draw body and front legs function
void drawBody (void)
{
	//Save function from function call
	glPushMatrix() ;

	//Transformations and draw B
	/*glTranslatef(,,) ;*/	glRotatef(90.f,0.f,0.f,1.f) ;	glScalef(3.f,2.f,7.f) ;	drawB(0) ;

	//Pop Matrix from function call, and save
	glPopMatrix() ;		glPushMatrix() ;

	//transforations, and draw tail
	drawTail() ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//---------------------------------------------------------- draw body and front legs function
void drawFrontLegsAndBody (void)
{
	//Push Matrix from function call
	glPushMatrix() ;

	//Draw left leg
	drawTopOfAndFrontLeg(1) ;

	//Draw right leg
	drawTopOfAndFrontLeg(-1) ;

	//Draw body
	glTranslatef(-0.2,0.3,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,) ;*/	drawBody() ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//-------------------------------------------------------------------- draw rear legs function
void drawRearLegsAndBody (void)
{
	//Push Matrix from function call
	glPushMatrix() ;

	//Draw left leg
	drawLeg(1) ;

	//Draw right leg
	drawLeg(-1) ;

	//Draw top of legs
	drawFrontLegsAndBody() ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//------------------------------------------------------------------------ draw Model function
void drawModel (void)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Transformations and raw rear legs and body
	glTranslatef(0.f,0.4,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,)*/	drawRearLegsAndBody() ;

	//Pop Matrix from function call
	glPopMatrix() ;
}