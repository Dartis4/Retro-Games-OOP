#ifndef TOUGHBIRD_H
#define TOUGHBIRD_H

#include "bird.h"
class ToughBird : public Bird
{
public:
	ToughBird() : Bird(15, 3, 3) { object = 't'; }
	ToughBird(Point point, Velocity velocity) : Bird(15, 3, 3, point, velocity) { object = 't'; }

	virtual void draw();
};

#endif