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
//					GLOBAL VARIABLES
//===================================================================================================================================

//-------------------------------------------------------------------------------------------------------------------- default angles
float tailAngles[7] = {20.f,15.f,0.f,0.f,0.f,0.f,0.f} ;
float neckAngles[5] = {-15.f,10.f,0.f,0.f,0.f} ;

//----------------------------------------------------------------------------------------------------------------------------- width
float neckWidth[5] = {3.75,3.5,3.25,3.f,2.75} ;

//===================================================================================================================================
//					MULTIPLE USE FUNCTIONS
//===================================================================================================================================

//---------------------------------------------------------------- draw parts of head function
void drawJaw(int r) 
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Calculate rotation
	if(r > 20)	r = 20 ;
	if(r < 0)	r = 0 ;
	
	//Transformations, and draw jaw
	glTranslatef(0.2,0.f,0.f) ;	glRotatef(180.f,1.f,0.f,0.F) ;	glRotatef(195.f+r,0.f,0.f,1.f) ;	glScalef(1.f,0.65,3.f) ;	drawF(0) ;

	//Pop Matrix from function call
	glPopMatrix();
}

void drawTopOfHeadAndNose(void)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Transformations, and draw top of head
	glRotatef(180.f,1.f,0.f,0.f) ;	glRotatef(75.f,0.f,0.f,1.f) ;
	glPushMatrix() ;	glScalef(1.f,0.75,3.f) ;	drawC(0) ;	glPopMatrix() ;

	//Transformations, and draw nose 
	glTranslatef(-0.125,0.25,0.f) ;	glRotatef(5.f,0.f,0.f,1.f) ;
	glPushMatrix() ;	glScalef(1.f,0.75,3.f) ;	drawN(0) ;	glPopMatrix() ;

	//Draw Jaw
	drawJaw(0) ;

	//Pop Matrix from function call
	glPopMatrix();
}

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

//------------------------------------------------------------------------- draw tail function
void drawTail (void)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Transformation, save, and draw components
	glTranslatef(0.18,0.5,0.f) ;	glRotatef(180.f,0.f,1.f,0.f) ;	glRotatef(145.f,0.f,0.f,1.f) ; glPushMatrix() ;
	glScalef(1.f,0.375,0.f) ;	drawF(0) ;	glPopMatrix() ;

	for(int i = 0; i < 7; i++)
	{
		glTranslatef(0.f,0.3*0.375,0.f) ;	glRotatef(tailAngles[i],0.f,0.f,1.f) ;
		glPushMatrix() ;	glScalef(1.f,0.375,0.f) ;	drawF(0) ;	glPopMatrix() ;
	}

	//Draw tail components
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

//===================================================================================================================================
//					FUNCTIONS FROM SCENE GRAPH (from last to first)
//===================================================================================================================================

//------------------------------------------------------------------------ draw head function
void drawHead(int jawRotation)
{
	//Save Matrix from function call
	glPushMatrix();

	//Transformations, and draw top of head and nose
	glRotatef(180.f,0.f,1.f,0.f) ;	drawTopOfHeadAndNose();

	//Pop Matrix from function call
	glPopMatrix();
}

//---------------------------------------------------------------- draw neck and head function
void drawNeckAndHead (void)
{
	//Save function from function call
	glPushMatrix() ;

	//Transfromations, and draw base of neck
	glTranslatef(-0.5,0.3,0.f) ;	glRotatef(40.f,0.f,0.f,1.f) ;	glPushMatrix() ;	glScalef(1.5,0.5,5.f) ;	drawM(0) ; glPopMatrix() ;
	glTranslatef(0.f,0.2,0.f) ;	glRotatef(-15.f,0.f,0.f,1.f) ;	glPushMatrix() ;	glScalef(1.25/1.5,0.5,4.f) ;	drawM(0) ;	glPopMatrix() ;

	//Pop Matrix from function call
	glPopMatrix() ;	

	//Transformations for trunc of neck
	glTranslatef(-0.55,0.7,0.f) ;	glRotatef(180.f,0.f,1.f,0.f) ;	
	for(int i = 0; i < 5; i++)
	{
		glRotatef(neckAngles[i],0.f,0.f,1.f) ;	glPushMatrix() ;
		glScalef(1.25/1.5,0.5,neckWidth[i]) ;	drawM(0) ;	glPopMatrix() ;
		glTranslatef(0.f,0.2,0.f) ;
	}

	//Draw head
	drawHead(0) ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//---------------------------------------------------------- draw body and front legs function
void drawBody (void)
{
	//Save function from function call
	glPushMatrix() ;

	//Transformations and draw B
	/*glTranslatef(,,) ;*/	glRotatef(90.f,0.f,0.f,1.f) ;	glScalef(3.f,2.f,7.f) ;	drawB(0) ;

	//Pop Matrix from function call, and save
	glPopMatrix() ;		glPushMatrix() ;

	//Draw tail
	drawTail() ;

	//Draw Neck and head
	drawNeckAndHead() ;

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
void drawModel (int jawRotation)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Transformations and rear legs and body
	glTranslatef(0.f,0.4,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,)*/	drawRearLegsAndBody() ;

	//Pop Matrix from function call
	glPopMatrix() ;
}
