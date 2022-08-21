#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

class FlyingObject
{
protected:
	Point position;
	Velocity velocity;
	bool alive;

public:
	FlyingObject()                                  :                                         alive(true) { }
	FlyingObject(Point position, Velocity velocity) : position(position), velocity(velocity), alive(true) { }
	FlyingObject(Point tl, Point br)                :                                         alive(true) { }

	Point getPoint() const { return position; }
	Velocity getVelocity() const { return velocity; }

	void setPoint(Point point) { position = point; }
	void setVelocity(Velocity velocity) { this->velocity = velocity; }

	bool isAlive() const { return alive; }
	void kill();
	void revive();

	virtual void draw() = 0;
	void advance();
};



#endif /* flyingObject_h */
