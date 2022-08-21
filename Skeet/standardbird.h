#ifndef STANDARDBIRD_H
#define STANDARDBIRD_H

#include "bird.h"
class StandardBird : public Bird
{
public:
	StandardBird() : Bird(15, 1, 1) { object = 's'; }
	StandardBird(Point point, Velocity velocity) : Bird(15, 1, 1, point, velocity) { object = 's'; }

	virtual void draw();
};

#endif