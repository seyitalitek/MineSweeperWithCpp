/*
 *
 *  Ali Tekin
 *
 */

#include "Game.h"
#include "GameData.h"
#include "Table.h"
#include "input.h"
#include "output.h"
#include "tools.h"
#define TEST // define for testing
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
      if (getInputFromHighScore() == 2)
        gameData.resetData();
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
  vector<score> scores;
  Game game;
  scores.push_back(game.playGame());
  Game autoPlay(scores[0]);
  autoPlay.autoPlay();
#endif
}
