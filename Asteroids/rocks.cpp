#include "rocks.h"
#include "uiDraw.h"

// Put your Rock methods here
void BigRock::draw() 
{ 
	drawLargeAsteroid(getPoint(), getRotation());
	/*cerr << "Point: " << getPoint().getX() << "," << getPoint().getY()
		<< " Velocity: " << getVelocity().getDx() << "," << getVelocity().getDy() << endl;*/
}

void MediumRock::draw()
{
	drawMediumAsteroid(getPoint(), getRotation());
}

void SmallRock::draw() 
{
	drawSmallAsteroid(getPoint(), getRotation());
}