#ifndef bullet_h
#define bullet_h

#include <cmath>
#include "uiDraw.h"

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#define _USE_MATH_DEFINES

// TODO Bullets being fired correctly (correct direciton, velocity, and dying at the correct time)

#include "flyingObject.h"
class Bullet : public FlyingObject
{
private:
	float angle;
	int life;

public:
	Bullet() : angle(0), life(0) { }
	Bullet(int life) : angle(0), life(life) { }

	float getAngle() const { return angle; }
	void setAngle(float angle) { this->angle = angle; }

	int getLife() const { return life; }
	void setLife(int life) { this->life = life; }
	void decreaseLife() { life--; }

	virtual void draw();

	void fire(Point position, Velocity velocity, float angle);
};

#endif /* bullet_h */
