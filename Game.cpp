#include "Game.h"

#include "cstdlib"
#include "input.h"
#include "output.h"
#include <unistd.h>

using std::cout;
using std::endl;

int convertLeveltoInt(level gameLevel) {
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
  return numberOfMines;
}

Game::Game(level gameLevel) : Table(convertLeveltoInt(gameLevel)) {
  this->gameLevel = gameLevel;
}

Game::Game(score toPlay) : Table(toPlay) {}

score Game::playGame() {

  bool multipleSelection = false;
  int afterSpielSelection = 0;

  while (true) {
    input currrentInput;
    Status status = CONTINUE;

    printTable(gameScore.point);

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
      status = controlAction(currrentInput.row, currrentInput.column);

      if (status == CONTINUE) {
        gameScore.draws.push_back(currrentInput.row * 10 +
                                  currrentInput.column);
        ++gameScore.steps;
        gameScore.point = calculatePoint(gameScore.steps, gameLevel, status);
        continue;
      } else if (status == GAMEOVER) {
        gameScore.draws.push_back(currrentInput.row * 10 +
                                  currrentInput.column);
        // nach GameOver
        gameScore.status = GAMEOVER;
        setVisibleforAllTable();
        printTable(gameScore.point);
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
        gameScore.draws.push_back(currrentInput.row * 10 +
                                  currrentInput.column);
        // nach Gewinn
        gameScore.status = SUCCESS;
        setVisibleforAllTable();
        printTable(gameScore.point);
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
      putNoteToPoint(currrentInput.row, currrentInput.column, NOTESAFE);
      break;
    case NOTEBOMBINPUT:
      putNoteToPoint(currrentInput.row, currrentInput.column, NOTEBOMB);
      break;
    case NOTERESETINPUT:
      putNoteToPoint(currrentInput.row, currrentInput.column, NONOTE);
      break;
    case DEFAULT:;
      /////////
    }
  }
}

int convertInttoInt(level gameLevel) {
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
  return numberOfMines;
}

void Game::autoPlay() {
  Status status;
  input currrentInput;
  int autoPlayPoint = 0;
  int autoPlayStep = 0;
  level autoPlayLevel = static_cast<level>(gameScore.mines.size() / 15 - 1);
  cout << autoPlayLevel;
  printTable(autoPlayPoint);
  sleep(2);
  for (size_t i = 0; i < gameScore.draws.size(); ++i) {
    currrentInput.row = gameScore.draws[i] / 10;
    currrentInput.column = gameScore.draws[i] % 10;
    sleep(2);
    status = controlAction(currrentInput.row, currrentInput.column);
    if (status == CONTINUE) {
      ++autoPlayStep;
      autoPlayPoint = calculatePoint(autoPlayStep, autoPlayLevel, status);
      printTable(autoPlayPoint);
      continue;
    } else if (status == GAMEOVER) {
      // nach GameOver
      gameScore.status = GAMEOVER;
      setVisibleforAllTable();
      printTable(autoPlayPoint);
      printGameOver(autoPlayStep);

    } else if (status == SUCCESS) {
      // nach Gewinn
      gameScore.status = SUCCESS;
      setVisibleforAllTable();
      printTable(autoPlayPoint);
      printSuccess(autoPlayStep);
    }
  }
  cout << "THE END" << endl;
  system("read");
}
