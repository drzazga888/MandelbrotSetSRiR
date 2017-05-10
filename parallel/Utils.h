#pragma once

#include "Board.h"
#include "Config.h"

void error(const char *message);
void inputError(const char *message, const char *program);
void exportBoardToFile(struct Config *config, struct Board *board);