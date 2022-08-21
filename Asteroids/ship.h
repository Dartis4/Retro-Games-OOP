#ifndef ship_h
#define ship_h

#include <cmath>
#include "flyingObject.h"

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#define _USE_MATH_DEFINES

#include <iostream>

class Ship : public FlyingObject
{
private:
	int size = SHIP_SIZE;
	float rotation;
	bool thrust;
	bool flame;
	bool invincible;

public:
	Ship() : FlyingObject(), rotation(0), thrust(true), flame(false), invincible(true) { }
	~Ship() { }

	int getSize() const { return size; }
	float getRotation() const { return rotation; }
	bool canThrust() const { return thrust; }
	bool getFlame() const { return flame; }
	bool getInvincible() const { return invincible; }

	void setRotation(float rotation) { this->rotation = rotation; }
	void setThrust(bool thrustable) { thrust = thrustable; }
	void setFlame(bool flame) { this->flame = flame; }
	void resurrect(Point position, Velocity velocity);
	void setInvincible(bool kryptonite) { invincible = kryptonite; }

	void turnLeft();
	void turnRight();
	void applyThrust();

	virtual void draw();
};

#endif /* ship_h */
