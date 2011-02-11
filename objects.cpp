#include "objects.h"

float Sphere::Intersect( Vector& origion, Vector& direction )
{
	Vector distans = origion - position;

	float dot = - distans.Dot( direction );
	if( dot < 0 )
		return 0;
	float det = dot * dot - distans.Dot( distans ) + radius * radius;
	if( det < 0 )
		return 0;
	else
		return dot - sqrt( det );
}
Vector Sphere::Normal( Vector& intersection )
{
	Vector normal = (intersection - position) * radius;
	normal.Normalize();
	return normal;
}

float Plane::Intersect( Vector& origion, Vector& ray )
{
	return 0;
}
Vector Plane::Normal( Vector& intersection )
{
	return Vector( 0, 0, 0 );
}
