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

// Niveau ist die Zahl von Mines
// Konstruktur für echtes Spiel
// Das Spiel-Niveau wird bestimmt durch Konstruktur von Baseklasse
// convertLeveltoInt gibt int zurück für Konstruktur von Baseklasse
Game::Game(level level_for_new_game)
    : Table(convertLeveltoInt(level_for_new_game)) {
  this->gameLevel = level_for_new_game; // initializirung von attribute
}

// Konstruktur für Autoplay
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
                                  currrentInput.column); // Merkung der Züge
        ++gameScore.steps;
        gameScore.point = calculatePoint(gameScore.steps, gameLevel, status);
        continue;
      } else if (status == GAMEOVER) {
        gameScore.draws.push_back(
            currrentInput.row * 10 +
            currrentInput.column); // Merkung von letzten Zug
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
        gameScore.draws.push_back(currrentInput.row *
                                      10 + // Merkung von letzten Zug
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

// Autoplay
void Game::autoPlay() {

  Status status; // Gewonnen oder Verloren oder weiter
  input currrentInput;
  int autoPlayPoint = 0;
  int autoPlayStep = 0;
  level autoPlayLevel = static_cast<level>(gameScore.mines.size() / 15 - 1);
  printTable(autoPlayPoint);
  for (size_t i = 0; i < gameScore.draws.size(); ++i) {
    currrentInput.row = gameScore.draws[i] / 10;    // eingaben von Score lesen
    currrentInput.column = gameScore.draws[i] % 10; // ""   ""   ""

    /////input visualization
    cout << "      ";
    cout.flush();
    usleep(500000);
    cout << static_cast<char>(currrentInput.column +
                              65); // eingabe als ASCII charachter anzeigen
    cout.flush();
    usleep(500000);
    cout << currrentInput.row + 1 << " ";
    cout.flush();
    sleep(1);
    cout.flush();
    /////

    status = controlAction(currrentInput.row, currrentInput.column);
    if (status == CONTINUE) { // wenn die Zug erfolgreich ist
      ++autoPlayStep;
      autoPlayPoint = calculatePoint(autoPlayStep, autoPlayLevel, status);
      printTable(autoPlayPoint);
      continue;
    } else if (status == GAMEOVER) { // wenn die Mine betretet wird
      // nach GameOver
      gameScore.status = GAMEOVER;
      setVisibleforAllTable();
      printTable(autoPlayPoint);
      printGameOver(autoPlayStep);

    } else if (status == SUCCESS) { // wenn das Spiel gewonnen wird
      // nach Gewinn
      gameScore.status = SUCCESS;
      setVisibleforAllTable();
      printTable(autoPlayPoint);
      printSuccess(autoPlayStep);
    }
  }
  cout << "     THE END" << endl;
  system("read");
}
