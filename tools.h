#ifndef TOOLS_H
#define TOOLS_H
#include <iostream>
#include <string>
#include <vector>
using std::string;
enum level {
  LOW,
  MID,
  HIGH,
};

enum Status { SUCCESS, GAMEOVER, CONTINUE, MULTIPEL };

struct score {
  int point = 0;
  int steps = 0;
  bool save = false;
  bool newGame = false;
  string name = "no_name_provided";
  Status status = Status::CONTINUE;
  std::vector<int> mines;
  std::vector<int> draws;
};
enum Content {
  BOMB,
  SAFE,
};

enum Note { NOTEBOMB, NOTESAFE, NONOTE };

struct point { // representation of points in the Game-Area
  int row;
  int column;
  int around;
  bool isSecret;
  bool isVisited;
  Content content; // Content is Bomb or Safe
  Note note;       // marking of the points will be saved (p,b)
};
int calculatePoint(int steps, level gameLevel, Status result);
bool sortByPoint(const score &a, const score &b);
#endif // TOOLS_H
