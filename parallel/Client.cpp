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

Client::Client(){
	workDone = false;
}
void Client::run(double startTime){
	double maxx = appConfig().maxx;
	double maxy = appConfig().maxy;
	double minx = appConfig().minx;
	double miny = appConfig().miny;
	double x_mult = (maxx - minx) / (getCols(minx, maxx, appConfig().step) - 1);
	double y_mult = (maxy - miny) / (getRows(miny, maxy, appConfig().step) - 1);
	//debugTimeStart(startTime, "Client run");
	//int dummy = 2001;
	//MPI_Send(&dummy, 1, MPI_INT, serverRank, IamFreeMsg, MPI_COMM_WORLD);
	while(true)
	{
		int pointData[2];
		MPI_Status status;
		MPI_Recv(pointData, 2, MPI_INT, serverRank, PointDataMsg, MPI_COMM_WORLD, &status); 
		if(isWorkDone(pointData))
			break;
//		cout << "MPI_Recv of client Rank nr: " << appConfig().procRank << " with data: " << pointData[0] << ", " << pointData[1] << endl;
//		cout << "MPI_Recv of client Rank nr: " << appConfig().procRank << " xmult: " << x_mult << " ymult: " << y_mult << endl;
		int iters = mandelbrot(getC(pointData, x_mult, y_mult));
		MPI_Send(&iters, 1, MPI_INT, serverRank, ItersDataMsg, MPI_COMM_WORLD);
//		cout << "Time: " << MPI_Wtime()-startTime << " ," <<"MPI_Send of client number: " << appConfig().procRank << "with iters: " << iters << endl;
	}
}
int Client::mandelbrot(std::complex<double> c){
//	cout << "Client::mandelbrot, c.real() " << c.real() << ", c.imag(): " << c.imag() << endl;
	std::complex<double> z = 0 + 0i;	
	int iters = 0;   
	do {
		z = z * z + c;
		++iters;
	} while (iters < maxiters && fabs(z.real()) <= 2.0);
	//if(iters > 1)
	//	cout << "MORE THAN ONE!" << endl;
	return iters;
}
std::complex<double> Client::getC(int* pointData, double x_mult, double y_mult){
	double row = pointData[0];
	double col = pointData[1];
//	cout << "Client: " << appConfig().procRank << ", get C, col: " << col << ", row: " << row <<", y_mult: " << y_mult << ", x_mult: " << x_mult << ", minx: " << appConfig().minx << ", miny: " << appConfig().miny <<  endl;
	return std::complex<double>(x_mult * col + appConfig().minx, y_mult * row + appConfig().miny);
}
bool Client::isWorkDone(int* endIndicationPoint){
	if(endIndicationPoint[0] == -1 && endIndicationPoint[1] == -1){
	//	cout << "Client: " << appConfig().procRank << " terminated" << endl;
		return true;
	}
	return false;
}
