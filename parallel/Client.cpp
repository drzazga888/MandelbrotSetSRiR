#include "Client.h"
#include <iostream>
#include "MessagesTags.h"
#include "Config.h"
#include "Utils.h"
#include <cmath>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

const int maxiters = 999;
const int serverRank = 0;

Client::Client(){}

void Client::run(){
	
	double maxx = appConfig().maxx;
	double maxy = appConfig().maxy;
	double minx = appConfig().minx;
	double miny = appConfig().miny;
	int cols = getCols(minx, maxx, appConfig().step);
	double x_mult = (maxx - minx) / (cols - 1);
	double y_mult = (maxy - miny) / (getRows(miny, maxy, appConfig().step) - 1);
	int row;
	int iters[cols];
	
	while(true)
	{
		MPI_Status status;
		MPI_Recv(&row, 1, MPI_INT, serverRank, ItersDataMsg, MPI_COMM_WORLD, &status);
		if (row == -1) {
			break;
		}
		for (int col = 0; col < cols; ++col) {
			iters[col] = mandelbrot(row, col, x_mult, y_mult);
		}
		MPI_Send(iters, cols, MPI_INT, serverRank, ItersDataMsg, MPI_COMM_WORLD);
	}
		
}

int Client::mandelbrot(int row, int col, double x_mult, double y_mult){
	std::complex<double> c(x_mult * col + appConfig().minx, y_mult * row + appConfig().miny);
	std::complex<double> z = 0 + 0i;	
	int iters = 0;   
	do {
		z = z * z + c;
		++iters;
	} while (iters < maxiters && fabs(z.real()) <= 2.0);
	return iters;
}