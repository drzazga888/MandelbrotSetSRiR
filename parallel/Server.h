#include <mpi.h>
#include "Board.h"
#include "MessagesTags.h"
const int SERVER = 0;
const int FIRST_CLIENT = 1;

class Server
{
	public:
		Server();
		void run();
		int** getBoard();
	private:
		Board board;
		int **tempRows;
		MPI_Request *handlersToClients;
		int clientsCount;
		int waitSomeTimeForClientsResponse(int clientsCount, MPI_Request* handlersToClients, int* responsiveClients);
		void startListenerForCompletedWork(int clientId, MPI_Request& handle, int *promisedRow);
		int requestWorkTo(int clientId);
};
