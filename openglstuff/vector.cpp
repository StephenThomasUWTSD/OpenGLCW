
#include "Vector.h"
//construct
Vector::Vector(float myx, float myy, float myz)
{
	x = myx;
	y = myy;
	z = myz;
}

void Vector::Scale(float s)
{
	x = s*x;
	y = s*y;
	z = s*z;
}

void Vector::Add(Vector & v1, Vector & v2)
{
	v1.x = v2.x + v1.x;
	v1.y = v2.y + v1.y;
	v1.z = v2.z + v1.z;
}
void Vector::Add(Vector & v1)
{
	x = x + v1.x;
	y = y + v1.y;
	z = z + v1.z;
}
Vector operator -(const Vector & v2, const Vector & v1)
{
	return Vector(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
}
float Vector::Dot(Vector &v1)
{
	return (x * v1.x) + (y * v1.y) + (z * v1.z);
}



Ray::Ray() :dir(0, 0, 0), Origin(0, 0, 0)
{
}


void Ray::SetOrigin(const Vector & p)
{
	Origin.x = p.x;
	Origin.y = p.y;
	Origin.z = p.z;
}
void Ray::SetDirection(const Vector & d)
{
	dir.x = d.x;
	dir.y = d.y;
	dir.z = d.z;
}
float Ray::LinePointDistanceSqd(const Vector & p)
{
	Vector w = p - Origin; //p-origin
	float vsq = dir.Dot(dir); //direction squared
	float wsq = w.Dot(w); //w squared
	float proj = w.Dot(dir); //w.v
	return wsq - proj*proj / vsq; //the line point closest distance
}