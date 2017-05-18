#include <mpi.h>
#include <complex>

/**
 * Zawiera kod, ktory zostanie wykonany przez workerow
 */
class Client
{
	public:
		
		/**
		 * Konstruktor
		 */
		Client();
		
		/**
		 * Uruchamia program przeznaczony dla workera - zawiera petle, w ktorej:
		 * - program czeka na informacje od managera (nr wiersza do obliczenia)
		 * - oblicza caly wiersz plaszczyzny
		 * - zwraca obliczony wiersz do managera
		 */
		void run();
		
	private:
		int mandelbrot(int row, int col, double x_mult, double y_mult);
		std::complex<double> getC(int* pointData, double x_mult, double y_mult);
};
