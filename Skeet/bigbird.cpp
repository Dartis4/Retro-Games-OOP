#include "bigbird.h"

void BigBird::draw()
{
	std::cerr << "drawing big bird...\n";
	drawToughBird(getPoint(), getRadius(), getHP());
}