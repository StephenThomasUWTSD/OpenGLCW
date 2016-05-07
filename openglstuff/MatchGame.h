#pragma once
using namespace std;
class MatchGame
{
public:
	MatchGame();
	void changeSize(int w, int h);
	void drawBox(float w, float h, float l);
	void computePos(float deltaMove);
	void computeDir(float deltaAngle);
	void renderScene(void);
	void pressKey(int key, int xx, int yy);
	void releaseKey(int key, int x, int y);
	float randColour();
	void generateBoxes(int numBoxes);
	void initialBoxPositions(int width, int height);
	void generateTilePositions();
	void shuffleBoxes();
	~MatchGame();
	const static int GRID_WIDTH = 6;
	const static int GRID_HEIGHT = 6;

	
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

};

