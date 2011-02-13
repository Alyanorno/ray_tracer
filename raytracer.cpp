#include "raytracer.h"

void Raytracer::Initialize()
{
	_origion = Vector( 0, 0, -500 );

	for( int i(0); i < NUMBER_OF_PRIMITIVS; i++ )
		_primitivs[i] = new Sphere();
	_primitivs[3] = new Plane();

	//set all values of the different objects
	((Sphere*)_primitivs[0])->material.color = Vector( 1, 0, 0 );
	((Sphere*)_primitivs[0])->radius = 100;
	((Sphere*)_primitivs[0])->position = Vector( -150, -150, 0 );

	((Sphere*)_primitivs[1])->material.color = Vector( 0, 1, 0 );
	((Sphere*)_primitivs[1])->radius = 100;
	((Sphere*)_primitivs[1])->position = Vector( 100, 0, 0 );

	((Sphere*)_primitivs[2])->material.color = Vector( 0, 0, 1 );
	((Sphere*)_primitivs[2])->radius = 100;
	((Sphere*)_primitivs[2])->position = Vector( 0, 100, 0 );

	((Plane*)_primitivs[3])->material.color = Vector( 0.5, 0.5, 0.5 );
	((Plane*)_primitivs[3])->point = Vector( 300, 300, 0 );
	((Plane*)_primitivs[3])->point0 = Vector( 0, 0, 300 );
	((Plane*)_primitivs[3])->normal = Vector( 0, 0, -1 );//Vector( 0, 1, 0).Cross( Vector( 1, 0, 0 ));
	((Plane*)_primitivs[3])->normal.Normalize();
	((Plane*)_primitivs[3])->material.reflection = 1;
	((Plane*)_primitivs[3])->material.diffuse = 0.5;
	((Plane*)_primitivs[3])->material.specular = 0;

	_lights[0].position = Vector( 100, -100, -200 );
	_lights[1].position = Vector( -200, -200, -200 );
}

void Raytracer::Draw()
{
	SDL_LockSurface( screen );
	int i;
#pragma omp parallel for
	for( i = 0; i < screen->w * screen->h; i++ )
	{
		Vector direction( i%screen->w - screen->w/2, i/screen->h - screen->h/2, 0 );
		direction -= _origion;
		direction.Normalize();
		Vector color = CastRay( _origion, direction );
		Uint8 r = 255*(color[0] > 1 ? 1 : color[0]);
		Uint8 g = 255*(color[1] > 1 ? 1 : color[1]);
		Uint8 b = 255*(color[2] > 1 ? 1 : color[2]);

		// Antialiazing
		if( i - 1 > 0 && i - screen->h > 0 )
		{
			Uint8 leftR, leftG, leftB;
			SDL_GetRGB( *((Uint32*)screen->pixels + (i - 1)),
				    screen->format,
				    &leftR,
				    &leftG,
				    &leftB );
			Uint8 upR, upG, upB;
			SDL_GetRGB( *((Uint32*)screen->pixels + (i - screen->w)),
				    screen->format,
				    &upR,
				    &upG,
				    &upB );

			r = (r + leftR + leftR) / 3;
			g = (g + leftG + leftG) / 3;
			b = (b + leftB + leftB) / 3;
		}

		*((Uint32*)screen->pixels + i) = SDL_MapRGB( screen->format, r, g, b );
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
		return LightRay( origion + direction * (distans - 0.1), direction, *_primitivs[ID] );
}

Vector inline Raytracer::LightRay( Vector& origion, Vector& hit_direction, Primitiv& primitiv, int deapth )
{
	Vector color( 0, 0, 0 );
	float r = 0, g = 0, b = 0;
	for( int i(0); i < NUMBER_OF_LIGHTS; i++ )
	{
		float distans = (_lights[i].position - origion).Length();

		Vector direction = _lights[i].position - origion;
		direction.Normalize();

		Vector normal = primitiv.Normal( origion );
		float dot = normal.Dot( direction );
		if( dot < 0 )
			continue;
		
		//Check for collision
		for( int ii(0); ii < NUMBER_OF_PRIMITIVS; ii++ )
		{
			float intersection = _primitivs[ii]->Intersect( origion,
								        direction );
			if( intersection && intersection < distans )
				goto end_of_i_loop;
		}

		// Diffuse
		if( primitiv.material.diffuse )
		{
			float diffuse = dot * primitiv.material.diffuse;
			color += primitiv.material.color * _lights[i].color * diffuse;
		}

		// Specular
		if( primitiv.material.specular )
		{
			Vector reflection = direction - normal * (2 * normal.Dot( direction ) );
			dot = reflection.Dot( hit_direction );
			if( dot > 0 )
			{
				float specular = powf( dot, 20 ) * primitiv.material.specular;
				color += primitiv.material.color * specular;
			}
		}

		// Reflection
		if( primitiv.material.reflection > 0 && deapth < 3 )
			color += CastRay( origion,
					  hit_direction - normal * (2 * normal.Dot( hit_direction ) ))
//			       * primitiv.material.color
			       * primitiv.material.reflection;
		
		// Refraction
		if( primitiv.material.refraction > 0 && deapth < 3 )
		{
			// TO DO: Refraction
		}
end_of_i_loop:;
	}
	return color;
}
