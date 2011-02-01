#pragma once

#include "vector.h"

typedef linear_math::Vector<3> Vector;

struct Color
{
	unsigned char r, g, b, a;
};

struct Circle
{
	float Intersect( Vector& origion, Vector& ray );
	Vector position;
	float radius;
};

struct Plane
{
	float Intersect( Vector& origion, Vector& ray );
	Vector point1, point2;
};

// Not used for now
struct Light
{
	Vector position;
	Color color;
};
