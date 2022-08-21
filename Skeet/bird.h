#ifndef bird_h
#define bird_h

#include "flyingobject.h"

#include "uiDraw.h"

class Bird :  public FlyingObject
{
protected:
	int radius;
	int hp;
	int reward;
	

public:
	Bird() : FlyingObject(), radius(0), hp(0), reward(0) { }
	Bird(int radius, int hp, int reward) : FlyingObject() { setRadius(radius); setHP(hp); setReward(reward); }
	Bird(int radius, int hp, int reward, Point point, Velocity velocity) : FlyingObject() { setRadius(radius); setHP(hp); setReward(reward); setPoint(point); setVelocity(velocity); }

	int getRadius() const { return radius; } 
	int getHP() const { return hp; }
	int getDeathBonus() const { return reward; }

	void setRadius(int radius) { this->radius = radius; }
	void setHP(int hp) { this->hp = hp; }
	void setReward(int reward) { this->reward = reward; }

	int hit();

	virtual void draw() = 0;
};

#endif