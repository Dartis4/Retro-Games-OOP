#ifndef BIGBIRD_H
#define BIRD_H

#include "bird.h"
class BigBird : public Bird
{
public:
	BigBird() : Bird(30, 10, 6) { object = 'B'; }
	BigBird(Point point, Velocity velocity) : Bird(30, 10, 6, point, velocity) { object = 'B'; }

	virtual void draw();
};

#endif