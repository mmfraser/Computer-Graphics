////////////////////////////////////////////////////////////////
//
//	drawModel.h - prototypes of accessible functions contained in the drawModel.cpp file
//
//	Author: Ewan C. Burns,	Mark M. Fraser
//	Date:   14/10/2011
//
////////////////////////////////////////////////////////////////

/**************************************************************
List of varibles for the drawModel function, from first to last
	- kneeRotation
	- tailFlick
	- neckTilt
	- jawRotation
***************************************************************/

void drawModel (int kneeRotation, float* tailFlick, int neckTilt, int jawRotation) ;
void drawJaw (int jawRotation) ;
void drawTopOfHeadAndNose(int jawRotation) ;
void drawHead(int neckTilt, int jawRotation) ;
void drawNeckAndHead (int kneeRotation, int neckTilt, int jawRotation) ;
void drawTail (int kneeRotation, float* tailFlick) ;
void drawBody (int kneeRotation, float* tailFlick, int neckTilt, int jawRotation) ;
void drawFrontLegsAndBody (int kneeRotation, float* tailFlick, int neckTilt, int jawRotation) ;