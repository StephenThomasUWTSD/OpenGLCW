#pragma once
#include <glut.h>

class Box
{
public:
	Box(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	~Box();
	GLfloat x, y, z;
	GLfloat r, g, b;
};

