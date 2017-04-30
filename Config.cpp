#include "Config.h"
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::cerr;
Config& appConfig()
{
	return Config::getInstance();
}

Config::Config()
{
}
Config& Config::getInstance()
{
	static Config instance;
	return instance;
}
void Config::initialize(int argc, char* argv[])
{	
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
}
void Config::inputError(const char *message, const char *program) {
    cerr << "Blad: " << message << endl;
    cerr << "Poprawne wejscie:" << endl;
    cerr << program << " MIN_X MAX_X MIN_Y MAX_Y STEP" << endl;
    exit(-1);
}
