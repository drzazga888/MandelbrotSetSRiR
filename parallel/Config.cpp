#include "Config.h"
#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include "Utils.h"
#include <string>

//Because we employ manager-workers design, there
//should be at least 2 processors
const int MIN_PROC_COUNT = 2; 

using std::cout;
using std::endl;
using std::cerr;
Config& appConfig(){
	return Config::getInstance();
}
Config::Config(){
}
Config& Config::getInstance(){
	static Config instance;
	return instance;
}
void Config::initialize(int argc, char* argv[]){	
    if (argc != 6) {
        inputError("Nalezy padac 5 argumentow", argv[0]);
    }
    
 	minx = atof(argv[1]);
 	maxx = atof(argv[2]);
	miny = atof(argv[3]);
	maxy = atof(argv[4]);
 	step = atof(argv[5]);
    
    if (maxx < minx) {
        inputError("MAX_X musi byc wieksze badz rowne od MIN_X", argv[0]);
    }
    
    if (maxy < miny) {
        inputError("MAX_Y musi byc wieksze badz rowne od MIN_Y", argv[0]);
    }
    
    if (step <= 0.0) {
        inputError("STEP musi byc wieksze od 0", argv[0]);
    }    

	if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
	{
		error("Problem przy inicjalizacji MPI");
	}
	if (MPI_Comm_size(MPI_COMM_WORLD, &procCount) != MPI_SUCCESS) {
		error("Nie mozna odczytac liczby procesorow");	
		MPI_Finalize();
	}

	if (MPI_Comm_rank(MPI_COMM_WORLD, &procRank) != MPI_SUCCESS) {
		error("Nie mozna odczytac numeru procesu");
		MPI_Finalize();
	}
}
int Config::getNumOfClients(){
	if(procCount < MIN_PROC_COUNT){
		warning(std::string("Dostepna ilosc procesorow: ") + std::to_string(procCount));	
	}
	return procCount-1; // -1 for one serwer proc	
}
void Config::inputError(const char *message, const char *program) {
    cerr << "Poprawne wejscie:" << endl;
    cerr << program << " MIN_X MAX_X MIN_Y MAX_Y STEP" << endl;
	error(message);
}
