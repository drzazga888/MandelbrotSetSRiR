#include <mpi.h>
#include "Board.h"
#include "MessagesTags.h"
const int SERVER = 0;
const int FIRST_CLIENT = 1;

/**
 * Klasa, ktora zawiera kod przeznaczony do wykonania przez managera
 */
class Server
{
	public:
		
		/**
		 * Konstruktor
		 */
		Server();
		
		/**
		 * Metoda uruchamia kod managera, ktory m.in:
		 * - rozsyla poczatkowe dane dla workerow
		 * - zaczyna nasluchiwac na przyjscie danych od workerow (nieblokujaco)
		 * - gdy otrzyma jakies dane zwrtotne, to sprawdza, co trzeba jeszcze obliczyc...
		 *   i jest trzeba, to wysyla kolejny numer wiersza do tego samego workera,
		 *   z ktorego przyszla informacja zwrotna workera
		 * - po skonczonych obliczenia - odsyla numer wiersza -1 (koniec)
		 */
		void run();
		
		/**
		 * Pozwala pobrac plaszczyzne
		 * @return plaszczyna
		 */
		int** getBoard();
		
	private:
		Board board;
		int **tempRows;
		
		/**
		 * Tablica requestow - rozmiar rowny ilosci kientow (workerow)
		 */
		MPI_Request *handlersToClients;
		
		int clientsCount;
		
		/**
		 * Pomocnicza funkcja, ktora wykonuje MPI_Waitsome, czyli nasluchuje na jakiegokolwiek workera
		 * @param clientsCount ilosc workerow
		 * @param handlersToClients tablica requestow MPI
		 * @param responsiveClients tablica, do ktorej zostania zapisane numery ID klientow, od ktorych otrzymane zostana odpowiedzi
		 * @return ilosc otrzymanych odpowiedzi
		 */
		int waitSomeTimeForClientsResponse(int clientsCount, MPI_Request* handlersToClients, int* responsiveClients);
		
		/**
		 * Zaczyna sluchac nieblokujaco na konkretnego workera
		 * @param clientId numer ID workera
		 * @param handle request MPI, ktory zostanie powiazany z nasluchiwaniem
		 * @param promisedRow tablica, do ktorej zostanie zapisany wiersza danych od workera
		 */
		void startListenerForCompletedWork(int clientId, MPI_Request& handle, int *promisedRow);
		
		/**
		 * Zada od konkretnego workera obliczenia nastepnego wiersza plaszczyzny
		 * @param clientId numer ID klienta
		 * @return numer wiersza, ktory zostal wyznaczony do obliczenia przez klienta
		 */
		int requestWorkTo(int clientId);
};
