#ifndef SACREDBIRD_H
#define SACREDBIRD_H

#include "bird.h"
class SacredBird : public Bird
{
public:
	SacredBird() : Bird(15, 1, -10) { object = 'x'; }
	SacredBird(Point point, Velocity velocity) : Bird(15, 1, -10, point, velocity) { object = 'x'; }

	virtual void draw();
};

#endif