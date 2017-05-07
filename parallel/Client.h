#include <mpi.h>
#include <complex>
class Client
{
	public:
		Client();
		void run(double start);
	private:
		int mandelbrot(std::complex<double> c);
		std::complex<double> getC(int* pointData, double x_mult, double y_mult);
		bool isWorkDone(int*);
		bool workDone;	
};
