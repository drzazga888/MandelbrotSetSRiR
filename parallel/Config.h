#pragma once

#define MIN_PROC_COUNT 2
#define OUTPUT_CLOG2_FILE "mpe-logs"
define SERVER_TASK 0
define END_MARKER 1

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
