#include "main.h"
using namespace std;

bool tilesGenerated = false;

PairsGame game;

// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 3.0f, z = 1.0f;

bool movingUp = false; // Whether or not we are moving up or down  
float yLocation = 0.0f; // Keep track of our position on the y axis.  

float yRotationAngle = 0.0f; // The angle of rotation for our object  
// the key states. These variables will be zero
//when no key is being presses
float deltaMove = 0;
float deltaAngle = 0.0f;


void bounce()
{
	if (movingUp) // If we are moving up  
		yLocation -= 0.005f; // Move up along our yLocation  
	else  // Otherwise  
		yLocation += 0.005f; // Move down along our yLocation  

	if (yLocation < -3.0f) // If we have gone up too far  
		movingUp = false; // Reverse our direction so we are moving down  
	else if (yLocation > 3.0f) // Else if we have gone down too far  
		movingUp = true; // Reverse our direction so we are moving up  
	glTranslatef(0.0f, yLocation, 0.0f); // Translate our object along the y axis  

	
}


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

//This function first translates a further x,y,z units then draws a box of
//width w, height h, length l
void drawBox(float w, float h, float l)
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

	for (Box box : game.boxes) {
		glPushMatrix();
		glTranslatef(box.x, box.y, box.z);
		
		//rotateTiles();

		glColor3f(box.r, box.g, box.b);
		drawBox(1, 1, 1);
		glPopMatrix();
	}
	
	//glTranslatef(0.0f, yLocation, 0.0f); // Translate our object along the y axis 
	
	glutSwapBuffers();
}


void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_LEFT:
		deltaAngle = -0.01f;
		break;
	case GLUT_KEY_RIGHT:
		deltaAngle = 0.01f;
		break;
	case GLUT_KEY_UP:
		deltaMove = 0.5f;
		break;
	case GLUT_KEY_DOWN:
		deltaMove = -0.5f;
		break;
	case GLUT_KEY_END:
		yLocation = 0.5;
		game.ShuffleBoxes();
		break;
	case GLUT_KEY_INSERT:
		yRotationAngle = -45.0f;
		break;
	}
}

void releaseKey(int key, int x, int y) 
{

	switch (key) 
	{
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT:
		deltaAngle = 0.0f;
		break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:
		deltaMove = 0;
		break;
	case GLUT_KEY_END:
		yRotationAngle = 0;
		break;
	}
}

float randColour() 
{
	return (double)rand() / (RAND_MAX + 1.0);
}

int main(int argc, char **argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Match Game: Tile Madness!");

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
	
	game.ShuffleBoxes();
	
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

void rotateTiles()
{
	/*
	yRotationAngle += 0.005f; // Increment our rotation value
	if (yRotationAngle > 360.0f) // If we have rotated beyond 360 degrees (a full rotation)
	yRotationAngle -= 360.0f; // Subtract 360 degrees off of our rotation
	*/
	yRotationAngle += 0.005f; // Increment our rotation value  
	if (yRotationAngle > 360.0f) // If we have rotated beyond 360 degrees (a full rotation)
		yRotationAngle -= 360.0f; // Subtract 360 degrees off of our rotation
	glRotatef(yRotationAngle, 0.0f, 0.0f, 1.0f); // Rotate our object around the y axis 

}