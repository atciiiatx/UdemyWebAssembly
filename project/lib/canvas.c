#include <stdio.h>
#include <emscripten.h>

// Init circle data and start render
int main() {
    printf("Init circles\n");
    emscripten_run_script("render()");
}

// Get number of circles to draw
int getCircles() {
    return 1;
}