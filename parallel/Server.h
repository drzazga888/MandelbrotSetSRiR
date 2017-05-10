#pragma once

#include <mpi.h>
#include "Config.h"
#include "Board.h"

void server_run(struct Config *config);
int waitSomeTimeForClientsResponse(int clientsCount, MPI_Request* handlersToClients, int* responsiveClients);
void startListenerForCompletedWork(int cols, int clientId, MPI_Request *handle, int *promisedRow);
int requestWorkTo(struct Board *board, int clientId);