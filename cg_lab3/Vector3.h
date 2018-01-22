// #pragma once
#include <cmath>

class Vector3
{
private:
	float x;
	float y;
	float z;

	float radius;
	float teta;
	float fi;

	void calculateDecartCoords();
	void calculateSphericalCoords();
public: 
	Vector3();
	Vector3(float x, float y, float z);
	void X(const float value);
	void Y(const float value);
	void Z(const float value);
	void Radius(const float value);
	void Teta(const float value);
	void Fi(const float value);
	float X() const;
	float Y() const;
	float Z() const;
	float Radius() const;
	float Teta() const;
	float Fi() const;
};
