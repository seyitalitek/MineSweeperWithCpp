#ifndef GAME_H
#define GAME_H
#include "Table.h"
#include "tools.h"

using std::string;

class Game {
  level gameLevel;
  Table table;
  score gameScore;

public:
  Game();
  Game(level gameLevel);
  score playGame();
};

#endif // GAME_H
