#include "Config.h"
#include <mpi.h>
#include "Utils.h"

struct Config app_init(int argc, char* argv[]){
	
	struct Config config;
	
	if (argc != 6) {
        inputError("Nalezy padac 5 argumentow", argv[0]);
    }
    
 	config.minx = atof(argv[1]);
 	config.maxx = atof(argv[2]);
	config.miny = atof(argv[3]);
	config.maxy = atof(argv[4]);
 	config.step = atof(argv[5]);
	
	config.rows =  floor((config.maxy - config.miny) / config.step) + 1;
	config.cols =  floor((config.maxx - config.minx) / config.step) + 1;
	
    if (config.maxx < config.minx) {
        inputError("MAX_X musi byc wieksze badz rowne od MIN_X", argv[0]);
    }
    
    if (config.maxy < config.miny) {
        inputError("MAX_Y musi byc wieksze badz rowne od MIN_Y", argv[0]);
    }
    
    if (config.step <= 0.0) {
        inputError("STEP musi byc wieksze od 0", argv[0]);
    }    

	if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
		error("Problem przy inicjalizacji MPI");
	}
	
	#ifdef MPE_LOGS
    MPE_Init_log();
    #endif
	
	if (MPI_Comm_size(MPI_COMM_WORLD, &config.procCount) != MPI_SUCCESS) {
		MPI_Finalize();
		error("Nie mozna odczytac liczby procesorow");	
	}

	if (MPI_Comm_rank(MPI_COMM_WORLD, &config.procRank) != MPI_SUCCESS) {
		MPI_Finalize();
		error("Nie mozna odczytac numeru procesu");
	}
	
	if (config.procCount < MIN_PROC_COUNT) {
		MPI_Finalize();
		error(sprintf("Musisz uzyc conajmniej %d procesow", MIN_PROC_COUNT));	
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(config.procRank == SERVER_TASK) {
        
        #ifdef MPE_LOGS
        MPE_Describe_state(REQ_TO_WORK_SEND_START, REQ_TO_WORK_SEND_END, "request to work", "red");
        MPE_Describe_state(LISTEN_FOR_WORKER_START, LISTER_FOR_WORKER_END, "non-blocking listen", "orange");
        MPE_Describe_state(WAITING_FOR_WORKER_START, WAITING_FOR_WORKER_END, "waiting for response", "yellow");
        MPE_Describe_state(SENDING_END_MARKER_START, SENDING_END_MARKER_END, "sending end-of-work", "green");
        MPE_Describe_state(WAITING_FOR_ORDER_START, WAITING_FOR_ORDER_END, "waiting for order (row number)", "blue");
        MPE_Describe_state(SENDING_RESULTS_TO_SERVER_START, SENDING_RESULTS_TO_SERVER_END, "sending back results", "pink");
        #endif
		
	}
	
}

void app_finish() {
	
	MPI_Barrier(MPI_COMM_WORLD);
    
    #ifdef MPE_LOGS
    MPE_Finish_log(OUTPUT_CLOG2_FILE);
    #endif
    
	MPI_Finalize();
	
}