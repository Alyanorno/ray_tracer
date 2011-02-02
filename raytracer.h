#pragma once

#include "use_sdl.h"
#include "objects.h"
#include "vector.h"

extern SDL_Surface* screen;

#define NUMBER_OF_CIRCLES 3
#define NUMBER_OF_PLANES 1
#define NUMBER_OF_LIGTHS 2

typedef linear_math::Vector<3> Vector;

class Raytracer
{
public:
	void Initialize();
	void Draw();
private:
	Uint32 inline CastRay( Vector& direction );
	Vector _origion;
	Circle _circles[NUMBER_OF_CIRCLES];
	Plane _planes[NUMBER_OF_PLANES];
	Light _lights[NUMBER_OF_LIGTHS];
};
