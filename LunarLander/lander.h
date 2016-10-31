#ifndef LANDER_H
#define LANDER_H

#include "velocity.h"

class Lander
{
public:
	//constructors
	Lander();
	//getters and setters
	Point getPoint() const;
	void setPoint(Point);
	int getFuel();
	void setFuel(int);
	bool isAlive();
	void setAlive(bool);
	bool isLanded();
	void setLanded(bool);
	Velocity getVelocity() const;
	//other
	void applyGravity(float);
	void applyThrustBottom();
	void applyThrustLeft();
	void applyThrustRight();
	void draw();
	void advance();
	bool canThrust();
private:
	Point pos;
	Velocity velocity;
	int fuelLevel;
	bool alive = true;
	bool landed = false;
};

#endif
