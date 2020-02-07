#include <emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants
#define NUM_CIRCLES 20

// Data structures
struct Circle {
	int x;
	int y;
	int r;
	int cr;
	int cg;
	int cb;
};

struct CircleAnimationData {
	int x;
	int y;
	int r;
	int xv;
	int yv;
	int xd;
	int yd;
};

struct Circle circles[NUM_CIRCLES];
struct CircleAnimationData animationData[NUM_CIRCLES];

// Random number in range
int getRand(int min, int max)
{
	int range = max - min;
	int result = min + (int)(((float)rand() / (float)RAND_MAX) * range);
	return result;
}

// Init circle data and start render
int main()
{
	printf("Generate %d circles\n", NUM_CIRCLES);
	srand(time(NULL));
	for(int i = 0; i < NUM_CIRCLES; ++i) {
		int radius = getRand(5, 150);
		circles[i].x = getRand(0, 500) + radius;
		circles[i].y = getRand(0, 500) + radius;
		circles[i].r = radius;
		circles[i].cr = getRand(55, 255);
		circles[i].cg = getRand(55, 255);
		circles[i].cb = getRand(55, 255);

		animationData[i].x = circles[i].x;
		animationData[i].y = circles[i].y;
		animationData[i].r = circles[i].r;
		animationData[i].xv = getRand(1, 10);
		animationData[i].yv = getRand(1, 10);
		animationData[i].xd = 1;
		animationData[i].yd = 1;
	}

	EM_ASM({ render($0); }, NUM_CIRCLES);
}

// Get circles to draw
struct Circle *getCircles()
{
	return circles;
}

int getX(int index)
{
	return circles[index].x;
}

int getY(int index)
{
	return circles[index].y;
}

int getRadius(int index)
{
	return circles[index].r;
}

int getRed(int index)
{
	return circles[index].cr;
}

int getGreen(int index)
{
	return circles[index].cg;
}

int getBlue(int index)
{
	return circles[index].cb;
}

void incrementAnimation(int canvasWidth, int canvasHeight)
{
	printf("Increment animation width = %d height = %d\n", canvasWidth, canvasHeight);
	for(int i = 0; i < NUM_CIRCLES; ++i) {
		int x = animationData[i].x;
		int y = animationData[i].y;
		int r = animationData[i].r;
		if(((x + r) >= canvasWidth) || ((x - r) <= 0)) {
			animationData[i].xd *= -1;
		}
		if(((y + r) >= canvasHeight) || ((y - r) <= 0)) {
			animationData[i].yd *= -1;
		}
		animationData[i].x += animationData[i].xd * animationData[i].xv;
		animationData[i].y += animationData[i].yd * animationData[i].yv;
		circles[i].x = animationData[i].x;
		circles[i].y = animationData[i].y;
	}
}