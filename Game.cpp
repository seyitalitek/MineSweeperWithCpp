#include "Game.h"

#include "cstdlib"
#include "input.h"
#include "output.h"
using std::cout;
using std::endl;

Game::Game(level gameLevel) {
  int numberOfMines = 15;
  switch (gameLevel) {
  case LOW:
    break;
  case MID:
    numberOfMines = 20;
    break;
  case HIGH:
    numberOfMines = 25;
    break;
  };
  this->table = Table(numberOfMines);
  this->gameLevel = gameLevel;
}

score Game::playGame() {

  bool multipleSelection = false;
  int afterSpielSelection = 0;

  while (true) {
    input currrentInput;
    Status status = CONTINUE;

    table.printTable(gameScore.point);

    if (multipleSelection) {
      cout << "      Sie waren schon da!" << endl;
      multipleSelection = false;
    }

    currrentInput = getInputForSpiel();

    switch (currrentInput.flag) {
    ////
    case EXIT:
      printAfterSpielMenu();
      afterSpielSelection = getInputAfterSpiel();
      if (afterSpielSelection == 2) {
        gameScore.newGame = true;
      } else if (afterSpielSelection == 3) {
        gameScore.save = true;
        gameScore.name = getUserName();
      }
      return gameScore;
    ////
    case OPENINPUT:
      /////
      status = table.controlAction(currrentInput.row, currrentInput.column);
      if (status == CONTINUE) {
        ++gameScore.steps;
        gameScore.point = calculatePoint(gameScore.steps, gameLevel, status);
        continue;
      } else if (status == GAMEOVER) {
        // nach GameOver
        gameScore.status = GAMEOVER;
        table.setVisibleforAllTable();
        table.printTable(gameScore.point);
        printGameOver(gameScore.steps);
        printAfterSpielMenu();
        afterSpielSelection = getInputAfterSpiel();
        if (afterSpielSelection == 2) {
          gameScore.newGame = true;
        } else if (afterSpielSelection == 3) {
          gameScore.save = true;
          gameScore.name = getUserName();
        }
        return gameScore;

      } else if (status == SUCCESS) {
        // nach Gewinn
        gameScore.status = SUCCESS;
        table.setVisibleforAllTable();
        table.printTable(gameScore.point);
        printSuccess(gameScore.steps);
        printAfterSpielMenu();
        afterSpielSelection = getInputAfterSpiel();
        if (afterSpielSelection == 2) {
          gameScore.newGame = true;
        } else if (afterSpielSelection == 3) {
          gameScore.save = true;
          gameScore.name = getUserName();
        }
        return gameScore;

      } else if (status == MULTIPEL) {

        multipleSelection = true;
        continue;
      }
      break;
      /////
    case NOTESAFEINPUT:
      table.putNoteToPoint(currrentInput.row, currrentInput.column, NOTESAFE);
      break;
    case NOTEBOMBINPUT:
      table.putNoteToPoint(currrentInput.row, currrentInput.column, NOTEBOMB);
      break;
    case NOTERESETINPUT:
      table.putNoteToPoint(currrentInput.row, currrentInput.column, NONOTE);
      break;
    case DEFAULT:;
      /////////
    }
  }
}
