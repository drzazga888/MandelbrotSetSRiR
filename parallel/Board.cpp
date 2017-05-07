#include "Board.h"
#include "Config.h"
#include "Utils.h"
#include <iostream>
#include <unistd.h>

Board::Board(){
    rows = getRows(appConfig().miny, appConfig().maxy, appConfig().step);
    cols = getCols(appConfig().minx, appConfig().maxx, appConfig().step);
	initBoard();
	currentRow = 0;
	currentCol = 0;
}
Board::~Board(){
	freeBoard();
}
void Board::freeBoard() {
    for (int i = 0; i < rows; ++i) {
         delete[] board[i];
    }
    delete board;
}
void Board::initBoard() {
    board = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new int[cols];
    }
    for (int i = 0; i < rows; ++i) {
    	for (int j = 0; j < cols; ++j) {
			board[i][j] = 6;
		}
	}
}
int Board::getCurrentCol(){
	return currentCol;
}
int Board::getCurrentRow(){
	return currentRow;
}
void Board::moveToNextPoint(){
	if(currentCol == cols-1){
		++currentRow;
		currentCol = 0;
	}else{
		++currentCol;
	}
}
void Board::setPoint(int row, int col, int value){
	std::cout << "Row: " << row << std::endl;
//	std::cout << "Set Point: row: "<< row <<" col: " << col <<" value: " << value <<std::endl;
	board[row][col] = value;
}
bool Board::areStillPointsToProcess(){
	if(getCurrentRow() >= rows-1 && getCurrentCol() >= cols-1)
		return false;
	return true;
}
int** Board::getBoardData(){
	return board;
}
