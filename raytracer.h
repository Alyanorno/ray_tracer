#pragma once

#include <omp.h>
#include "use_sdl.h"
#include "objects.h"
#include "vector.h"

extern SDL_Surface* screen;

#define NUMBER_OF_PRIMITIVS 4
#define NUMBER_OF_LIGHTS 2

typedef linear_math::Vector<3> Vector;

class Raytracer
{
friend void Input();
public:
	void Initialize();
	void Draw();
private:
	float inline Intersection( Ray& ray, float distans );
	float inline Intersection( Ray& ray, float* distans );
	Vector inline CastRay( Ray& ray );
	Vector inline LightRay( Ray& ray, Primitiv& primitiv );
	Vector _origion;

	Primitiv* _primitivs[NUMBER_OF_PRIMITIVS];
	Light _lights[NUMBER_OF_LIGHTS];
};
