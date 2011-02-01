#pragma once

#include <Windows.h>
#include "SDL/include/SDL.h"

#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")

#include "objects.h"
#include "vector.h"

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
	Color inline CastRay( Vector& direction );
	Color colors[800*600];
	Vector origion;
	Circle circles[NUMBER_OF_CIRCLES];
	Plane planes[NUMBER_OF_PLANES];
	Light lights[NUMBER_OF_LIGTHS];
};
