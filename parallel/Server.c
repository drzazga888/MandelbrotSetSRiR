#include "Server.h"
#include "Config.h"
#include "Utils.h"
#include <stdlib.h>

#ifdef MPE_LOGS
#include "mpe.h"
#endif

void server_run(struct Config *config) {
	
	struct Board board = board_init(config->rows, config->cols);
	int workersCount = config->procCount - 1;
	MPI_Request handlersToClients[workersCount];
	int tempNr[workersCount];
	int endMarker = END_MARKER;
	int requestsSent = 0;
	
	int **tempRows = (int **) malloc(sizeof(int*) * workersCount);
	for (int i = 0; i < workersCount; ++i) {
		tempRows[i] = (int *) malloc(sizeof(int) * config->rows);
	}
	
	for(int i=0; board_areStillRowsToProcess(&board) && i<workersCount; ++i){
		int clientId = i+1;
		startListenerForCompletedWork(config->cols, clientId, &handlersToClients[i], tempRows[i]);
		tempNr[i] = requestWorkTo(&board, clientId);
	}
	
	while(true)
	{
		int responsiveClients[workersCount];
		int responsesCount = waitSomeTimeForClientsResponse(workersCount, handlersToClients, responsiveClients);
		
		if (responsesCount < 1) {
			break;
		}
		
		for(int i=0; i<responsesCount; ++i)
		{
			int requestIndex = responsiveClients[i];
			int clientId = requestIndex+1;
			
			board_setRow(&board, tempNr[requestIndex], tempRows[requestIndex]);
			
			/*if (requestsSent >= config->rows) {
				handlersToClients[requestIndex] = MPI_REQUEST_NULL;
			}*/
			
			if (board_areStillRowsToProcess(&board)) {
				startListenerForCompletedWork(config->cols, clientId, &handlersToClients[requestIndex], tempRows[requestIndex]);
				tempNr[requestIndex] = requestWorkTo(&board, clientId);
			}
		}
	}
	
	for(int i=0; i<workersCount; ++i){
		
		#ifdef MPE_LOGS
		MPE_Log_event(SENDING_END_MARKER_START, 0, "sending end-of-work - start");
		#endif
		
		MPI_Send(&endMarker, 1, MPI_INT, i+1, ItersDataMsg, MPI_COMM_WORLD);
		
		#ifdef MPE_LOGS
		MPE_Log_event(SENDING_END_MARKER_END, 0, "sending end-of-work - end");
		#endif
	}
	
	exportBoardToFile(config, &board);
		
	for (int i = 0; i < workersCount; ++i) {
         free(tempRows[i]);
    }
    free(tempRows);
	
	board_free(&board);
	
}

int requestWorkTo(struct Board *board, int clientId){
	int nextRow = board_next(board);
	
	#ifdef MPE_LOGS
	MPE_Log_event(REQ_TO_WORK_SEND_START, 0, "request to work send - start");
	#endif
	
	MPI_Send(&nextRow, 1, MPI_INT, clientId, ItersDataMsg, MPI_COMM_WORLD);
	
	#ifdef MPE_LOGS
	MPE_Log_event(REQ_TO_WORK_SEND_END, 0, "request to work send - end");
	#endif
	
	return nextRow;
}

void startListenerForCompletedWork(int cols, int clientId, MPI_Request *handle, int *promisedRow){

	#ifdef MPE_LOGS
	MPE_Log_event(LISTEN_FOR_WORKER_START, 0, "non-blocking listen - start");
	#endif

	MPI_Irecv(promisedRow, cols, MPI_INT, clientId, ItersDataMsg, MPI_COMM_WORLD, handle);
	
	#ifdef MPE_LOGS
	MPE_Log_event(LISTER_FOR_WORKER_END, 0, "non-blocking listen - end");
	#endif
}

int waitSomeTimeForClientsResponse(int clientsCount, MPI_Request* handlersToClients, int *responsiveClients){
	int receivedResponsesCount;
	MPI_Status responsesStatuses[clientsCount];
	
	#ifdef MPE_LOGS
	MPE_Log_event(WAITING_FOR_WORKER_START, 0, "waiting for worker - start");
	#endif
	
	MPI_Waitsome(clientsCount, handlersToClients, &receivedResponsesCount, responsiveClients, responsesStatuses);

	#ifdef MPE_LOGS
	MPE_Log_event(WAITING_FOR_WORKER_END, 0, "waiting for worker - end");
	#endif
	
	return receivedResponsesCount;
}
