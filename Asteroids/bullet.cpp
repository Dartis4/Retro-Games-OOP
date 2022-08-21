#include "bullet.h"

#define M_PI 3.14159265358979323846

void Bullet::draw()
{
	drawDot(getPoint());
}

void Bullet::fire(Point position, Velocity velocity, float angle)
{
	setPoint(position);

	Velocity tempV = velocity;
	tempV.addDx(BULLET_SPEED * (-sin(float(M_PI) / 180.0 * angle)));
	tempV.addDy(BULLET_SPEED * (cos(float(M_PI) / 180.0 * angle)));
	
	setVelocity(tempV);
}
