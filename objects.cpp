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

float inline Length( float x )
{
	return x < 0 ? -x : x;
}
float Plane::Intersect( Vector& origion, Vector& direction )
{
	//(P-P0)*n = 0;
	//P = dL+L0
	//d = (P0-L0)*n / L*n
	float value = point0[2] - origion[2];
	float distans = normal[2] * value / normal.Dot( direction );
	if( distans < 0 )
		return 0;

	Vector intersection = origion + direction * distans;
	if( Length( point0[0] + intersection[0] ) > Length( point[0] )
	 || Length( point0[1] + intersection[1] ) > Length( point[1] ))
		return 0;

	return distans;
}
Vector Plane::Normal( Vector& intersection )
{
	return normal;
}
