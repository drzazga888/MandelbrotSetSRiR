#include "Client.h"
#include "Config.h"
#include "Utils.h"
#include <complex.h>
#include <mpi.h>
#include <math.h>

#ifdef MPE_LOGS
#include "mpe.h"
#endif

#include <stdio.h>

void client_run(struct Config *config){
	
	double x_mult = (config->maxx - config->minx) / (config->cols - 1);
	double y_mult = (config->maxy - config->miny) / (config->rows - 1);
	int row;
	int iters[config->cols];
	
	while(true)
	{
		MPI_Status status;

		#ifdef MPE_LOGS
		MPE_Log_event(WAITING_FOR_ORDER_START, 0, "waiting for server - start");
		#endif
		
		MPI_Recv(&row, 1, MPI_INT, SERVER_TASK, ItersDataMsg, MPI_COMM_WORLD, &status);
		
		#ifdef MPE_LOGS
		MPE_Log_event(WAITING_FOR_ORDER_END, 0, "waiting for server - end");
		#endif
		
		if (row == END_MARKER) {
			break;
		}
		for (int col = 0; col < config->cols; ++col) {
			iters[col] = mandelbrot(config->minx, config->miny, row, col, x_mult, y_mult);
		}
		
		#ifdef MPE_LOGS
		MPE_Log_event(SENDING_RESULTS_TO_SERVER_START, 0, "sending results - start");
		#endif
		
		MPI_Send(iters, config->cols, MPI_INT, SERVER_TASK, ItersDataMsg, MPI_COMM_WORLD);
		
		#ifdef MPE_LOGS
		MPE_Log_event(SENDING_RESULTS_TO_SERVER_END, 0, "sending results - end");
		#endif
		
	}
		
}

int mandelbrot(int minx, int miny, int row, int col, double x_mult, double y_mult){
	double complex c = (x_mult * col + minx) + (y_mult * row + miny) * I;
	double complex z = 0;	
	int iters = 0;   
	do {
		z = z * z + c;
		++iters;
	} while (iters < MAX_ITERS && fabs(creal(z)) <= 2.0);
	return iters;
}