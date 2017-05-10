#include <mpi.h>
#include "Board.h"
#include "MessagesTags.h"

void server_run(struct Config &config);
int waitSomeTimeForClientsResponse(int clientsCount, MPI_Request* handlersToClients, int* responsiveClients);
void startListenerForCompletedWork(int clientId, MPI_Request& handle, int *promisedRow);
int requestWorkTo(int clientId);