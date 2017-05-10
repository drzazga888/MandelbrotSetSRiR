#include "Utils.h"
#include <iostream>
#include <cmath>
#include <mpi.h>
#include <cstdlib>

using std::cerr;
using std::endl;
using std::cout;
void warning(std::string message){
    cerr << "Uwaga: " << message << endl;
}
void error(const char *message){
    cerr << "Blad: " << message << endl;
	exit(-1);
}
int getRows(double miny, double maxy, double step) {
    return floor((maxy - miny) / step) + 1;
}
int getCols(double minx, double maxx, double step) {
    return floor((maxx - minx) / step) + 1;
}
void freeBoard(int **board, int rows) {
    for (int i = 0; i < rows; ++i) {
         delete[] board[i];
    }
    delete board;
}
int **initBoard(int rows, int cols) {
    int **board = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new int[cols];
    }
    return board;
}
void debugTimeStart(double startTime, std::string message){
	cout << message << ", Start Time: " << MPI_Wtime()-startTime<< ", " << endl;
}
void debugTimeEnd(double startTime, std::string message)
{
	cout << message << ", End Time: " << MPI_Wtime()-startTime<< ", " << endl;
}
