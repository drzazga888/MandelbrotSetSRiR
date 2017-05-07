#pragma once
#include <string>

void error(const char *message);
void warning(std::string message);
int getRows(double miny, double maxy, double step);
int getCols(double minx, double maxx, double step);
void freeBoard(int **board, int rows);
int **initBoard(int rows, int cols);
void debugTimeStart(double startTime, std::string message = "");
void debugTimeEnd(double startTime, std::string message = "");
