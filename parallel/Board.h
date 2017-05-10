#pragma once

#include <stdbool.h>

struct Board {
	int** board;
	int currentRow;
	int rows;
	int cols;
};

struct Board board_init(int rows, int cols);
void board_free(struct Board *board);
int board_next(struct Board *board);
void board_setRow(struct Board *board, int row, int *data);
bool board_areStillRowsToProcess(struct Board *board);
int* board_getRow(struct Board *board, int row);