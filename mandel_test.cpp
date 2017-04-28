#include <iostream>
#include <iomanip>
#include <complex>
#include <cstdlib>
#include <cmath>

using std::cout;
using std::endl;
using std::cerr;
using std::complex;
using std::setw;

const int MAX_ITERS = 999;


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

void inputError(const char *message, const char *program) {
    cerr << "Blad: " << message << endl;
    cerr << "Poprawne wejscie:" << endl;
    cerr << program << " MIN_X MAX_X MIN_Y MAX_Y STEP" << endl;
    exit(-1);
}

void printBoard(int **board, int rows, int cols) {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            cout << setw(5) << board[row][col];
        }
        cout << endl;
    }
}

int **mandelbrot(double minx, double maxx, double miny, double maxy, double step, double rows, double cols) {
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
            } while (iters < MAX_ITERS && fabs(z.real()) <= 2.0);
            
            board[row][col] = iters;
            
        }
    }
    
    // magic end
    return board;
}

int main(int argc, char *argv[]) {
    
    if (argc != 6) {
        inputError("Nalezy padac 5 argumentow", argv[0]);
    }
    
    double minx = atof(argv[1]);
    double maxx = atof(argv[2]);
    double miny = atof(argv[3]);
    double maxy = atof(argv[4]);
    double step = atof(argv[5]);
    
    if (maxx < minx) {
        inputError("MAX_X musi byc wieksze badz rowne od MIN_X", argv[0]);
    }
    
    if (maxy < miny) {
        inputError("MAX_Y musi byc wieksze badz rowne od MIN_Y", argv[0]);
    }
    
    if (step <= 0.0) {
        inputError("STEP musi byc wieksze od 0", argv[0]);
    }
    
    int rows = getRows(miny, maxy, step);
    int cols = getCols(minx, maxx, step);
    int **board = mandelbrot(minx, maxx, miny, maxy, step, rows, cols);
    printBoard(board, rows, cols);
    freeBoard(board, rows);
    
    return 0;
}
