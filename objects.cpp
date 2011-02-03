#include "objects.h"

float Sphere::Intersect( Vector& origion, Vector& ray )
{
/*	position = Vector( 0, 0, 20 );
	ray = Vector( i, i, i-10000 )	
	_origion = Vector( 0, 0, 1 ); */

/* bool hitSphere(const ray &r, const sphere &s, float &t) 
 { 
    // Intersection of a ray and a sphere
    // Check the articles for the rationale
    // NB : this is probably a naive solution
    // that could cause precision problems
    // but that will do it for now. 
    vecteur dist = s.pos - r.start; 
    float B = r.dir * dist; //Dot product
    float D = B*B - dist * dist + s.size * s.size; //Dot^2 - Dot(dist,dist) + size^2
    if (D < 0.0f) 
        return false; *//*
v = ray
u = distans
puv = ( v . u ) / v.Length * v*/

	Vector distans = position - origion;

	float dot = ray.Dot( distans );
	if( dot < 0 )
		return 0;
	if( dot / ray.Length() < radius )
		return 0;
	else
		return distans.Length() - radius;
}

float Plane::Intersect( Vector& origion, Vector& ray )
{
	return 0;
}
