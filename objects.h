#pragma once

#include "use_sdl.h"
#include "vector.h"

extern SDL_Surface* screen;

typedef linear_math::Vector<3> Vector;

struct Sphere
{
	float Intersect( Vector& origion, Vector& ray );
	Vector position;
	float radius;
	Uint32 color;
};

struct Plane
{
	float Intersect( Vector& origion, Vector& ray );
	Vector point1, point2;
	Uint32 color;
};

// Not used for now
struct Light
{
	Vector position;
	Uint32 color;
};
