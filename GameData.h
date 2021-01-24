#ifndef HICHSCORES_H
#define HICHSCORES_H
#include "tools.h"
#include <algorithm>
#include <fstream>
using std::fstream;
using std::string;
using std::vector;

class GameData {
  string filename;
  vector<score> highscores;
  fstream file;

public:
  GameData(string filename);
  vector<score> *getHighScores();
  void addScore(score newScore);
  void writeData();
  void resetData();
  void printHighScores();
};

#endif // HICHSCORES_H
