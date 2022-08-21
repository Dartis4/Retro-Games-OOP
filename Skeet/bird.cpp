#include "bird.h"

#include "uiDraw.h"

int Bird::hit()
{
	std::cerr << "Hit with " << getHP() << "! ";
	this->setHP(hp - 1);
	std::cerr << getHP() << " hp left.\n";
	if (this->getHP() <= 0)
	{
		this->kill();
		std::cerr << "Reward for kill: " << reward << object << std::endl;
		return this->reward;
	}
	else
		return 1;
}