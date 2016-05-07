#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>
#include <cmath>
#include <vector>
#include <ctime>
#include <algorithm>
#include "vector.h"
#include "MatchGame.h"
/*
const int GRID_WIDTH = 6;
const int GRID_HEIGHT = 6;

using namespace std;
double WorldT[16];
double objectNear[4];
double objectFar[4];
const int amount = 32;
bool tilesGenerated = false;
struct Box {
	GLfloat x, y, z;
	GLfloat red, green, blue;
};

vector<Box> boxes;

struct TilePositions {
	int x, z;
};

vector<TilePositions> tilePositions;

// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 3.0f, z = 1.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

void shuffleBoxes(void);


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0f / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(60.0f, ratio, 1.0f, 1000.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawBox(float w, float h, float l)
//drawBox
//***************************************************************************
//This function first translates a further x,y,z units then draws a box of
//width w, height h, length l
{
	glPushMatrix();       //save modelview
	w = w / 2.0; h = h / 2.0; l = l / 2.0; //adjust values so centre is in middle of box
										   //draw faces of box
	glBegin(GL_POLYGON);
	glVertex3f(w, l, h);
	glVertex3f(w, l, -h);
	glVertex3f(-w, l, -h);
	glVertex3f(-w, l, h);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(w, l, h);
	glVertex3f(-w, l, h);
	glVertex3f(-w, -l, h);
	glVertex3f(w, -l, h);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(w, l, h);
	glVertex3f(w, -l, h);
	glVertex3f(w, -l, -h);
	glVertex3f(w, l, -h);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-w, l, h);
	glVertex3f(-w, l, -h);
	glVertex3f(-w, -l, -h);
	glVertex3f(-w, -l, h);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-w, -l, h);
	glVertex3f(-w, -l, -h);
	glVertex3f(w, -l, -h);
	glVertex3f(w, -l, h);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(w, -l, -h);
	glVertex3f(-w, -l, -h);
	glVertex3f(-w, l, -h);
	glVertex3f(w, l, -h);
	glEnd();
	glPopMatrix();   //restore previous modelview matrix so leaving things as you found them
}



void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}

void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 20.0f, z,
		x + lx, 3.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	for (Box box : boxes) {
		glPushMatrix();
		glTranslatef(box.x, box.y, box.z);
		glColor3f(box.red, box.green, box.blue);
		drawBox(1, 1, 1);
		glPopMatrix();
	}

	glutSwapBuffers();
}


void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
	case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
	case GLUT_KEY_UP: deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	case GLUT_KEY_END: shuffleBoxes(); break;
	}
}

void releaseKey(int key, int x, int y) 
{

	switch (key) 
	{
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT: deltaAngle = 0.0f; break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}

float randColour() 
{
	return (double)rand() / (RAND_MAX + 1.0);
}

void generateBoxes(int numBoxes = GRID_WIDTH * GRID_HEIGHT) 
{
	for (int boxIndex = 0; boxIndex < numBoxes; boxIndex += 2) 
	{
		float r = randColour(), g = randColour(), b = randColour();
		Box first = { 0,0,0,r,g,b };
		Box second = { 0,0,0,r,g,b };

		boxes.push_back(first);
		boxes.push_back(second);
	}
}

void initialBoxPositions(int width = GRID_WIDTH, int height = GRID_HEIGHT) 
{
	int x = 0, z = 0;

	for (int boxIndex = 0; boxIndex < boxes.size(); boxIndex++) 
	{
		boxes[boxIndex].x = x;
		boxes[boxIndex].y = 0;
		boxes[boxIndex].z = z;

		x++;
		if (x >= width) 
		{
			x = 0;
			z++;
		}
	}

	// NOTE: foreach style like below does NOT work!
	// The elements inside boxes do not get changed becase
	// you are editing a copy of each box, not the actual
	// box in the collection.
	/*for (Box box : boxes) {
	box.x = x;
	box.y = 0;
	box.z = z;

	x++;
	if (x > width) {
	x = 0;
	z++;
	}
	}*//*
}

void generateTilePositions() 
{
	for (int x = 0; x < GRID_WIDTH; x++) 
	{
		for (int z = 0; z < GRID_HEIGHT; z++) 
		{
			tilePositions.push_back({ x, z });
		}
	}
}

void shuffleBoxes() 
{
	if (!tilesGenerated) 
	{
		tilesGenerated = true;
		generateTilePositions();
	}

	random_shuffle(tilePositions.begin(), tilePositions.end());

	for (int boxIndex = 0; boxIndex < boxes.size(); boxIndex++) 
	{
		boxes[boxIndex].x = tilePositions[boxIndex].x;
		boxes[boxIndex].z = tilePositions[boxIndex].z;
	}
}
*/
int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutSpecialFunc(pressKey);

	// here are the new entries
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	generateBoxes();
	initialBoxPositions();
	shuffleBoxes();
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

/*
House::House() : position(0, 0, 0), BVposition(0, 0, 0) {
intersect = false;
BoundSphereRadius = 1.0;
BVposition.x = position.x + 0.5;
BVposition.y = position.y - 0.25;
BVposition.z = position.z - 0.5;
}
bool House::isBoundSphereIntersect(Ray v) {
//calc collision
cout << "line point distance squared is: " << v.LinePointDistanceSqd(BVposition) << "\n";


if (v.LinePointDistanceSqd(BVposition)>(BoundSphereRadius*BoundSphereRadius))
return false; //no intersection detected
else true;//intersection detected
}
*/

/*
void rayCastMouse(int button, int state, int x, int y)
{
if (state == GLUT_DOWN) {
int view[4];
//   double modelview[16];
double proj[16];
glGetIntegerv(GL_VIEWPORT, view);
glGetDoublev(GL_PROJECTION_MATRIX, proj);
int realy = view[3] - (GLint)y - 1;
int check = gluUnProject(x, realy, -1, WorldT, proj, view, objectNear, objectNear + 1, objectNear + 2);
cout << "unprojected near co-ords are ";
for (int i = 0; i<4; i++) {
cout << objectNear[i] << " ";
} cout << "\n";
check = gluUnProject(x, realy, 1, WorldT, proj, view, objectFar, objectFar + 1, objectFar + 2);
cout << "unprojected far co-ords are ";
for (int i = 0; i<4; i++) {
cout << objectFar[i] << " ";
} cout << "\n";
//prepare for collision test by making a ray
Vector d(objectFar[0], objectFar[1], objectFar[2]);
Vector p(objectNear[0], objectNear[1], objectNear[2]);
Ray ray1;  //this is the ray cast
ray1.SetOrigin(p);      //initialise ray with origin and direction vector
ray1.SetDirection(d - p);
if (boxes.isBoundSphereIntersect(ray1))
cout << "hit" << endl;
else
cout << "miss" << endl;


glutPostRedisplay();

}

}
*/