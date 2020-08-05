#include "Vector.h"

Vector::Vector(double heading, double magnitude)
{
	setX(0);
	setY(0);
	setMagnitude(magnitude);
	setHeading(heading);
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
