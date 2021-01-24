#ifndef INPUT_H
#define INPUT_H
#include "tools.h"

#include <iostream>
#include <regex>
#include <string>

enum inputFlag {
  OPENINPUT,
  NOTESAFEINPUT,
  NOTEBOMBINPUT,
  NOTERESETINPUT,
  EXIT,
  DEFAULT,
};
struct input {
  int column;
  int row;
  inputFlag flag = inputFlag::DEFAULT;
};
input getInputForSpiel();
int getInputFromMenu();
int getInputAfterSpiel();
std::string getUserName();
int getInputLevel();
int getInputFromHighScore();

#endif // INPUT_H
