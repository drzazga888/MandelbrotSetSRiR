#include <iostream>
#include <iomanip>
#include <complex>
#include <fstream>
#include <mpe.h>
#include "Config.h"
#include "Server.h"
#include "Client.h"
#include "Utils.h"
#include "MpeLogFlags.h"

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

int **mandelbrot(double minx, double maxx, double miny, double maxy, double step, double rows, double cols, const int maxiters) {
    int **board = initBoard(rows, cols);
    // do the magic
    
    double x_mult = (maxx - minx) / (cols - 1);
    double y_mult = (maxy - miny) / (rows - 1);
    
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            
            std::complex<double> c(x_mult * col + minx, y_mult * row + miny);
            std::complex<double> z = 0 + 0i;
            
            int iters = 0;
            
            do {
                z = z * z + c;
                ++iters;
            } while (iters < maxiters && fabs(z.real()) <= 2.0);
            board[row][col] = iters;
        }
    }    
    // magic end
    return board;
}

int main(int argc, char *argv[]) {
	appConfig().initialize(argc, argv);
    MPE_Init_log();
    int rows = getRows(appConfig().miny, appConfig().maxy, appConfig().step);
    int cols = getCols(appConfig().minx, appConfig().maxx, appConfig().step);
	MPI_Barrier(MPI_COMM_WORLD);
	double time = MPI_Wtime();
	if(appConfig().procRank == SERVER){
        MPE_Describe_state(REQ_TO_WORK_SEND_START, REQ_TO_WORK_SEND_END, "request to work - send", "red");
        
		Server server;
		server.run(time);	
		int** board = server.getBoard();
		ofstream ofs("data.txt", ofstream::out);
		//debugBoard(ofs, board, rows, cols);
		exportBoardToFile(ofs, board, appConfig().minx, appConfig().maxx, appConfig().miny, 
							appConfig().maxy, appConfig().step, rows, cols);
		ofs.close();	
	}
	else
		Client().run(time); 
	MPI_Barrier(MPI_COMM_WORLD);
    MPE_Finish_log("mpe-logs");
	MPI_Finalize();
    return 0;
}