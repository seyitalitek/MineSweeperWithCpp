#ifndef GAME_H
#define GAME_H
#include "Table.h"
#include "tools.h"

using std::string;

class Game : public Table {
  level gameLevel;
  score gameScore;

public:
  Game();
  Game(level gameLevel);
  score playGame();
};

#endif // GAME_H
