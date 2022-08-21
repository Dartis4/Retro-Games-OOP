#include "standardbird.h"

void StandardBird::draw()
{
	std::cerr << "drawing std bird...\n";
	drawCircle(getPoint(), getRadius());
}