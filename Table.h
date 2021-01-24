#ifndef TABLE_H
#define TABLE_H

#include "tools.h"

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

class Table {
protected:
  point table[10][10];

public:
  Table(int NumberOFMines = 10, bool isSecret = true);
  Status controlAction(int row, int column);
  void putNoteToPoint(int row, int column, Note type);
  void printTable(int points = 0);
  void setVisibleforAllTable(
      bool isVisible = true); // to make the all points visible
};

#endif // TABLE_H
