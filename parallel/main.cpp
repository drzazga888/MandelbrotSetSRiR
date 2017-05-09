#include <iostream>
#include <iomanip>
#include <complex>
#include <fstream>
#include "Config.h"
#include "Server.h"
#include "Client.h"
#include "Utils.h"

using std::cout;
using std::endl;
using std::cerr;
using std::complex;
using std::setw;
using std::ostream;
using std::ofstream;

void debugBoard(ostream &out, int **board, int rows, int cols) {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            out << setw(5) << board[row][col];
        }
        out << endl;
    }
}

void exportBoardToFile(ostream &out, int **board, double minx, double maxx, double miny, double maxy, double step, int rows, int cols) {
    
    out << "# Mandelbrot set for x = [" << minx << ", " << maxx << "], y = [" << miny << ", " << maxy << "], step = " << step << endl;
    
    double x_mult = (maxx - minx) / (cols - 1);
    double y_mult = (maxy - miny) / (rows - 1);
    for (int row = 0; row < rows; ++row) {
        double y = y_mult * row + miny;
        for (int col = 0; col < cols; ++col) {
            double x = x_mult * col + minx;
            out << x << "\t" << y << "\t" << board[row][col] << endl;
        }
        out << endl;
    }
}

int main(int argc, char *argv[]) {
	appConfig().initialize(argc, argv);
    int rows = getRows(appConfig().miny, appConfig().maxy, appConfig().step);
    int cols = getCols(appConfig().minx, appConfig().maxx, appConfig().step);
	MPI_Barrier(MPI_COMM_WORLD);
	if(appConfig().procRank == SERVER){
		Server server;
		server.run();	
		int** board = server.getBoard();
		ofstream ofs("data.txt", ofstream::out);
		//debugBoard(ofs, board, rows, cols);
		exportBoardToFile(ofs, board, appConfig().minx, appConfig().maxx, appConfig().miny, 
							appConfig().maxy, appConfig().step, rows, cols);
		ofs.close();	
	}
	else
		Client().run(); 
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
    return 0;
}