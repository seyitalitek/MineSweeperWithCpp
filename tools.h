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
};
int calculatePoint(int steps, level gameLevel, Status result);
bool sortByPoint(const score &a, const score &b);
#endif // TOOLS_H
