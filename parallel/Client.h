#pragma once

#include <complex.h>

void client_run(struct Config *config);
int mandelbrot(int minx, int miny, int row, int col, double x_mult, double y_mult);
