/***********************************************************************
 * Header File:
 *    LANDER : A class representing the moon lander
 * Author:
 *    Dane Artis
 * Summary:
 *    Handles the behavior of the Moon Lander
 ************************************************************************/

#ifndef LANDER_H
#define LANDER_H

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"
#include "uiInteract.h"

/********************************************
 * LANDER
 * The moon lander
 ********************************************/
class Lander
{
private:
	Point position;
	Velocity velocity;
	bool alive;
	bool landed;
	int fuel;

public:
	Lander()
	{
		position.setX(0);
		position.setY(160);
		setAlive(true);
		setLanded(false);
		setFuel(0);
	}

	Point getPoint() const { return position; }
	Velocity getVelocity() const { return  velocity;  }
	bool isAlive() const { return alive;  }
	bool isLanded() const { return landed;  }
	int getFuel() const { return fuel;  }
	bool canThrust();
		
	void setLanded(bool land) { this->landed = land; }
	void setAlive(bool alive) { this->alive = alive; }
	void setFuel(int fuel);

	void applyGravity(float gravity);
	void applyThrustLeft();
	void applyThrustRight();
	void applyThrustBottom();
	void useFuel(int usage) { setFuel(getFuel() - usage); }

	void advance();
	void draw() const;

	void reset();
};

#endif