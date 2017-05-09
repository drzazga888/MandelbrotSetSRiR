#include "Board.h"
#include "Config.h"
#include "Utils.h"
#include <iostream>
#include <unistd.h>

Board::Board(){
    rows = ::getRows(appConfig().miny, appConfig().maxy, appConfig().step);
    cols = ::getCols(appConfig().minx, appConfig().maxx, appConfig().step);
	init();
	currentRow = 0;
}

Board::~Board(){
	free();
}

void Board::free() {
    for (int i = 0; i < rows; ++i) {
         delete[] board[i];
    }
    delete board;
}

void Board::init() {
    board = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new int[cols];
    }
}

int Board::next(){
    int temp = currentRow;
    ++currentRow;
	return temp;
}

void Board::setRow(int row, int *data) {
    for (int i = 0; i < cols; ++i) {
        board[row][i] = data[i];
    }
}

int Board::getRows() {
    return rows;
}

int Board::getCols() {
    return cols;
}

bool Board::areStillRowsToProcess(){
	return currentRow < rows;
}

int* Board::getRow(int row){
	return board[row];
}

int** Board::getBoardData(){
	return board;
}