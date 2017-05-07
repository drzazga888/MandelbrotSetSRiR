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
void Server::run(double startTime){
	int clientsCount = appConfig().getNumOfClients();
	MPI_Request handlersToClients[clientsCount];
	int dummy;
	PointInfo valueHandler[clientsCount];
	//listenForAvailableClients(dummy, clientsCount, handlersToClients);
	for(int i=0; i<clientsCount; ++i){
		int clientId = i+1;
		valueHandler[i].row = board.getCurrentRow();
		valueHandler[i].col = board.getCurrentCol();
		startListenerForCompletedWork(clientId, handlersToClients[i], valueHandler[i].value);
		requestWorkTo(clientId);
		board.moveToNextPoint();
	}	
	while(board.areStillPointsToProcess())
	{
		int responsiveClients[clientsCount];
//		debugTimeStart(startTime, "wait some time");	 
		int responsesCount = waitSomeTimeForClientsResponse(clientsCount, handlersToClients, responsiveClients);
//		debugTimeEnd(startTime, "wait some time");	 
		for(int i=0; i<responsesCount; ++i)
		{
			int requestIndex = responsiveClients[i];
			int clientId = requestIndex+1;
//			cout << "Before setPoint" << endl;
			board.setPoint(valueHandler[requestIndex].row, valueHandler[requestIndex].col, valueHandler[requestIndex].value);
			if(board.areStillPointsToProcess())
			{
				valueHandler[requestIndex].row = board.getCurrentRow();
				valueHandler[requestIndex].col = board.getCurrentCol();
				startListenerForCompletedWork(clientId, handlersToClients[requestIndex], valueHandler[requestIndex].value);
				requestWorkTo(clientId);
				board.moveToNextPoint();
			}
		}
	}

	int pointData[2] = {endMarker, endMarker};
	for(int i=0; i<clientsCount; ++i){
		MPI_Send(&pointData, 2, MPI_INT, i+1, PointDataMsg, MPI_COMM_WORLD);
	}
}
void Server::requestWorkTo(int clientId){
	int pointData[2] = {board.getCurrentRow(), board.getCurrentCol()};
//	cout << "Server::request Work To client Id: " << clientId << " with data: " << pointData[0] << ", " << pointData[1] << endl;
	MPI_Send(&pointData, 2, MPI_INT, clientId, PointDataMsg, MPI_COMM_WORLD);
}
void Server::startListenerForCompletedWork(int clientId, MPI_Request& handle, int &valueHandler){
//	cout << "Server::start Listener For Completed Work On Client: " << clientId << ", handle: " << &handle << endl;
	MPI_Irecv(&valueHandler, 1, MPI_INT, clientId, ItersDataMsg, MPI_COMM_WORLD, &handle);
}
void Server::listenForAvailableClients(int dummy, int clientsCount, MPI_Request *handlersToClients){
	for(int i=0; i<clientsCount;++i){
		int clientRank = i+1;
		MPI_Irecv(&dummy, 1, MPI_INT, clientRank, ItersDataMsg, MPI_COMM_WORLD, 
				&handlersToClients[i]);
	}
}
int Server::waitSomeTimeForClientsResponse(int clientsCount, MPI_Request* handlersToClients, int* responsiveClients){
	int receivedResponsesCount;
	MPI_Status responsesStatuses[clientsCount];
	MPI_Waitsome(clientsCount, handlersToClients, &receivedResponsesCount, responsiveClients, responsesStatuses);
	//cout << "Server::wait Some Time For Clients Response, handle: " << &handlersToClients[responsiveClients[0]] << " responded" << endl; 
	return receivedResponsesCount;
}
int** Server::getBoard(){
	return board.getBoardData();	
}
