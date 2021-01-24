#ifndef OUTPUT_H
#define OUTPUT_H
#include "tools.h"

#include <iostream>
#include <string>
#include <vector>

void printMenu();
void printAnleitung();
void printHighScores(std::vector<score> highscores);
void printGameOver(int steps);
void printSuccess(int steps);
void printLevelOptions(level gameLevel);
void printAfterSpielMenu();
void printHighScoreMenu();
#endif // OUTPUT_H
