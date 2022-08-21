#include "bullet.h"

#include <iostream>

void Bullet::draw()
{
	std::cerr << "drawing bullet...\n";
	drawDot(getPoint());
}

void Bullet::fire(Point position, float angle)
{
	std::cerr << "Fire!\n";

	this->setPoint(position);
	this->setAngle(angle);
	
	velocity.setDx(BULLET_SPEED * (-cos(float(M_PI) / 180.0 * angle)));
	velocity.setDy(BULLET_SPEED * (sin(float(M_PI) / 180.0 * angle)));
}
