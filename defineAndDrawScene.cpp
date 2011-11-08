////////////////////////////////////////////////////////////////
//
//	defineAndDrawScene.cpp - code for drawing the different elements of the scene
//
//	Author: Ewan C. Burns,	Marc M. Fraser
//	Date:   04/10/2011
//
////////////////////////////////////////////////////////////////

//Includes for glut
#include <GL/glut.h>

//Includes for initials
#include "initials.h"

//Includes for scene
#include "drawBackground.h"
#include "drawModel.h"

//===================================================================================================================================
//					FUNCTIONS FOR THE ANIMATED SCENE
//===================================================================================================================================

//--------------------------------------------------------------------------------------------------------------------- main function
void drawScene (int kneeRotation, float* tailFlick, int neckTilt, int jawRotation)
{
	//Set camera
	glMatrixMode(GL_PROJECTION) ;
	glLoadIdentity() ;
	glOrtho(-3.0,3.0,-3.0,3.0,-10.0,10.0) ;
	glMatrixMode(GL_MODELVIEW) ;

	//Save Matrix from function call
	glPushMatrix() ;

	//Transformations for scene
	glTranslatef(0.f,-2.f,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,) ;*/

	//Draw Background
	drawBackground() ;

	//Draw Model
	drawModel(kneeRotation, tailFlick, neckTilt, jawRotation) ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//===================================================================================================================================
//					DRAW ALL SIX INITIALS
//===================================================================================================================================

void drawAllInitials (void)
{
	//Set camera
	glMatrixMode(GL_PROJECTION) ;
	glLoadIdentity() ;
	glOrtho(-3.0,3.0,-3.0,3.0,-10.0,10.0) ;
	glMatrixMode(GL_MODELVIEW) ;

	//Save Matrix from function call
	glPushMatrix() ;

	//Transformations and draw E
	glTranslatef(-1.f,1.f,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,) ;*/	drawE(0) ;

	//Pop Matrix from function call, and save
	glPopMatrix() ;			glPushMatrix() ;

	//Transformations and draw C
	glTranslatef(0.f,1.f,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,) ;*/	drawC(0) ;

	//Pop Matrix from function call, and save
	glPopMatrix() ;			glPushMatrix() ;

	//Transformations and draw B
	glTranslatef(+1.f,1.f,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,) ;*/	drawB(0) ;

	//Pop Matrix from function call, and save
	glPopMatrix() ;			glPushMatrix() ;

	//Transformations and draw M
	glTranslatef(-1.f,-1.f,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,) ;*/	drawM(0) ;

	//Pop Matrix from function call, and save
	glPopMatrix() ;			glPushMatrix() ;

	//Transformations and draw N
	glTranslatef(0.f,-1.f,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,) ;*/	drawN(0) ;

	//Pop Matrix from function call, and save
	glPopMatrix() ;			glPushMatrix() ;

	//Transformations and draw F
	glTranslatef(+1.f,-1.f,0.f) ;	/*glRotatef(,,,) ;*/	/*glScalef(,,) ;*/	drawF(0) ;

	//Pop Matrix from function call
	glPopMatrix() ;
}

//===================================================================================================================================
//					DEFINE THE SCENE TO DRAW
//===================================================================================================================================

void defineAndDrawScene (int scene, int origin, int kneeRotation, float* tailFlick, int neckTilt, int jawRotation)
{
	//Define the scene to be drawn, and draw
	switch (scene)
	{
		case 0 : drawScene(kneeRotation, tailFlick, neckTilt, jawRotation) ;			break ;
		case 1 : drawE(origin) ;								break ;
		case 2 : drawC(origin) ;								break ;
		case 3 : drawB(origin) ;								break ;
		case 4 : drawM(origin) ;								break ;
		case 5 : drawN(origin) ;								break ;
		case 6 : drawF(origin) ;								break ;
		case 7 : drawAllInitials() ;								break ;
		case 8 : drawJaw(jawRotation) ; 							break ;
		case 9 : drawTopOfHeadAndNose(jawRotation) ;						break ;
		case 10 : drawNeckAndHead(kneeRotation, neckTilt, jawRotation) ;			break ;
		case 11 : drawTail(kneeRotation, tailFlick) ;						break ;
		case 12 : drawBody (kneeRotation, tailFlick, neckTilt, jawRotation) 	;		break ;
		case 13 : drawFrontLegsAndBody (kneeRotation, tailFlick, neckTilt, jawRotation) ;	break ;
		default :										break ;
	}
}
