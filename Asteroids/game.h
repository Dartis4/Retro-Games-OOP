/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include "point.h"
#include "velocity.h"
#include "flyingObject.h"
#include "ship.h"
#include "rocks.h"
#include "bullet.h"
#include "uiDraw.h"
#include "uiInteract.h"

#include <list>

#define CLOSE_ENOUGH 15

class Game
{
private:
	Point topLeft;
	Point bottomRight;

	int highScore = 0;
	int score;
	int choice;

	Ship ship;
	std::list<Rock*> rocks;
	std::list<Bullet*> bullets;

public:
	Game() : score(0), choice(0) {}
	Game(Point tl, Point br);
	~Game() { }

	bool isOnScreen(const Point& point);
	void advanceBullets();
	void advanceRocks();
	void advanceShip();
	Rock* createRocks();
	void handleCollisions();
	void cleanUpZombies();
	float getClosestDistance(const FlyingObject& obj1, const FlyingObject& obj2) const;

	void wrap(FlyingObject & object);
	void handleInput(const Interface& ui);
	void draw(const Interface& ui);
	void advance();
};


#endif /* GAME_H */