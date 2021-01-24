#include "output.h"

using std::cout;
using std::endl;

void printMenu() {
  system("clear");
  cout << "\n Wilkommen bei Minesweeper" << endl;
  cout << "\n (1) Anleitung" << endl;
  cout << "\n (2) Spielen" << endl;
  cout << "\n (3) Niveau Einstellen" << endl;
  cout << "\n (4) Highscores" << endl;
  cout << "\n (5) Beenden" << endl;
}

void printAnleitung() {
  system("clear");
  cout << "                                                    " << endl;
  cout << "              Spielregeln                           " << endl;
  cout << "                                                    " << endl;
  cout << "  1 - Das Spiel is beendet, wenn eine Mine aufgedeckt wird." << endl;
  cout
      << endl
      << "  2 - Das Spiel wird fortgesetzt, wenn Sie ein leeres Feld aufdecken."

      << endl
      << endl;
  cout
      << "  3 - Wird beim Aufdecken eines Feldes eine Zahl angezeigt, steht "
         "diese \n"
         "  für die Anzahl der Minen, die in den benachbarten 8 Feldern \n"
         "  verborgen sind. Anhand dieser Angabe kann abgeleitet werden, "
         "unter \n"
         "  welchen der angrenzenden Feldern sich Minen befinden und auf "
         "welche "
         "  \n"
         "  Felder gefahrlos geklickt werden kann.\n"
         "\n   Drücken Sie eine beliebige Taste, um zum Hauptmenu zurückzugehen"
      << endl;
  system("read");
}

void printHighScores(std::vector<score> highscores) {
  system("clear");
  cout << "                                  " << endl;
  cout << "            TOP TEN               " << endl;
  cout << "                                  " << endl;
  int size = highscores.size();
  for (int i = size - 1; i >= 0; i--) {
    cout << "            " << size - i << ". " << highscores[i].name << "\t"
         << highscores[i].point << endl;
  };
  cout << endl;
}

void printSuccess(int steps) {
  cout << "            GEWONNEN !!!\n";
  cout << "      Unbeschadete Schritte: " << steps + 1 << endl;
  cout << "                                                " << endl;
}

void printGameOver(int steps) {

  cout << "            GAME OVER!!!\n";
  cout << "      Unbeschadete Schritte: " << steps << endl;
  cout << "                                                " << endl;
}

void printAfterSpielMenu() {
  cout << "(1) Zum Hauptmenu, (2)  Neuspiel (3) Score speichern" << endl;
}

void printLevelOptions(level gameLevel) {
  system("clear");
  cout << "\n Wählen Sie ein Niveau\n" << endl;
  cout << "\n (1) Anfänger" << (gameLevel == level::LOW ? "*" : "") << endl;
  cout << "\n (2) Fortgeschrittene" << (gameLevel == level::MID ? "*" : "")
       << endl;
  cout << "\n (3) Profis" << (gameLevel == level::HIGH ? "*" : "") << endl
       << endl;
}

void printHighScoreMenu() {
  cout << "(1) Zum Hauptmenu, (2)  Liste löschen" << endl;
}
