////////////////////////////////////////////////////////////////
//
//	drawModel.cpp - code for drawing the different elements of the model
//
//	Author: Ewan C. Burns,	Marc M. Fraser
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
int noNeckParts = 5;
int noNeckPartsDrawn = 0;

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

	//Transformations, and draw jaw
	glTranslatef(0.2,0.f,0.f) ;	glRotatef(180.f,1.f,0.f,0.f) ;	glRotatef(195.f+r,0.f,0.f,1.f) ;	glScalef(1.f,0.65,3.f) ;	
drawF(0) ;

	//Pop Matrix from function call
	glPopMatrix();
}

void drawTopOfHeadAndNose(int jawRotation)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Transformations, and draw top of head
	glRotatef(180.f,1.f,0.f,0.f) ;	glRotatef(75.f,0.f,0.f,1.f) ;
	glPushMatrix() ;	glScalef(1.f,0.75,3.f) ;	drawC(0) ;	glPopMatrix() ;

	//Transformations, and draw ears
	glPushMatrix();	glTranslatef(-0.3,0.f,-0.05) ;	glRotatef(120.f,0.f,0.f,1.f) ;	glScalef(0.25,0.3,1.f) ; 	drawN(0) ;	glPopMatrix();
	glPushMatrix();	glTranslatef(-0.3,0.f,0.05) ;	glRotatef(120.f,0.f,0.f,1.f) ;	glScalef(0.25,0.3,1.f) ; 	drawN(0) ;	glPopMatrix() ;

	//Transformations, and draw nose
	glTranslatef(-0.125,0.25,0.f) ;	glRotatef(5.f,0.f,0.f,1.f) ;
	glPushMatrix() ;	glScalef(1.f,0.75,3.f) ;	drawN(0) ;	glPopMatrix() ;

	//Draw Jaw
	drawJaw(jawRotation) ;

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
void drawTail (int kneeRotation, float* tailFlick)
{
	//Define temporary tail angles
	int tempTailAngles[8] = {0,0,0,0,0,0,0,0} ;
	if(kneeRotation < 15) tempTailAngles[2] = kneeRotation ;
	else if(kneeRotation < 35)		{	tempTailAngles[2] = 15 ;	tempTailAngles[1] = kneeRotation - 15 ;	}
	else	{	tempTailAngles[2] = 15 ;	tempTailAngles[1] = 20 ;	tempTailAngles[0] = kneeRotation - 35 ;	}

	//Save Matrix from function call
	glPushMatrix() ;

	//Transformation, save, and draw components
	glTranslatef(0.18,0.5,0.f) ;	glRotatef(180.f,0.f,1.f,0.f) ;	glRotatef(145.f-tempTailAngles[0],0.f,0.f,1.f) ;
	glRotatef(tailFlick[0],1.f,0.f,0.f) ;	glPushMatrix() ;	glScalef(1.f,0.375,1.f) ;	drawF(0) ;	glPopMatrix() ;

	for(int i = 0; i < 7; i++)
	{
		glTranslatef(0.f,0.3*0.375,0.f) ;	glRotatef(tailAngles[i]-tempTailAngles[i+1],0.f,0.f,1.f) ;
		glRotatef(tailFlick[i+1]-tailFlick[i],1.f,0.f,0.f) ;
		glPushMatrix() ;	glScalef(1.f,0.375,1.f) ;	drawF(0) ;	glPopMatrix() ;
	}

	//Pop Matrix from function call
	glPopMatrix() ;
}

//--------------------------------------------------- draw top of legs and front legs function
void drawTopOfAndFrontLeg (int side, int kneeRotation)
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
	glTranslatef(-0.7,0.f,0.f) ;	glRotatef(kneeRotation,0.f,0.f,1.f) ;	/*glScalef(,,) ;*/	drawLeg(side) ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//===================================================================================================================================
//					FUNCTIONS FROM SCENE GRAPH (from last to first)
//===================================================================================================================================

//------------------------------------------------------------------------ draw head function
void drawHead(int neckTilt, int jawRotation)
{
	//Save Matrix from function call
	glPushMatrix();

	//Transformations, and draw top of head and nose
	glRotatef(2*((float)neckTilt),0.f,0.f,1.f) ;	glRotatef(180.f,0.f,1.f,0.f) ;	drawTopOfHeadAndNose(jawRotation);

	//Pop Matrix from function call
	glPopMatrix();
}

void drawNeckPart(int neckTilt, int neckPart) {
	int tempNeckAngles[5] = {neckTilt,-neckTilt,-neckTilt,-neckTilt,0} ;
	glRotatef(neckAngles[neckPart]+tempNeckAngles[neckPart],0.f,0.f,1.f) ;	glPushMatrix() ;
	glScalef(1.25/1.5,0.5,neckWidth[neckPart]) ;	drawM(0) ;	glPopMatrix() ;
	glTranslatef(0.f,0.2,0.f) ;
	noNeckPartsDrawn++;

	if(noNeckParts == noNeckPartsDrawn) {
		noNeckPartsDrawn = 0;
		return;
	} else
		drawNeckPart(neckTilt, neckPart++);
}

//---------------------------------------------------------------- draw neck and head function
void drawNeckAndHead (int kneeRotation, int neckTilt, int jawRotation)
{
	//Defining temporary neck angles
	int tempNeckAngles[5] = {neckTilt,-neckTilt,-neckTilt,-neckTilt,0} ;

	//Save function from function call
	glPushMatrix() ;

	//Transfromations, and draw base of neck
	glTranslatef(-0.5,0.3,0.f) ;	glRotatef(40.f,0.f,0.f,1.f) ;	glPushMatrix() ;	glScalef(1.5,0.5,5.f) ;	drawM(0) ; glPopMatrix()  ;
	glTranslatef(0.f,0.2,0.f) ;	glRotatef(-15.f+kneeRotation,0.f,0.f,1.f) ;	glPushMatrix() ;	glScalef(1.25/1.5,0.5,4.f) ;	drawM(0) ;	glPopMatrix() ;

	//Transformations for trunc of neck
	glTranslatef(0.1625,0.175,0.f) ;	glRotatef(180.f,0.f,1.f,0.f) ;	glRotatef(25.f,0.f,0.f,1.f) ;

	// Draws the neck, recursively so it is jointed.
	drawNeckPart(neckTilt, 1);
	
	//Draw head
	drawHead(neckTilt,jawRotation) ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//---------------------------------------------------------- draw body and front legs function
void drawBody (int kneeRotation, float* tailFlick, int neckTilt, int jawRotation)
{
	//Save function from function call
	glPushMatrix() ;

	//Transformations and draw B
	/*glTranslatef(,,) ;*/	glRotatef(90.f,0.f,0.f,1.f) ;	glScalef(3.f,2.f,7.f) ;	drawB(0) ;

	//Pop Matrix from function call, and save
	glPopMatrix() ;		glPushMatrix() ;

	//Draw tail
	drawTail(kneeRotation,tailFlick) ;

	//Draw Neck and head
	drawNeckAndHead(kneeRotation,neckTilt,jawRotation) ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//---------------------------------------------------------- draw body and front legs function
void drawFrontLegsAndBody (int kneeRotation, float* tailFlick, int neckTilt, int jawRotation)
{
	//Push Matrix from function call
	glPushMatrix() ;

	//Draw left leg
	drawTopOfAndFrontLeg(1,kneeRotation) ;

	//Draw right leg
	drawTopOfAndFrontLeg(-1,kneeRotation) ;

	//Draw body
	glTranslatef(-0.2,0.3,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,) ;*/	drawBody(kneeRotation,tailFlick,neckTilt,jawRotation) ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//-------------------------------------------------------------------- draw rear legs function
void drawRearLegsAndBody (int kneeRotation, float* tailFlick, int neckTilt, int jawRotation)
{
	//Push Matrix from function call
	glPushMatrix() ;

	//Draw left leg
	drawLeg(1) ;

	//Draw right leg
	drawLeg(-1) ;

	//Draw top of legs
	glRotatef(-kneeRotation,0.f,0.f,1.f) ;	drawFrontLegsAndBody(kneeRotation,tailFlick,neckTilt,jawRotation) ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//------------------------------------------------------------------------ draw Model function
void drawModel (int kneeRotation, float* tailFlick, int neckTilt, int jawRotation)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Transformations and rear legs and body
	glTranslatef(0.f,0.4,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,)*/	drawRearLegsAndBody(kneeRotation,tailFlick,neckTilt,jawRotation) ;

	//Pop Matrix from function call
	glPopMatrix() ;
}
