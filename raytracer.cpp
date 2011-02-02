#include "raytracer.h"

void Raytracer::Initialize()
{
	//set all values of the different objects
	_circles[0].color = Color::White;
	_circles[1];
	_circles[2];
	_planes[0];
	_lights[1];
	_lights[2];
}

void Raytracer::Draw()
{
	SDL_LockSurface( screen );
	for( int i(0); i < screen->w * screen->h; i++ )
		*((Uint32*)screen->pixels + i) = CastRay( Vector(0,0,0) );
	SDL_UnlockSurface( screen );
}

Uint32 inline Raytracer::CastRay( Vector& direction )
{
	Uint32 result = 0x000f;

	//Check for collision with circles
	for( int i(0); i < NUMBER_OF_CIRCLES; i++ )
	{
		float intersection = _circles[i].Intersect( _origion, direction );
		if( intersection )
		{
			return _circles[i].color;
		}
	}

	//Check for collision with planes
	for( int i(0); i < NUMBER_OF_PLANES; i++ )
	{
		float intersection = _planes[i].Intersect( _origion, direction );
		if( intersection )
		{
			return _planes[i].color;
		}
	}

	return result;
}
