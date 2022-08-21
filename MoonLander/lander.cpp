/******************************************
 * File: lander.cpp
 ******************************************/

#include "lander.h"
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"
#include "uiInteract.h"

using namespace std;

/***************************************
 * LANDER :: CAN THRUST
 * checks if the lander can thrust
 ***************************************/
bool Lander::canThrust()
{
	if (this->getFuel() > 0)
		return true;
	else
		return false;
}

/***************************************
 * LANDER :: SET FUEL
 * sets the fuel of lander to passed value
 ***************************************/
void Lander::setFuel(int fuel)
{
	this->fuel = fuel;
	if (this->fuel < 0)
		this->fuel = 0;
}

/***************************************
 * LANDER :: APPLY GRAVITY
 * applies gravity to lander velocity
 ***************************************/
void Lander::applyGravity(float gravity)
{
	this->velocity.add(Velocity(0, -gravity));
}

/***************************************
 * LANDER :: APPLY THRUST LEFT
 * applies thrust left amount to lander velocity
 ***************************************/
void Lander::applyThrustLeft()
{
	if (canThrust())
	{
		this->velocity.add(Velocity(0.1, 0));
		useFuel(1);
	}	
}

/***************************************
 * LANDER :: APPLY THRUST RIGHT
 * applies thrust right amount to lander velocity
 ***************************************/
void Lander::applyThrustRight()
{
	if (canThrust())
	{
		this->velocity.add(Velocity(-0.1, 0));
		useFuel(1);
	}
	
}

/***************************************
 * LANDER :: APPLY THRUST BOTTOM
 * applies thrust down amount to lander velocity
 ***************************************/
void Lander::applyThrustBottom()
{
	if (canThrust())
	{
		this->velocity.add(Velocity(0, 0.3));
		useFuel(3);
	}
}

/***************************************
 * LANDER :: ADVANCE
 * advances the lander to its new position
 * based on it's velocity
 ***************************************/
void Lander::advance()
{
	this->velocity.advancePoint(position);
}

/***************************************
 * LANDER :: DRAW
 * draws lander at new position
 ***************************************/
void Lander::draw() const
{
	drawLander(position);
}

/***************************************
 * LANDER :: RESET
 * resets the lander position
 ***************************************/
void Lander::reset()
{
	position.setX(0);
	position.setY(160);
	setAlive(true);
	setLanded(false);
	setFuel(500);
	velocity.setDx(0);
	velocity.setDy(0);
}
