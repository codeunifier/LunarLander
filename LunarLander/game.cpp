/*************************************************************
 * File: game.cpp
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

#include <iostream>

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
         lander.setAlive(false);
   
      // check for just landed
      if (justLanded())
         lander.setLanded(true);
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
	   if (!frozen)
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
	   else
	   {
		   if (ui.isRight())
			   lander.setFuel(500);
		   else if (ui.isDown())
			   lander.setFuel(300);
		   else if (ui.isLeft())
			   lander.setFuel(150);

		   if (ui.isSpace())
			   frozen = false;
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

   if (frozen)
   {
	   Point p = { 0, 100 };
	   drawText(p, "Press space to start.");
	   p = { 0, 85 };
	   drawText(p, "Easy: right arrow key");
	   p = { 0, 70 };
	   drawText(p, "Medium: down arrow key");
	   p = { 0, 55 };
	   drawText(p, "Hard: left arrow key");
   }

   if (lander.isLanded())
   {
      drawText(Point(), "You have successfully landed!");
   }
   
   if (!lander.isAlive())
   {
      drawText(Point(), "You have crashed!");
   }
   
   if (lander.canThrust() && !frozen && !lander.isLanded())
   {
      drawLanderFlames(lander.getPoint(), ui.isDown(), ui.isLeft(), ui.isRight());
   }
   
   Point fuelLocation;
   fuelLocation.setX(topLeft.getX() + 5);
   fuelLocation.setY(topLeft.getY() - 5);
   
   drawNumber(fuelLocation, lander.getFuel());

   // draw ground
   ground.draw();
}

//setter for the frozen boolean variable
void Game::setFrozen(bool f)
{
	frozen = f;
}

//getter for the frozen boolean variable
bool Game::getFrozen() const
{
	return frozen;
}