#pragma once

#define MIN_PROC_COUNT 2
#define OUTPUT_CLOG2_FILE "mpe-logs"
#define OUTPUT_DATA_FILE "data.txt"
#define SERVER_TASK 0
#define END_MARKER -1
#define MAX_ITERS 999

#define ItersDataMsg 0

#define REQ_TO_WORK_SEND_START 0
#define REQ_TO_WORK_SEND_END 1

#define LISTEN_FOR_WORKER_START 2
#define LISTER_FOR_WORKER_END 3

#define WAITING_FOR_WORKER_START 4
#define WAITING_FOR_WORKER_END 5

#define SENDING_END_MARKER_START 6
#define SENDING_END_MARKER_END 7

#define WAITING_FOR_ORDER_START 8
#define WAITING_FOR_ORDER_END 9

#define SENDING_RESULTS_TO_SERVER_START 10
#define SENDING_RESULTS_TO_SERVER_END 11

struct Config {
	double minx;
	double maxx;
	double miny;
	double maxy;
	double step;
	int rows;
	int cols;
	int procRank;
	int procCount;
};

struct Config app_init(int argc, char *argv[]);
void app_finish();
