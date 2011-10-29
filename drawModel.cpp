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

//----------------------------------------------------------------------------------------------------------------------- tail angles
float angles[7] = {20.f,15.f,0.f,0.f,0.f,0.f,0.f} ;

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

	//Transformation, save, and draw components
	glTranslatef(0.18,0.5,0.f) ;	glRotatef(180.f,0.f,1.f,0.f) ;	glRotatef(145.f,0.f,0.f,1.f) ; glPushMatrix() ;
	glScalef(1.f,0.375,0.f) ;	drawF(0) ;	glPopMatrix() ;

	for(int i = 0; i < 7; i++)
	{
		glTranslatef(0.f,0.3*0.375,0.f) ;	glRotatef(angles[i],0.f,0.f,1.f) ;
		glPushMatrix() ;	glScalef(1.f,0.375,0.f) ;	drawF(0) ;	glPopMatrix() ;
	}

	//Draw tail components
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


//------------------------------------------------------------------------ draw head function


void drawTopOfHeadAndNose(void)
{
	glPushMatrix();
		glRotatef(180.f, 1.f, 0.f ,0.f);
		glRotatef(50.f, 0.f, 0.f, 1.f);
		glScalef(1.f, 1.f, 3.f);
		drawC(0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.2, -0.2, 0.f);
		glRotatef(140.f, 0.f, 0.f, 1.f);
		glScalef(1.f, 0.75, 3.f);
		drawN(0);
	glPopMatrix();
}

void drawJaw(int r) {
	glPushMatrix();
		glTranslatef(-0.2, -0.2, 0);
		glRotatef(165, 0, 0, 1);

		if(r > 20)
			r = 20;
		if(r < 0)
			r = 0;

		glRotatef(r, 0, 0, 1);
		glScalef(1.f, 0.65, 3.f);
		drawF(0);
	glPopMatrix();
}


void drawHead(int jawRotation)
{
	glPushMatrix();
		glTranslatef(0, .5, 0);

		drawTopOfHeadAndNose();
		drawJaw(jawRotation);

	glPopMatrix();
}




//------------------------------------------------------------------------ draw Model function
void drawModel (int jawRotation)
{
	//Save Matrix from function call
	glPushMatrix() ;

	//Transformations and rear legs and body
	glTranslatef(0.f,0.4,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,)*/	drawRearLegsAndBody() ;
	glPushMatrix();
	glTranslatef(-1.2, 2.f, 0);
	drawHead(jawRotation);
	glPopMatrix();

	//Pop Matrix from function call
	glPopMatrix() ;
}
