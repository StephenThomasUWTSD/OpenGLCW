#pragma once

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
#include "Vector.h"
#include "Box.h"
#include "PairsGame.h"

void rotateTiles(void);
void bounce(void);
void changeSize(int, int);
void drawBox(float, float, float);
void computePos(float);
void computeDir(float);
void renderScene(void);
void pressKey(int, int, int);
void releaseKey(int, int, int);
float randColour(void);