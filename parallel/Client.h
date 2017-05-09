#include <mpi.h>
#include <complex>
class Client
{
	public:
		Client();
		void run();
	private:
		int mandelbrot(int row, int col, double x_mult, double y_mult);
		std::complex<double> getC(int* pointData, double x_mult, double y_mult);
};
