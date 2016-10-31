/*************************************************************************
* File: lander.cpp
*
* Description: Implementations of the method bodies of the lander class
*
*************************************************************************/

#include "point.h"
#include "lander.h"
#include "uiDraw.h"

#include <cstdlib>
#include <ctime>

using namespace std;

//default constructor
Lander::Lander()
{
	//range: -200 - 200
	pos.setX(rand()% 401 + (-200));
	pos.setY(300);
}

//getter for the ship's position
Point Lander::getPoint() const
{
	return pos;
}

//setter for the ship's position
void Lander::setPoint(Point p)
{
	pos = p;
}

//getter for the fuel
int Lander::getFuel()
{
	if (fuelLevel < 0)
		return 0;
	else
		return fuelLevel;
}

//setter for the ship's fuel level
void Lander::setFuel(int f)
{
	if (f < 0)
		cout << "Error: fuel level cannot be less than zero" << endl;
	else
		fuelLevel = f;
}

//returns a boolean value - false is dead, true is alive
bool Lander::isAlive()
{
	return alive;
}

//setter for the alive boolean variable
void Lander::setAlive(bool a)
{
	alive = a;
}

//returns a boolean varibale - false is not landed, true is landed
bool Lander::isLanded()
{
	return landed;
}

//setter for the landed boolean variable
void Lander::setLanded(bool l)
{
	landed = l;
}

//getter for the velocity
Velocity Lander::getVelocity() const
{
	return velocity;
}

/**********************************************
 * applies gravity: velocity of y - gravity
 **********************************************/
void Lander::applyGravity(float gravity)
{
	velocity.setDy(velocity.getDy() - gravity);
}

/**********************************************
* applies the ship's bottom thruster
**********************************************/
void Lander::applyThrustBottom()
{
	if (fuelLevel > 0 && !isLanded())
	{
		fuelLevel -= 3;
		float y = velocity.getDy();
		y += .3;
		velocity.setDy(y);
	}
}

/**********************************************
* applies the ship's left thruster
**********************************************/
void Lander::applyThrustLeft()
{
	if (fuelLevel > 0 && !isLanded())
	{
		fuelLevel--;
		float x = velocity.getDx();
		x += .1;
		velocity.setDx(x);
	}
}

/**********************************************
* applies the ship's right thruster
**********************************************/
void Lander::applyThrustRight()
{
	if (fuelLevel > 0 && !isLanded())
	{
		fuelLevel--;
		float x = velocity.getDx();
		x -= .1;
		velocity.setDx(x);
	}
}

/*****************************************************
* draws the ship by calling the drawLander() function
* from uiDraw.cpp
******************************************************/
void Lander::draw()
{
	drawLander(pos);
}

/*********************************************************
* checks if the ship can thrust
*    ship will be able to thrust as long as there is fuel
*    and the ship is alive
**********************************************************/
bool Lander::canThrust()
{
	if (fuelLevel > 0 && alive)
		return true;
	else 
		return false;
}

/*****************************************************************************
* advances the ship's movement by adding the velocities to the x and y values
******************************************************************************/
void Lander::advance()
{
	pos.setX(pos.getX() + velocity.getDx());
	pos.setY(pos.getY() + velocity.getDy());
}