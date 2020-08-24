#define _USE_MATH_DEFINES

#include "Vector.h"
#include "Character.h"
#include <cmath>

Vector::Vector(double heading, double magnitude)
{
	setX(0);
	setY(0);
	setMagnitude(magnitude);
	setHeading(heading);
}

Vector::Vector(int x1, int y1, int x2, int y2)
{
	double x_dist = x2 - x1;
	double y_dist = y2 - y1;
	double y = abs(y_dist);
	double x = abs(x_dist);
	if (x_dist > 0 && y_dist > 0) // Down-Right
	{
		setHeading(atan(x / y) + 3 * M_PI / 2);
	}
	if (x_dist < 0 && y_dist > 0) // Down-Left
	{
		setHeading(atan(y / x) + M_PI);
	}
	if (x_dist > 0 && y_dist < 0) // Up-Right
	{
		setHeading(atan(y / x));
	}
	if (x_dist < 0 && y_dist < 0) // Up-Left
	{
		setHeading(atan(x / y) + M_PI / 2);
	}
	if (x_dist == 0 || y_dist == 0)
	{
		// fuck
		setHeading(-9999999999999999999);
	}
	setMagnitude(x_dist * x_dist + y_dist * y_dist);
}

Vector::Vector(int direction, double magnitude)
{
	setMagnitude(magnitude);
	switch (direction)
	{
	case RIGHT:
		setHeading(0.0);
		break;
	case DOWN_RIGHT:
		setHeading(M_PI / 4.0);
		break;
	case DOWN:
		setHeading(M_PI / 2.0);
		break;
	case DOWN_LEFT:
		setHeading(3.0 * M_PI / 4.0);
		break;
	case LEFT:
		setHeading(M_PI);
		break;
	case UP_LEFT:
		setHeading(5.0 * M_PI / 4.0);
		break;
	case UP:
		setHeading(3.0 * M_PI / 2.0);
		break;
	case UP_RIGHT:
		setHeading(7.0 * M_PI / 4.0);
		break;
	}
}

double Vector::getX()
{
	return xComponent;
}

double Vector::getY()
{
	return yComponent;
}

void Vector::setX(double x)
{
	xComponent = x;
}

void Vector::setY(double y)
{
	yComponent = y;
}

double Vector::getHeading()
{
	return atan2(getY(), getX());
}


double Vector::getMagnitude()
{
	return sqrt(xComponent * xComponent + yComponent * yComponent);
}

void Vector::setHeading(double heading)
{
	this->heading = heading;
	double magnitude = getMagnitude();
	setX(cos(heading) * magnitude);
	setY(sin(heading) * magnitude);
}

void Vector::appendHeading(double angle)
{
	heading += angle;
	double magnitude = getMagnitude();
	setX(cos(heading) * magnitude);
	setY(sin(heading) * magnitude);
}

void Vector::setMagnitude(double magnitude)
{
	double oldMagnitude = getMagnitude();

	// Prevent divide by zero if we attempt to set the magnitude of a vector
	// with no heading.
	if (oldMagnitude < .0000001)
	{
		xComponent = magnitude;
	}
	else
	{
		xComponent *= magnitude / oldMagnitude;
		yComponent *= magnitude / oldMagnitude;
	}
}
