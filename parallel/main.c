#include "Config.h"
#include "Server.h"
#include "Client.h"

int main(int argc, char *argv[]) {
	struct Config config = app_init(argc, argv);
    if (config.procRank == SERVER_TASK) {
        server_run(&config);
    } else {
        client_run(&config);
    }
    app_finish();
    return 0;
}