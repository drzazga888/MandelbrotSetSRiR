#pragma once

class Board{
	
	public:
		
		Board();
		~Board();
		int getRows();
		int getCols();
		int next();
		void setRow(int row, int *data);
		bool areStillRowsToProcess();
		int* getRow(int row);
		int** getBoardData();

	private:
		
		int** board;
		int currentRow;
		int rows;
		int cols;
		void init();
		void free();
		
};
