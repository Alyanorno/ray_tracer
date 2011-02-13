#pragma once

#include "use_sdl.h"
#include "vector.h"

extern SDL_Surface* screen;

typedef linear_math::Vector<3> Vector;

struct Material
{
	Material( Vector _color = Vector( 0.2, 0.2, 0.2 ),
		  float _diffuse = 0.4,
		  float _specular = 0.4,
		  float _reflection = 0.5,
		  float _refraction = 0.0 ) : color( _color ),
					     diffuse( _diffuse ),
					     specular( _specular ),
					     reflection( _reflection ),
					     refraction( _refraction ) {}
	Vector color;
	float diffuse;
	float specular;
	float reflection;
	float refraction;
};

struct Primitiv
{
	virtual float Intersect( Vector& origion, Vector& ray ) = 0;
	virtual Vector Normal( Vector& intersection ) = 0;
	Material material;
};

struct Sphere : public Primitiv
{
	virtual float Intersect( Vector& origion, Vector& ray );
	Vector Normal( Vector& intersection );
	Vector position;
	float radius;
};

struct Plane : public Primitiv
{
	virtual float Intersect( Vector& origion, Vector& ray );
	Vector Normal( Vector& intersection );
	Vector point0, point, normal;
};

struct Light
{
	Light() : color( 1, 1, 1 ) {}
	Vector position;
	Vector color;
};
