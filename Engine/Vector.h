#pragma once
#include <cmath>

class Vector
{
private:
	double xComponent;
	double yComponent;


	static int const NO_DIRECTION = 0;
	static int const UP = 1;
	static int const DOWN = 2;
	static int const LEFT = 3;
	static int const RIGHT = 4;
	static int const UP_LEFT = 5;
	static int const UP_RIGHT = 6;
	static int const DOWN_LEFT = 7;
	static int const DOWN_RIGHT = 8;


public:
	Vector(double heading, double magnitude);
	Vector(int direction, double magnitude);
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
	double getHeading();
	double getMagnitude();
	void setHeading(double heading);
	void setMagnitude(double magnitude);

};