#ifndef GAME_H
#define GAME_H
#include "Table.h"
#include "tools.h"

using std::string;

class Game : public Table {
  level gameLevel;

public:
  Game(level gameLevel = LOW);
  Game(score toPlay);
  score playGame();
  void autoPlay();
};

#endif // GAME_H
