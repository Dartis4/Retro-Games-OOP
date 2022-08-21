/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
#include <iostream>
using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 20 //makes wrapping smooth
#define NUMBER_OF_ROCKS 5 //asserts the number of asteroids available
#define BULLET_LIFE 40

Game::Game(Point tl, Point br) : topLeft(tl), bottomRight(br), score(0), choice(0)
{
   while (rocks.size() < NUMBER_OF_ROCKS && ship.isAlive())
   {
      cerr << "Creating rock...";
      rocks.push_back(createRocks());
   }
}

/**************************************************************************
* GAME :: ADVANCE BULLETS
* Advances the bullets to their new positions. Wraps if needed.
**************************************************************************/
void Game::advanceBullets()
{
   //cerr << "Advancing bullets\n";
   for (list<Bullet*>::iterator bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt)
   {
      if ((*bulletIt)->getLife() <= 0)
      {
         (*bulletIt)->kill();
      }
      if ((*bulletIt)->isAlive())
      {
         (*bulletIt)->advance();
         (*bulletIt)->decreaseLife();
         if (!isOnScreen((*bulletIt)->getPoint()))
         {
            wrap(**bulletIt);
         }
      }
   }
}

/**************************************************************************
* GAME :: ADVANCE ROCKS
* Advance the rocks to their new positions and wraps if needed. Create more
* if needed.
**************************************************************************/
void Game::advanceRocks()
{
   if (rocks.size() < NUMBER_OF_ROCKS && ship.isAlive()) // This will make it so more rocks spawn when most of them are destroyed
   {
      cerr << "Creating rock...";
      rocks.push_back(createRocks());
   }

   int count = 1;
   for (list<Rock*>::iterator it = rocks.begin(); it != rocks.end(); ++it)
   {
      if ((*it)->isAlive()) // check if the rock is alive
      {
         //cerr << "Advancing rocks...\n";
         (*it)->advance();
         (*it)->spin();
         if (!isOnScreen((*it)->getPoint()))
         {
            wrap(**it);
         }
      }
      else // if not, get rid of it
      {
         cerr << count << " rock destroyed.\n";
         delete* it;
         it = rocks.erase(it);
      }
   }
}

/**************************************************************************
* GAME :: ADVANCE SHIP
* Advance the ship to it's new position and wraps if needed.
**************************************************************************/
void Game::advanceShip()
{
   if (!(score == 0 && ship.getRotation() == 0 && ship.getPoint() == Point(0, 0) && ship.getVelocity() == Velocity(0, 0)))
   {
      ship.setInvincible(false);
   }
   //cerr << "Advancing ship\n";
   if (ship.isAlive())
   {
      ship.advance();
      if (!isOnScreen(ship.getPoint()))
      {
         wrap(ship);
      }
   }  
}

/**************************************************************************
* GAME :: CREATE ROCKS
* Creates a big rock and adds it to the list
**************************************************************************/
Rock* Game::createRocks()
{
   Rock* newRock = NULL;
   
   newRock = new BigRock(topLeft, bottomRight);

   cerr << "rock created.\n";

   return newRock;
}

/**************************************************************************
* GAME :: IS ON SCREEN
* Determines if a given point is on the screen.
**************************************************************************/
void Game::handleCollisions()
{
   //cerr << "Handling collisions...\n";

   // Check for ship and rock collisons
   for (list<Rock*>::iterator rockIt = rocks.begin(); rockIt != rocks.end(); ++rockIt)
   {
      if (ship.isAlive())
      {
         if (CLOSE_ENOUGH >= getClosestDistance(ship, **rockIt))
         {
            ship.kill();
            std::cerr << "Ship destroyed.\n";
            (*rockIt)->kill();
         }
      }
   }

   //Check for bullets colliding with rocks
   for (list<Bullet*>::iterator bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt)
   {
      for (list<Rock*>::iterator rockIt = rocks.begin(); rockIt != rocks.end(); ++rockIt)
      {
         if ((*bulletIt)->isAlive() && (*rockIt)->isAlive())
         {
            if (CLOSE_ENOUGH >= getClosestDistance(**bulletIt, **rockIt))
            {
               (*rockIt)->kill();
               (*bulletIt)->kill();

               score += (*rockIt)->getValue();

               //Spawn 2 med and 1 s rock from big
               if ((*rockIt)->getType() == 3) 
               {
                  Velocity aVel1 = (*rockIt)->getVelocity();
                  Velocity aVel2 = (*rockIt)->getVelocity();
                  Velocity aVel3 = (*rockIt)->getVelocity();
                  
                  aVel1.setDy(aVel1.getDy() + 1);
                  aVel2.setDy(aVel2.getDy() - 1);
                  aVel3.setDx(aVel3.getDx() + 1);

                  Rock* newMR1 = new MediumRock((*rockIt)->getPoint(), aVel1);
                  rocks.push_back(newMR1);

                  Rock* newMR2 = new MediumRock((*rockIt)->getPoint(), aVel2);
                  rocks.push_back(newMR2);

                  Rock* newS1 = new SmallRock((*rockIt)->getPoint(), aVel3);
                  rocks.push_back(newS1);
               }

               // Spawn 2 small from med
               if ((*rockIt)->getType() == 2) 
               {
                  Velocity aVel1 = (*rockIt)->getVelocity();
                  Velocity aVel2 = (*rockIt)->getVelocity();

                  aVel1.setDx(aVel1.getDx() + 3);
                  aVel2.setDx(aVel2.getDx() - 3);

                  Rock* newS1 = new SmallRock((*rockIt)->getPoint(), aVel1);
                  rocks.push_back(newS1);

                  Rock* newS2 = new SmallRock((*rockIt)->getPoint(), aVel2);
                  rocks.push_back(newS2);
               }
            }
         }
      }
   }
}

/**************************************************************************
* GAME :: CLEAN UP ZOMBIES
* Frees up any memory that needs to be freed
**************************************************************************/
void Game::cleanUpZombies()
{
   list<Bullet*>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      Bullet* pBullet = *bulletIt;

       if (!pBullet->isAlive())
      {
         delete* bulletIt;
         bulletIt = bullets.erase(bulletIt);
      }
      else if (bulletIt != bullets.end())
      {
         bulletIt++;
      }
   }

   list<Rock*>::iterator rockIt = rocks.begin();
   while (rockIt != rocks.end())
   {
      Rock* pRock = *rockIt;

      if (!pRock->isAlive())
      {
         delete* rockIt;
         rockIt = rocks.erase(rockIt);
      }
      else if (rockIt != rocks.end())
      {
         rockIt++;
      }
   }
}

/**************************************************************************
* GAME :: HANDLE INPUT
* Handles the users input from the keyboard
**************************************************************************/
void Game::handleInput(const Interface& ui)
{
   if (ui.isUp())
   {
      if (ship.isAlive())
         ship.applyThrust();
   }

   if (ui.isLeft())
   {
      if (ship.isAlive())
         ship.turnLeft();

      if (!ship.isAlive())
      {
         choice = 1;
      }
   }

   if (ui.isRight())
   {
      if (ship.isAlive())
         ship.turnRight();

      if (!ship.isAlive())
      {
         choice = 2;
      }
   }

   if (ui.isSpace())
   {
      if (ship.isAlive())
      {
         Bullet * newBullet = new Bullet(BULLET_LIFE);
         newBullet->fire(ship.getPoint(), ship.getVelocity(), ship.getRotation());
         bullets.push_back(newBullet);
      }
      if (!ship.isAlive())
      {
         if (choice == 1)
         {
            if (score > highScore)
            {
               highScore = score;

            }
            score = 0;
            choice = 0;
            ship.resurrect(Point(0, 0), Velocity(0, 0));
            cerr << "Restarting game...\n";
         }

         if (choice == 2)
         {
            exit(0); //Exit game
            cerr << "Goodbye\n";
         }
      }
   }
}

/**************************************************************************
* GAME :: DRAW
* Draws all the objects on the screen
**************************************************************************/
void Game::draw(const Interface& ui)
{
   for (int i = 0; i < rocks.size(); i++)
   {
      for (list<Rock*>::iterator it = rocks.begin(); it != rocks.end(); ++it)
      {
         //cerr << "Drawing rock...";
         if ((*it)->isAlive())
         {
            (*it)->draw();
            //cerr << "rock drawn.\n";
         }
      }
   }

   if (ship.isAlive())
   {
      ship.draw();
   }

   if (!ship.isAlive())
   {
      drawText(Point(-75, 150), "Would you like to play again?");
      drawText(Point(-100, 130), "Restart");
      drawText(Point(85, 130), "Quit");

      if (choice == 1) //Restart
      {
         drawRect(Point(-81, 135), 42, 15, 0);
      }
      if (choice == 2) //Quit
      {
         drawRect(Point(97, 135), 27, 15, 0);
      }
   }

   for (list<Bullet*>::iterator bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt)
   {
      if ((*bulletIt)->isAlive())
      {
         (*bulletIt)->draw();
      }
   }

   Point scoreLocation;
   scoreLocation.setX(topLeft.getX() + 5);
   scoreLocation.setY(topLeft.getY() - 5);
   drawNumber(scoreLocation, score);

   drawText(Point(topLeft.getX() + 5, bottomRight.getY() + 6), "Your highscore: ");

   Point hScoreLocation;
   hScoreLocation.setX(topLeft.getX() + 98);
   hScoreLocation.setY(bottomRight.getY() + 16);
   drawNumber(hScoreLocation, highScore);
}

/**************************************************************************
* GAME :: ADVANCE
* Handles the game loop by calling each objects advance and the collision 
* and clean up methods.
**************************************************************************/
void Game::advance()
{
   advanceShip();
   advanceRocks();
   advanceBullets();

   handleCollisions();
   cleanUpZombies();
}

/**************************************************************************
* GAME :: WRAP
* If the passed object is off the screen in the game, it will push the 
* object to the other side.
**************************************************************************/
void Game::wrap(FlyingObject & object)
{
   const int screenWidth =  bottomRight.getX() - topLeft.getX();
   const int screenHeight = topLeft.getY()     - bottomRight.getY();

   const int offLeft = topLeft.getX(); // -200
   const int offRight = bottomRight.getX(); // 200
   const int offUp = topLeft.getY(); // 200
   const int offDown = bottomRight.getY(); // -200

   if (object.getPoint().getX() <= offLeft)
   {
      //std::cerr << "Wrapping right\n";
      Point tPoint;
      tPoint.setX(object.getPoint().getX() + screenWidth);
      tPoint.setY(object.getPoint().getY());
      object.setPoint(tPoint);
   }

   if (object.getPoint().getX() >= offRight)
   {
      //std::cerr << "Wrapping left\n";
      Point tPoint;
      tPoint.setX(object.getPoint().getX() - screenWidth);
      tPoint.setY(object.getPoint().getY());
      object.setPoint(tPoint);
   }

   if (object.getPoint().getY() >= offUp)
   {
      //std::cerr << "Wrapping down\n";
      Point tPoint;
      tPoint.setX(object.getPoint().getX());
      tPoint.setY(object.getPoint().getY() - screenHeight);
      object.setPoint(tPoint);
   }

   if (object.getPoint().getY() <= offDown)
   {
      //std::cerr << "Wrapping up\n";
      Point tPoint;
      tPoint.setX(object.getPoint().getX());
      tPoint.setY(object.getPoint().getY() + screenHeight);
      object.setPoint(tPoint);
   }
}

/**************************************************************************
* GAME :: IS ON SCREEN
* Determines if a given point is on the screen.
**************************************************************************/
bool Game::isOnScreen(const Point& point)
{
   return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
      && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
      && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
      && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

