#include "Vector3.h"

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	radius = 0.0f;
	teta = 0.0f;
	fi = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->calculateSphericalCoords();
}

void Vector3::calculateSphericalCoords()
{
	radius = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(x, 2.0));
	teta = acos(z / radius);
	fi = atan(x / z);
}

void Vector3::calculateDecartCoords()
{
	x = radius * sin(teta) * sin(fi);
	y = radius * cos(teta);
	z = radius * sin(teta) * cos(fi);
}


void Vector3::X(const float value)
{
	x = value;
	calculateSphericalCoords();
}

void Vector3::Y(const float value)
{
	y = value;
	calculateSphericalCoords();
}

void Vector3::Z(const float value)
{
	z = value;
	calculateSphericalCoords();
}

void Vector3::Radius(const float value)
{
	radius = value;
	calculateDecartCoords();
}

void Vector3::Teta(const float value)
{
	teta = value;
	calculateDecartCoords();
}

void Vector3::Fi(const float value)
{
	fi = value;
	calculateDecartCoords();
}

float Vector3::X() const 
{
	return x;
}

float Vector3::Y() const
{
	return y;
}

float Vector3::Z() const
{
	return z;
}

float Vector3::Radius() const
{
	return radius;
}

float Vector3::Teta() const
{
	return teta;
}

float Vector3::Fi() const
{
	return fi;
}