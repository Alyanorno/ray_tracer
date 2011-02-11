#include "raytracer.h"

void Raytracer::Initialize()
{
	_origion = Vector( 0, 0, -500 );

	for( int i(0); i < NUMBER_OF_PRIMITIVS; i++ )
		_primitivs[i] = new Sphere();

	//set all values of the different objects
	((Sphere*)_primitivs[0])->material.color = Vector( 1, 0, 0 );
	((Sphere*)_primitivs[0])->radius = 100;
	((Sphere*)_primitivs[0])->position = Vector( 0, 0, 2 );

	((Sphere*)_primitivs[1])->material.color = Vector( 0, 1, 0 );
	((Sphere*)_primitivs[1])->radius = 100;
	((Sphere*)_primitivs[1])->position = Vector( 100, 0, 0 );

	((Sphere*)_primitivs[2])->material.color = Vector( 0, 0, 1 );
	((Sphere*)_primitivs[2])->radius = 100;
	((Sphere*)_primitivs[2])->position = Vector( 0, 100, 0 );

	_lights[0].position = Vector( 100, -100, -100 );
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
	Uint32 result = 0xff000000;
	float distans = 1000;
	int ID = -1;

	//Check for collision
	for( int i(0); i < NUMBER_OF_PRIMITIVS; i++ )
	{
		float intersection = _primitivs[i]->Intersect( origion, direction );
		if( intersection && intersection < distans )
		{
			distans = intersection;
			ID = i;
		}
	}

	if( ID != -1 )
		result = LightRay( origion + direction * (distans - 0.1), ID );

	return result;
}

Uint32 inline Raytracer::LightRay( Vector& origion, int ID )
{
	float r = 0, g = 0, b = 0;
	for( int i(0); i < NUMBER_OF_LIGHTS; i++ )
	{
		float distans = (_lights[i].position - origion).Length();
		Vector direction = _lights[i].position - origion;
		direction.Normalize();

		float dot = _primitivs[ID]->Normal( origion ).Dot( direction );
		if( dot < 0 )
			break;
		
		//Check for collision
		for( int ii(0); ii < NUMBER_OF_PRIMITIVS; ii++ )
		{
			float intersection = _primitivs[ii]->Intersect( origion,
								        direction );
			if( intersection && intersection < distans )
			{
				goto end_of_i_loop;
			}
		}
		float diffuse = dot * _primitivs[ID]->material.diffuse;
		r += diffuse * _primitivs[ID]->material.color[0] * _lights[i].color[0];
		g += diffuse * _primitivs[ID]->material.color[1] * _lights[i].color[1];
		b += diffuse * _primitivs[ID]->material.color[2] * _lights[i].color[2];
end_of_i_loop:;
	}
	return SDL_MapRGB( screen->format, 255*r, 255*g, 255*b );
}
