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

/*	((Plane*)_primitivs[3])->material.color = Vector( 1, 0, 1 );
	((Plane*)_primitivs[3])->point = Vector( 0, 0, 0 );
	((Plane*)_primitivs[3])->point0 = Vector( 0, 0, 0 );
	((Plane*)_primitivs[3])->normal = Vector( 0, 0, 0 ); */

	_lights[0].position = Vector( 100, -100, -100 );
	_lights[1].position = Vector( -100, 100, -100 );
}

void Raytracer::Draw()
{
	SDL_LockSurface( screen );
	for( int i(0); i < screen->w * screen->h; i++ )
	{
		Vector direction( i%screen->w- screen->w/2, i/screen->h - screen->h/2, 0 );
		direction -= _origion;
		direction.Normalize();
		Vector color = CastRay( _origion, direction );
		*((Uint32*)screen->pixels + i) = SDL_MapRGB( screen->format,
							     255*color[0],
							     255*color[1], 
							     255*color[2] );
	}
	SDL_UnlockSurface( screen );
}

Vector inline Raytracer::CastRay( Vector& origion, Vector& direction )
{
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

	if( ID == -1 )
		return Vector( 0, 0, 0 );
	else
		return LightRay( origion + direction * (distans - 0.1), direction, ID );
}

Vector inline Raytracer::LightRay( Vector& origion, Vector& hit_direction, int ID, int deapth )
{
	Vector color( 0, 0, 0 );
	float r = 0, g = 0, b = 0;
	for( int i(0); i < NUMBER_OF_LIGHTS; i++ )
	{
		float distans = (_lights[i].position - origion).Length();

		Vector direction = _lights[i].position - origion;
		direction.Normalize();

		Vector normal = _primitivs[ID]->Normal( origion );
		float dot = normal.Dot( direction );
		if( dot < 0 )
			break;
		
		//Check for collision
		for( int ii(0); ii < NUMBER_OF_PRIMITIVS; ii++ )
		{
			float intersection = _primitivs[ii]->Intersect( origion,
								        direction );
			if( intersection && intersection < distans )
				goto end_of_i_loop;
		}

		float diffuse = dot * _primitivs[ID]->material.diffuse;
		color += _primitivs[ID]->material.color * _lights[i].color * diffuse;

		Vector reflection = direction - normal * (2 * normal.Dot( direction ) );
		dot = reflection.Dot( hit_direction );
		if( dot > 0 )
		{
			float specular = powf( dot, 20 ) * _primitivs[ID]->material.specular;
			color += _primitivs[ID]->material.color * specular;
		}

		if( _primitivs[ID]->material.reflection > 0 && deapth < 3 )
			color += CastRay( origion,
					  hit_direction - normal * (2 * normal.Dot( hit_direction ) ))
//			       * _primitivs[ID]->material.color
			       * _primitivs[ID]->material.reflection;
end_of_i_loop:;
	}
	return color;
}
