#include <iostream>
#include <iomanip>
#include <complex>
#include <cmath>
#include <fstream>
#include <mpi.h>
#include "Config.h"

using std::cout;
using std::endl;
using std::cerr;
using std::complex;
using std::setw;
using std::ostream;
using std::ofstream;

const int MASTER = 0;


int getRows(double miny, double maxy, double step) {
    return floor((maxy - miny) / step) + 1;
}

int getCols(double minx, double maxx, double step) {
    return floor((maxx - minx) / step) + 1;
}

int **initBoard(int rows, int cols) {
    int **board = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new int[cols];
    }
    return board;
}

void freeBoard(int **board, int rows) {
    for (int i = 0; i < rows; ++i) {
         delete[] board[i];
    }
    delete board;
}

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

    int numprocs, myid;

	appConfig().initialize(argc, argv);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    printf ("Siema, mam na imie %d!\n", myid);
    if (myid == MASTER)
       printf("Master: Yo, liczba taskow: %d... mam nadzieje ze moje dzieci-taski byly grzeczne i sie przedstawily hehiehhehuehe\n",numprocs);
    

    int rows = getRows(appConfig().miny, appConfig().maxy, appConfig().step);
    int cols = getCols(appConfig().minx, appConfig().maxx, appConfig().step);
    int **board = mandelbrot(appConfig().minx, appConfig().maxx, appConfig().miny, 
							appConfig().maxy, appConfig().step, rows, cols, 999);

    // debugBoard(cout, board, rows, cols);
    
    ofstream ofs("data.txt", ofstream::out);
    exportBoardToFile(ofs, board, appConfig().minx, appConfig().maxx, appConfig().miny, 
						appConfig().maxy, appConfig().step, rows, cols);
    ofs.close();
    
    freeBoard(board, rows);
    MPI_Finalize();
    
    return 0;

}