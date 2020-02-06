#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten.h>

// Constants
#define NUM_CIRCLES 20

// Data structure
struct Circle {
    int x;
    int y;
    int r;
    int cr;
    int cg;
    int cb;
};

struct Circle circles[NUM_CIRCLES];

// Random number in range
int getRand(int min, int max) {
    int range = max - min;
    int result = min + (int)(((float)rand() / (float)RAND_MAX) * range);
    return result;
}

// Init circle data and start render
int main() {
    printf("Generate %d circles\n", NUM_CIRCLES);
    srand(time(NULL));
    for (int i = 0; i < NUM_CIRCLES; ++i) {
        int radius = getRand(5, 150);
        circles[i].x = getRand(0, 1000) + radius;
        circles[i].y = getRand(0, 1000) + radius;
        circles[i].r = radius;
        circles[i].cr = getRand(55, 255);
        circles[i].cg = getRand(55, 255);
        circles[i].cb = getRand(55, 255);
    }

    EM_ASM({ render($0); }, NUM_CIRCLES);
}

// Get circles to draw
struct Circle* getCircles() {
    return circles;
}

int getX(int index) {
    return circles[index].x;
}

int getY(int index) {
    return circles[index].y;
}

int getRadius(int index) {
    return circles[index].r;
}

int getRed(int index) {
    return circles[index].cr;
}

int getGreen(int index) {
    return circles[index].cg;
}

int getBlue(int index) {
    return circles[index].cb;
}