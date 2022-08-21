#include "ship.h"

#include "uiDraw.h"

#include <iostream>

// Put your ship methods here
#define M_PI 3.14159265358979323846

void Ship::resurrect(Point position, Velocity velocity)
{
	revive();
	setRotation(0);
	setPoint(position);
	setVelocity(velocity);
}

void Ship::turnLeft()
{
	rotation += ROTATE_AMOUNT;
}

void Ship::turnRight()
{
	rotation -= ROTATE_AMOUNT;
}

void Ship::applyThrust()
{
	Velocity tempV;
	tempV.setDx(THRUST_AMOUNT * (-sin(float(M_PI) / 180.0 * rotation)));
	tempV.setDy(THRUST_AMOUNT * (cos(float(M_PI) / 180.0 * rotation)));

	Velocity totalVel = velocity + tempV;
	const int thrustLimit = 10;

	//Check to see if the addition of thrust will be under the threshold
	if (totalVel.getDx() * (-sin(float(M_PI) / 180.0 * rotation)) <= thrustLimit && totalVel.getDy() * (cos(float(M_PI) / 180.0 * rotation)) <= thrustLimit
		&& totalVel.getDx() * (-sin(float(M_PI) / 180.0 * rotation)) >= -thrustLimit && totalVel.getDy() * (cos(float(M_PI) / 180.0 * rotation)) >= -thrustLimit)
	{
		velocity.add(tempV);
	}

	setFlame(true);
}

void Ship::draw()
{
	//std::cerr << "Ship drawn at: " << getPoint() << std::endl;
	drawShip(getPoint(), getRotation(), getFlame());
	setFlame(false);
}

