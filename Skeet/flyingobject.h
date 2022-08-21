#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H

#include "point.h"
#include "velocity.h"

class FlyingObject
{
protected:
	Point position;
	Velocity velocity;
	bool alive;
	char object;

public:
	FlyingObject() { this->alive = true; object = '.'; }

	Point getPoint() const { return position; }
	Velocity getVelocity() const { return velocity; }

	void setPoint(Point point) { position = point;  }
	void setVelocity(Velocity velocity) { this->velocity = velocity;  }

	bool isAlive() const { return alive; }
	void kill();

	void draw() { }
	void advance();
};

#endif
