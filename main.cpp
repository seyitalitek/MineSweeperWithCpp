
#include "Game.h"
#include "GameData.h"
#include "Table.h"
#include "input.h"
#include "output.h"
#include "tools.h"
#define GAME // define TEST  for testing
using namespace std;

int main() {
#ifndef TEST
  GameData gameData("highscores.txt");
  level gameLevel = level::LOW;
  int selection = 0;
  while (true) {
    ///// Hauptmenu /////////
    printMenu();
    if (selection != 2) // 2=newGame
      selection = getInputFromMenu();

    if (selection == 5) { // Exit
      return 0;
    } else if (selection == 4) { // Highscores
      gameData.printHighScores();
      printHighScoreMenu();
      int inputFromHighscoremenu = getInputFromHighScore();
      if (inputFromHighscoremenu == 2)
        gameData.resetData();
      else if (inputFromHighscoremenu == 3) {
        inputFromHighscoremenu =
            getInputFromMenus(gameData.getHighScores()->size());
        int size_of_scores = gameData.getHighScores()->size();
        Game autoPlay(gameData.getHighScores()->at(
            size_of_scores - inputFromHighscoremenu)); // die Reihenfolge der
                                                       // Scores ist umgekehrt
        autoPlay.autoPlay();
      }
      continue;
    } else if (selection == 3) { // Level settings
      printLevelOptions(gameLevel);
      gameLevel = static_cast<level>(getInputLevel());
      continue;
    } else if (selection == 2) { // new game
      Game game(gameLevel);
      score newScore;
      newScore = game.playGame();
      if (newScore.save) {
        gameData.addScore(newScore); // add score to object
        gameData.writeData();        // and also to file
      } else if (newScore.newGame) {
        selection = 2;
        continue;
      }
    } else if (selection == 1) { // guide
      printAnleitung();
      continue;
    }
    selection = 0;
    ///// Hauptmenu //////////
  }

  return 0;
#endif
#ifdef TEST
  Game game;
  Game game2;
  GameData highscores("highscores.txt");
  Game autoPlay1(highscores.getHighScores()->at(0));
  Game autoPlay2(highscores.getHighScores()->at(1));
  autoPlay1.autoPlay();
  autoPlay2.autoPlay();
#endif
}
