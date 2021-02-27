#ifndef GAME_H
#define GAME_H
#include "Table.h"
#include "tools.h"

using std::string;

class Game : public Table {
  level gameLevel;

public:
  Game(level gameLevel = LOW); // für echtes Spiel
  Game(score toPlay);          // für AutoPlay

  score playGame(); // um das Spiel spielen lassen
  void autoPlay();  // zum Autuplay
};

#endif // GAME_H
