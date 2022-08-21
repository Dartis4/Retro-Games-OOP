#include "flyingObject.h"

#include <iostream>

void FlyingObject::kill()
{
	this->alive = false;
}

void FlyingObject::revive()
{
	this->alive = true;
}

void FlyingObject::advance()
{
	velocity.advancePoint(position);
}

