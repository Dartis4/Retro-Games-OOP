#include "sacredbird.h"

void SacredBird::draw()
{
	std::cerr << "drawing sacred bird...\n";
	drawSacredBird(getPoint(), getRadius());
}