#pragma once
struct PointInfo{
	int row;
	int col;
	int value;
};
class Board{
	public:
		Board();
		bool areStillPointsToProcess();
		int getCurrentCol();
		int getCurrentRow();
		void moveToNextPoint();
		void setPoint(int row, int col, int value);
		int** getBoardData();
		~Board();
	private:
		int** board;
		int currentRow;
		int processedRow;
		int currentCol;
		int processedCol;
		int rows;
		int cols;
		void initBoard();
		void freeBoard();
};
