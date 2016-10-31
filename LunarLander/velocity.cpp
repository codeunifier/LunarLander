/******************************************************************************
* File: velocity.cpp
*
* Description: Implementation of the method bodies of the velocity class
*
******************************************************************************/

#include "velocity.h"

using namespace std;

//default constructor
Velocity::Velocity()
{
	velX = 0.0;
	velY = 0.0;
}

//non-default constructor accepts two float values for x and y velocities
Velocity::Velocity(float x, float y)
{
	velX = x;
	velY = y;
}

//getter for the x velocity
float Velocity::getDx()
{
	return velX;
}

//getter for the y velocity
float Velocity::getDy()
{
	return velY;
}

//setter for the x velocity
void Velocity::setDx(float x)
{
	velX = x;
}

//setter for the y velocity
void Velocity::setDy(float y)
{
	velY = y;
}