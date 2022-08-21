#include "flyingobject.h"

#include <iostream>

void FlyingObject::kill()
{
	this->alive = false;

	switch (object)
	{
		case 'b':
			std::cerr << "bullet killed.\n";
			break;
		case 's':
			std::cerr << "std bird killed.\n";
			break;
		case 't':
			std::cerr << "tough bird killed.\n";
			break;
		case 'x':
			std::cerr << "sacred bird killed.\n";
			break;
		case 'B':
			std::cerr << "big bird killed.\n";
	}
	
}

void FlyingObject::advance()
{
	velocity.advancePoint(position);
	std::cerr << object << " Position: " << position.getX() << "," << position.getY() << " Velocity: " << velocity.getDx() << " " << velocity.getDy() << std::endl;
}
