#include "raytracer.h"

void Raytracer::Initialize()
{
	_origion = Vector( 0, 0, 1 );
	//set all values of the different objects
	_spheres[0].color = Color::Red;
	_spheres[0].radius = 1;
	_spheres[0].position = Vector( 0, 0.9, 10 );
	_spheres[1].color = Color::Green;
	_spheres[1].position = Vector( 1, 0, 0 );
	_spheres[2].color = Color::Blue;
	_spheres[1].position = Vector( 0, 1, 0 );
	_planes[0];
	_lights[1];
	_lights[2];
}

void Raytracer::Draw()
{
	SDL_LockSurface( screen );
	for( int i(0); i < screen->w * screen->h; i++ )
	{
		Vector ray( i%screen->w - screen->w/2, int(i/screen->h) - screen->h/2, 1 );
		*((Uint32*)screen->pixels + i) = CastRay( ray );
	}

	SDL_UnlockSurface( screen );
}

Uint32 inline Raytracer::CastRay( Vector& direction )
{
	Uint32 result = Color::Black;
	float distans = 0;

	//Check for collision with spheres
	for( int i(0); i < 1/*NUMBER_OF_CIRCLES*/; i++ )
	{
		float intersection = _spheres[i].Intersect( _origion, direction );
		if( intersection > distans )
		{
			result = _spheres[i].color;
			distans = intersection;
		}
	}

	//Check for collision with planes
	for( int i(0); i < NUMBER_OF_PLANES; i++ )
	{
		float intersection = _planes[i].Intersect( _origion, direction );
		if( intersection > distans )
		{
			result = _planes[i].color;
			distans = intersection;
		}
	}

	return result;
}
