#ifndef TABLE_H
#define TABLE_H

#include "tools.h"
#include <vector>

class Table {
protected:
  point table[10][10];

public:
  score gameScore;
  Table(int NumberOFMines = 10, bool isSecret = true);
  Table(score toPlay);
  Status controlAction(int row, int column);
  void putNoteToPoint(int row, int column, Note type);
  void printTable(int points = 0);
  void setVisibleforAllTable(
      bool isVisible = true); // to make the all points visible
};

#endif // TABLE_H
