#include "raytracer.h"

void Raytracer::Initialize()
{
	//set all values of the different objects
	circles[0];
	circles[1];
	circles[2];
	planes[0];
	lights[1];
	lights[2];
}

void Raytracer::Draw()
{
	for( int i(0); i < 800*600; i++ )
		colors[i] = CastRay( Vector(0,0,0) );
	//Use SDL to draw the picture
}

Color inline Raytracer::CastRay( Vector& direction )
{
	Color result;

	//Check for collision with circles
	for( int i(0); i < NUMBER_OF_CIRCLES; i++ )
	{
		float intersection = circles[i].Intersect( origion, direction );
		if( intersection )
		{
			//temp
			result.r = 0;
			result.g = 0;
			result.b = 0;
			result.a = 255;
			//end temp
			return result;
		}
	}

	//Check for collision with planes
	for( int i(0); i < NUMBER_OF_PLANES; i++ )
	{
		float intersection = planes[i].Intersect( origion, direction );
		if( intersection )
		{
			//temp
			result.r = 0;
			result.g = 0;
			result.b = 0;
			result.a = 255;
			//end temp
			return result;
		}
	}

	//temp
	result.r = 0;
	result.g = 0;
	result.b = 0;
	result.a = 255;
	//end temp
	return result;
}
