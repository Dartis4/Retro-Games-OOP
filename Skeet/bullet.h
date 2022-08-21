#ifndef bullet_h
#define bullet_h

#define _USE_MATH_DEFINES
#include <cmath>

#include "uiDraw.h"

#define BULLET_SPEED 10.0

#include "flyingobject.h"
class Bullet : public FlyingObject
{
private:
	float angle;

public:
	Bullet() : angle(60) { object = 'b'; }

	float getAngle() const { return angle; }
	void setAngle(float angle) { this->angle = angle; }

	virtual void draw();

	void fire(Point position, float angle);
};

#endif