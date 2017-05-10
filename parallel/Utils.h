#pragma once

void error(const char *message);
void inputError(const char *message, const char *program);
void exportBoardToFile(const char *filename, struct Config *config, struct Board *board);