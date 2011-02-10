#pragma once

#include "use_sdl.h"
#include "vector.h"

extern SDL_Surface* screen;

typedef linear_math::Vector<3> Vector;

struct Material
{
	Material() : color( 0.2, 0.2, 0.2 ), diffuse( 0.2 ), reflectiv( 0 ) {}
	Vector color;
	float diffuse;
	float reflectiv;
};

struct Primitiv
{
	virtual float Intersect( Vector& origion, Vector& ray ) = 0;
	virtual Vector Normal( Vector& intersection ) = 0;
	Material material;
};

struct Sphere : public Primitiv
{
	float Intersect( Vector& origion, Vector& ray );
	Vector Normal( Vector& intersection );
	Vector position;
	float radius;
};

struct Plane : public Primitiv
{
	float Intersect( Vector& origion, Vector& ray );
	Vector Normal( Vector& intersection );
	Vector point1, point2;
};

struct Light
{
	Light() : color( 1, 1, 1 ) {}
	Vector position;
	Vector color;
};

	/*	float diff = dot * prim->GetMaterial()->GetDiffuse();
				// add diffuse component to ray color
				a_Acc += diff * prim->GetMaterial()->GetColor() * light->GetMaterial()->GetColor();
			}*/
