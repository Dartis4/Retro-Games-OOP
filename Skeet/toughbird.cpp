#include "toughbird.h"

void ToughBird::draw()
{
	std::cerr << "drawing tough bird...\n";
	drawToughBird(getPoint(), getRadius(), getHP());
}