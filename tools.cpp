#include "tools.h"

int calculatePoint(int steps, level gameLevel, Status result) {
  int point = 0;
  point = steps * (static_cast<int>(gameLevel) + 1) +
          100 * (result == SUCCESS ? 1 : 0);
  return point;
}
bool sortByPoint(const score &a, const score &b) { return (a.point < b.point); }
