#include "Board.h"
#include "Config.h"
#include "Utils.h"

struct Board board_init(int rows, int cols) {
    
    struct Board board;
    
    board.rows = rows;
    board.cols = cols;
    board.currentRow = 0;
    
    board.board = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        board.board[i] = new int[cols];
    }
    
	return board
}

void board_free(struct Board *board) {
    for (int i = 0; i < rows; ++i) {
         delete[] board->board[i];
    }
    delete[] board->board;
}

int board_next(struct Board *board){
    int temp = board->currentRow;
    ++(board->currentRow);
	return temp;
}

void board_setRow(struct Board *board, int row, int *data) {
    for (int i = 0; i < cols; ++i) {
        board->board[row][i] = data[i];
    }
}

bool board_areStillRowsToProcess(struct Board *board){
	return board->currentRow < board->rows;
}

int* board_getRow(struct Board *board, int row){
	return board->board[row];
}