#include "GameData.h"

using std::cout;
using std::endl;

// to read and write highscores from - to file

GameData::GameData(string filename) {
  this->filename = filename;
  fstream file;
  file.open(filename, std::ios::in);
  int isEmpty = 1;

  if (file) // first charachter in file will be 1
            // if file is empty
    file >> isEmpty;
  else {
    file.close();
    file.open(filename, std::ios::out | std::ios::trunc);
    file << 1 << " ";
    file.close();
  }
  if (file && !isEmpty) { // if the file not empty

    while (true) {
      string name;
      score temp;
      int point;
      int mine;
      int c;
      //////
      file >> name; // to bypass rs
      if (name == "end")
        break;
      //////
      file >> name;
      temp.name = name;
      file >> point;
      temp.point = point;
      file >> c; // Anzahl der Mines
      for (int i = 0; i < c; ++i) {
        file >> mine;
        temp.mines.push_back(mine);
      }
      file >> c; // Anzahl der Züge
      for (int i = 0; i < c; ++i) {
        file >> mine;
        temp.draws.push_back(mine);
      }
      file >> name; // to bypass re
      this->highscores.push_back(temp);
    }
  }
  file.close();
}
// reading scores from file
vector<score> *GameData::getHighScores() { return &this->highscores; }
void GameData::writeData() {
  fstream file;
  file.open(filename, std::ios::out);
  if (file) {
    file << 0 << " \n";
    for (score sc : this->highscores) {
      file << "rs ";
      file << sc.name << " ";
      file << sc.point << " ";
      file << sc.mines.size() << " ";
      for (int mine : sc.mines) {
        file << mine << " ";
      }
      file << sc.draws.size() << " ";
      for (int draw : sc.draws) {
        file << draw << " ";
      }
      file << "re\n";
    }
    file << "end";
  } else {
    std::cout << "unable to open file ";
  }

  file.close();
}

void GameData::addScore(score newScore) {
  highscores.push_back(newScore);
  std::sort(highscores.begin(), highscores.end(), sortByPoint);
};

void GameData::resetData() {
  fstream file;
  file.open(filename, std::ios::out | std::ios::trunc);
  file << 1 << " ";
  file.close();
  this->highscores.clear();
}

void GameData::printHighScores() {
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
