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
	int number_of_pixels = screen->w * screen->h;
#pragma omp parallel for
	for( i = 0; i < number_of_pixels; i++ )
	{
		Vector direction( i%screen->w - screen->w/2, i/screen->h - screen->h/2, 0 );
		direction -= _origion;
		direction.Normalize();
		Vector color = CastRay( _origion, direction );
		Uint8 r = 255*(color[0] > 1 ? 1 : color[0]);
		Uint8 g = 255*(color[1] > 1 ? 1 : color[1]);
		Uint8 b = 255*(color[2] > 1 ? 1 : color[2]);

		// Antialiazing
		if( i - 1 > 0 && i - screen->w > 0 )
		{
			linear_math::Vector<3,Uint8> left, up, leftUp;
			SDL_GetRGB( *((Uint32*)screen->pixels + (i - 1)),
				    screen->format,
				    &left[0],
				    &left[1],
				    &left[2] );
			SDL_GetRGB( *((Uint32*)screen->pixels + (i - screen->w)),
				    screen->format,
				    &up[0],
				    &up[1],
				    &up[2] );
			SDL_GetRGB( *((Uint32*)screen->pixels + (i - screen->w - 1)),
				    screen->format,
				    &leftUp[0],
				    &leftUp[1],
				    &leftUp[2] );

			r = (r + left[0] + up[0] + leftUp[0]) / 4;
			g = (g + left[1] + up[1] + leftUp[1]) / 4;
			b = (b + left[2] + up[2] + leftUp[2]) / 4;
		}

		*((Uint32*)screen->pixels + i) = SDL_MapRGB( screen->format, r, g, b );
	}
	SDL_UnlockSurface( screen );
}

float inline Raytracer::Intersection( Vector& origion, Vector& direction, float distans )
{
	for( int i(0); i < NUMBER_OF_PRIMITIVS; i++ )
	{
		float intersection = _primitivs[i]->Intersect( origion, direction );
		if( intersection && intersection < distans )
			return -1;
	}
	return 0;
}
float inline Raytracer::Intersection( Vector& origion, Vector& direction, float* distans )
{
	int ID = -1;
	for( int i(0); i < NUMBER_OF_PRIMITIVS; i++ )
	{
		float intersection = _primitivs[i]->Intersect( origion, direction );
		if( intersection && intersection < *distans )
		{
			*distans = intersection;
			ID = i;
		}
	}
	return ID;
}

Vector inline Raytracer::CastRay( Vector origion, Vector direction )
{
	float distans = 1000;
	int ID = Intersection( origion, direction, &distans );

	if( ID == -1 )
		return Vector( 0, 0, 0 );
	else
	{
		origion = origion + direction * (distans - 0.1);
		Vector color;
		color = LightRay( origion, direction, *_primitivs[ID] );

		Vector normal = _primitivs[ID]->Normal( origion );
		// Reflection
		if( _primitivs[ID]->material.reflection > 0 )
			color += CastRay( origion,
					  direction - normal * (2 * normal.Dot( direction ) ))
//			       * _primitivs[ID]->material.color
			       * _primitivs[ID]->material.reflection;
		
		// Refraction
		if( _primitivs[ID]->material.refraction > 0 )
		{
			// TO DO: Refraction
		}
		return color;
	}
}

Vector inline Raytracer::LightRay( Vector& origion, Vector& hit_direction, Primitiv& primitiv )
{
	Vector color( 0, 0, 0 );
	Vector normal = primitiv.Normal( origion );
	for( int i(0); i < NUMBER_OF_LIGHTS; i++ )
	{
		float distans = (_lights[i].position - origion).Length();

		Vector direction = _lights[i].position - origion;
		direction.Normalize();

		float dot = normal.Dot( direction );
		if( dot < 0 )
			continue;
		
		//Check for collision
		if( Intersection( origion, direction, distans ) == -1 )
			continue;

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

	}
	return color;
}
