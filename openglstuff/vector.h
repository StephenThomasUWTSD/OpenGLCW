#ifndef VECTOR_H
#define VECTOR_H

class Vector

{

public:

	//construct
	Vector(float x, float y, float z);
	void Scale(float s);
	void Add(Vector & v1);
	void Add(Vector & v1, Vector & v2);
	float Dot(Vector &v1);
	//private:
	float x;
	float y;
	float z;
};

Vector operator -(const Vector & v2, const Vector & v1);

class Ray
{
public:
	Ray();
	float LinePointDistanceSqd(const Vector & p);
	void SetOrigin(const Vector & p);
	void SetDirection(const Vector & d);

private:
	Vector dir;
	Vector Origin;
};
#endif