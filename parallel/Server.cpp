#include "Server.h"
#include <iostream>
#include <vector>
#include "Config.h"
#include "Utils.h"
#include <stdlib.h>
#include <unistd.h>

const int endMarker = -1;
using namespace std;

Server::Server()
{
}

void Server::run(){
	
	int clientsCount = appConfig().getNumOfClients();
	MPI_Request handlersToClients[clientsCount];
	int tempNr[clientsCount];
	int totalComputed = 0;
	
	int **tempRows = new int*[clientsCount];
	for (int i = 0; i < clientsCount; ++i) {
		tempRows[i] = new int[board.getCols()];
	}
	
	for(int i=0; board.areStillRowsToProcess() && i<clientsCount; ++i){
		int clientId = i+1;
		startListenerForCompletedWork(clientId, handlersToClients[i], tempRows[i]);
		tempNr[i] = requestWorkTo(clientId);
	}
	
	while(true)
	{
		int responsiveClients[clientsCount];
		int responsesCount = waitSomeTimeForClientsResponse(clientsCount, handlersToClients, responsiveClients);
		if (responsesCount < 1) {
			break;
		}
		for(int i=0; i<responsesCount; ++i)
		{
			int requestIndex = responsiveClients[i];
			int clientId = requestIndex+1;
			
			board.setRow(tempNr[requestIndex], tempRows[requestIndex]);
			++totalComputed;
			
			if (board.areStillRowsToProcess()) {
				startListenerForCompletedWork(clientId, handlersToClients[requestIndex], tempRows[requestIndex]);
				tempNr[requestIndex] = requestWorkTo(clientId);
			}
		}
	}
	
	for(int i=0; i<clientsCount; ++i){
		MPI_Send(&endMarker, 1, MPI_INT, i+1, ItersDataMsg, MPI_COMM_WORLD);
	}
		
	for (int i = 0; i < clientsCount; ++i) {
         delete[] tempRows[i];
    }
    delete[] tempRows;
	
}

int Server::requestWorkTo(int clientId){
	int nextRow = board.next();
	MPI_Send(&nextRow, 1, MPI_INT, clientId, ItersDataMsg, MPI_COMM_WORLD);
	return nextRow;
}

void Server::startListenerForCompletedWork(int clientId, MPI_Request& handle, int *promisedRow){
	MPI_Irecv(promisedRow, board.getCols(), MPI_INT, clientId, ItersDataMsg, MPI_COMM_WORLD, &handle);
}

int Server::waitSomeTimeForClientsResponse(int clientsCount, MPI_Request* handlersToClients, int* responsiveClients){
	int receivedResponsesCount;
	MPI_Status responsesStatuses[clientsCount];
	MPI_Waitsome(clientsCount, handlersToClients, &receivedResponsesCount, responsiveClients, responsesStatuses);
	return receivedResponsesCount;
}

int** Server::getBoard(){
	return board.getBoardData();	
}
