/*************************************************************
 * File: game.cpp
 * Author: Br. Burton
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
 *************************************************************/

#include "game.h"

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "ground.h"
#include "lander.h"

/******************************************
 * GAME :: JUST LANDED
 * Did we land successfully?
 ******************************************/
bool Game :: justLanded() const
{
   bool landed = false;
   
   Point platformCenter = ground.getPlatformPosition();
   int width = ground.getPlatformWidth();

   float xDiff = lander.getPoint().getX() - platformCenter.getX();
   float yDiff = lander.getPoint().getY() - platformCenter.getY();

   float margin = width / 2.0;
   
   if (fabs(xDiff) < margin)
   {
      // between edges
      
      if (yDiff < 4 && yDiff >= 0)
      {
         // right above it
         
         if (fabs(lander.getVelocity().getDx()) < 3 && fabs(lander.getVelocity().getDy()) < 3)
         {
            // we're there!
            landed = true;
         }
      }
   }
   return landed;
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   if (lander.isAlive() && !lander.isLanded())
   {
      // advance the lander
      lander.applyGravity(GRAVITY_AMOUNT);
      lander.advance();
   
      // check for crash
      if (!ground.isAboveGround(lander.getPoint()))
      {
         lander.setAlive(false);
      }
   
      // check for just landed
      if (justLanded())
      {
         lander.setLanded(true);
      }
   }
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
   if (lander.isAlive() && !lander.isLanded())
   {
   
      if (ui.isDown())
      {
         lander.applyThrustBottom();
      }
      
      if (ui.isLeft())
      {
         lander.applyThrustLeft();
      }
      
      if (ui.isRight())
      {
         lander.applyThrustRight();
      }
   }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
   lander.draw();

   if (lander.isLanded())
   {
      drawText(Point(0, 185), "You have successfully landed!");
   }
   
   if (!lander.isAlive())
   {
      drawText(Point(bottomRight.getX() - 115, topLeft.getY() - 15), "You have crashed!");
   }
   
   if (lander.canThrust())
   {
      drawLanderFlames(lander.getPoint(), ui.isDown(), ui.isLeft(), ui.isRight());
   }

   
   Point fuelLocation;
   fuelLocation.setX(topLeft.getX() + 5);
   fuelLocation.setY(topLeft.getY() - 5);
   
   drawNumber(fuelLocation, lander.getFuel());

   // draw ground
   ground.draw();


   // This will give the user the option to replay the game or quit out.
   if (!lander.isAlive() || lander.isLanded())
   {
      static bool leftC = false; // restart option
      static bool rightC = false; // quit option

      drawText(Point(-75, 150), "Would you like to play again?");
      drawText(Point(-100, 130), "Restart");
      drawText(Point(85, 130), "Quit");

      // user chooses restart
      if (ui.isLeft())
      {
         leftC = true;
         rightC = false;
      }

      // user chooses quit
      if (ui.isRight())
      {
         leftC = false;
         rightC = true;
      }

      // user can select
      if (ui.isSpace())
      {
         if (rightC)
         {
            exit(0); // closes game
         }
         if (leftC)
         {
            // resets the game
            lander.reset();
            ground.generateGround();
            leftC = false;
            rightC = false;
         }
      }

      // draws the square to show which option is selected
      if (leftC == true && rightC == false)
      {
         drawRect(Point(-81, 135), 42, 15, 0);
      }
      if (leftC == false && rightC == true)
      {
         drawRect(Point(97, 135), 27, 15, 0);
      }
   }
}
