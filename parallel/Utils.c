#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>

void error(const char *message){
    printf("Blad: %s\n", message);
	exit(-1);
}

void inputError(const char *message, const char *program) {
    printf("Poprawne wejscie:\n");
    printf("%s MIN_X MAX_X MIN_Y MAX_Y STEP\n", program);
	error(message);
}

void exportBoardToFile(struct Config *config, struct Board *board) {
    
    FILE *fp;
    if (!(fp = fopen(OUTPUT_DATA_FILE, "w"))) {
        error("Nie mogę otworzyć pliku test.txt do zapisu!\n");
    }
    
    fprintf(fp, "# Mandelbrot set for x = [%f, %f], y = [%f, %f], step = %f\n", config->minx, config->maxx, config->miny, config->maxy, config->step);
    
    double x_mult = (config->maxx - config->minx) / (config->cols - 1);
    double y_mult = (config->maxy - config->miny) / (config->rows - 1);
    
    for (int row = 0; row < config->rows; ++row) {
        double y = y_mult * row + config->miny;
        for (int col = 0; col < config->cols; ++col) {
            double x = x_mult * col + config->minx;
            fprintf(fp, "%lf\t%lf\t%d\n", x, y, board->board[row][col]);
        }
        fprintf(fp, "\n");
    }
    
    fclose (fp);
}