#pragma once

#include "use_sdl.h"
#include "objects.h"
#include "vector.h"

extern SDL_Surface* screen;

#define NUMBER_OF_PRIMITIVS 4
#define NUMBER_OF_LIGHTS 1

typedef linear_math::Vector<3> Vector;

class Raytracer
{
friend void Input();
public:
	void Initialize();
	void Draw();
private:
	Uint32 inline CastRay( Vector& origion, Vector& direction );
	Uint32 inline LightRay( Vector& origion, int ID );
	Vector _origion;

	Primitiv* _primitivs[NUMBER_OF_PRIMITIVS];
	/*Sphere _spheres[NUMBER_OF_SPHERES];
	Plane _planes[NUMBER_OF_PLANES];*/
	Light _lights[NUMBER_OF_LIGHTS];
};
