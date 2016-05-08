#pragma once
#include "main.h"

class PairsGame
{
private:
	void InitialiseBoxPositions(int, int);
	void GenerateBoxes(int);
	void GenerateBoxPositions(void);

	struct BoxPositions {
		int x, y;
	};

	bool positionsGenerated;

public:
	PairsGame();
	~PairsGame();
	void ShuffleBoxes(void);

	std::vector<Box> boxes;
	std::vector<BoxPositions> boxPositions;

	const int GRID_WIDTH = 6;
	const int GRID_HEIGHT = 6;


};

