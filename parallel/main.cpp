#include <iostream>
#include <iomanip>
#include <complex>
#include <fstream>
#include "Config.h"
#include "Server.h"
#include "Client.h"
#include "Utils.h"

#ifdef MPE_LOGS
#include "mpe.h"
#include "MpeLogs.h"
#endif

int main(int argc, char *argv[]) {
	Struct Config config = config_init(argc, argv);
    if (config.procRank == SERVER_TASK) {
        server_run(&config);
    } else {
        client_run(&config);
    }
    app_finish();
    return 0;
}