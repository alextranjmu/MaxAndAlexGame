#pragma once
#include <cmath>

class Vector
{
private:
	double xComponent;
	double yComponent;
	
public:
	Vector(double heading, double magnitude);
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
	double getHeading();
	double getMagnitude();
	void setHeading(double heading);
	void setMagnitude(double magnitude);

};