#include "raytracer.h"

void Raytracer::Initialize()
{
	_origion = Vector( 0, 0, -500 );
	//set all values of the different objects
	_spheres[0].color = Color::Red;
	_spheres[0].radius = 100;
	_spheres[0].position = Vector( 0, 0, 2 );

	_spheres[1].color = Color::Green;
	_spheres[1].radius = 100;
	_spheres[1].position = Vector( 100, 0, 0 );

	_spheres[2].color = Color::Blue;
	_spheres[2].radius = 100;
	_spheres[2].position = Vector( 0, 100, 0 );

	_planes[0];
	_lights[0].position = Vector( 100, -100, -100 );

	_spheres[3].color = Color::White;
	_spheres[3].radius = 2;
	_spheres[3].position = _lights[0].position + 1;
}

void Raytracer::Draw()
{
	SDL_LockSurface( screen );
	for( int i(0); i < screen->w * screen->h; i++ )
	{
		Vector direction( i%screen->w- screen->w/2, i/screen->h - screen->h/2, 0 );
		direction -= _origion;
		direction.Normalize();
		*((Uint32*)screen->pixels + i) = CastRay( _origion, direction );
	}
	SDL_UnlockSurface( screen );
}

Uint32 inline Raytracer::CastRay( Vector& origion, Vector& direction )
{
	Uint32 result = Color::Black;
	float distans = 1000;
	Vector normal;

	//Check for collision with spheres
	for( int i(0); i < NUMBER_OF_SPHERES; i++ )
	{
		float intersection = _spheres[i].Intersect( origion, direction );
		if( intersection && intersection < distans )
		{
			result = _spheres[i].color;
			distans = intersection;
			normal = direction * distans - _spheres[i].position;
		}
	}

	//Check for collision with planes
	for( int i(0); i < NUMBER_OF_PLANES; i++ )
	{
		float intersection = _planes[i].Intersect( origion, direction );
		if( intersection && intersection < distans )
		{
			result = _planes[i].color;
			distans = intersection;
			normal = direction * distans - _spheres[i].position;
		}
	}

	if( result != Color::Black )
		result = LightRay( direction * distans, normal, result );

	return result;
}

Uint32 inline Raytracer::LightRay( Vector& origion, Vector& normal, Uint32 color )
{
	for( int i(0); i < NUMBER_OF_LIGHTS; i++ )
	{
		float distans = (origion - _lights[i].position).Length();
		Vector direction = origion - _lights[i].position;
		direction.Normalize();

		//if( normal.Dot( direction ) > 0 )
		//	goto end_of_light_loop;

		//Check for collision with spheres
		for( int ii(0); ii < NUMBER_OF_SPHERES - 1; ii++ )
		{
			float intersection = _spheres[i].Intersect( _lights[i].position,
								    direction );
			if( intersection && intersection < distans )
				goto end_of_light_loop;
		}

		//Check for collision with planes
		for( int ii(0); ii < NUMBER_OF_PLANES; ii++ )
		{
			float intersection = _planes[i].Intersect( _lights[i].position,
								    direction );
			if( intersection && intersection > distans )
				goto end_of_light_loop;
		}

		return Color::Blue + Color::Green;
end_of_light_loop:;
	}

	return color;
}
