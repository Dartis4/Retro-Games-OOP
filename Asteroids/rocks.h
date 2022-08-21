#ifndef rocks_h
#define rocks_h

#include "flyingObject.h"
#include "point.h"
#include "velocity.h"

#include <iostream>
using namespace std;

#define BIG_ROCK_SIZE    16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE  4

#define BIG_ROCK_SPIN    2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN  10

class Rock : public FlyingObject
{
protected:
	float rotation;
	float spinAmount;
	int type;
	int value;

public:
	Rock(): FlyingObject(), rotation(0), spinAmount(0), type(0), value(0) { }
	Rock(Point position, Velocity velocity) : FlyingObject(position, velocity), rotation(random(0, 360)), spinAmount(0), type(0), value(0) { }
	Rock(Point tl, Point br) : FlyingObject(tl, br), rotation(random(0, 360)), spinAmount(0), type(0), value(0) { }
	~Rock() { cerr << "Rock deleted.\n"; }

	float getRotation() const { return rotation;  }
	void setRotation(float rotation) { this->rotation = rotation; }

	int getValue() const { return value; }
	void setValue(int value) { this->value = value; }
 
	int getType() const { return type; }
	void setType(int type) { this->type = type; }

	void spin() { setRotation(rotation + spinAmount); }
};

class BigRock : public Rock
{
public:
	BigRock() : Rock() { }
	BigRock(Point tl, Point br) : Rock(tl, br)
	{ 
		setValue(1);
		setType(3);

		int lowX  = tl.getX();
		int highX = br.getX();
		int lowY  = br.getY();
		int highY = tl.getY();
		
		this->setPoint(Point(random(lowX, highX), random(lowY, highY)));
		
		float randDx = float(random(-1.0, 1.0));
		float randDy = float(random(-1.0, 1.0));
		if (randDx == 0)
			randDx++;
		if (randDy == 0)
			randDy++;

		this->setVelocity(Velocity(randDx, randDy));
		cerr << "Initial big rock value. Position: " << getPoint().getX() << ", " << getPoint().getY() << " Velocity: " << getVelocity().getDx() << ", " << getVelocity().getDy() << endl;
		
		int s = random(-1, 1);
		if (s == -1)
		{
			spinAmount = -BIG_ROCK_SPIN;
		}
		if (s == 1)
		{
			spinAmount = BIG_ROCK_SPIN;
		}
		else
		{
			spinAmount = BIG_ROCK_SPIN;
		}
	}

	virtual void draw();
};

class MediumRock : public Rock
{
public:
	MediumRock() : Rock() { }
	MediumRock(Point position, Velocity velocity) : Rock(position, velocity) 
	{ 
		setValue(2);
		setType(2);
		int s = random(-1, 1);
		if (s == -1)
		{
			spinAmount = -MEDIUM_ROCK_SPIN;
		}
		if (s == 1)
		{
			spinAmount = MEDIUM_ROCK_SPIN;
		}
		else
		{
			spinAmount = MEDIUM_ROCK_SPIN;
		}
	}

	virtual void draw();
};

class SmallRock : public Rock
{
public:
	SmallRock() : Rock() { }
	SmallRock(Point position, Velocity velocity) : Rock(position, velocity)
	{
		setValue(3);
		setType(1);

		int s = random(-1, 1);
		if (s == -1)
		{
			spinAmount = -SMALL_ROCK_SPIN;
		}
		if (s == 1)
		{
			spinAmount = SMALL_ROCK_SPIN;
		}
		else
		{
			spinAmount = SMALL_ROCK_SPIN;
		}
	}

	virtual void draw();
};

#endif /* rocks_h */
