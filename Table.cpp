#include "Table.h"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;

Table::Table(int NumberOfMines, bool isSecret) {

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      table[i][j].row = i;
      table[i][j].column = j;
      table[i][j].content = Content::SAFE;
      table[i][j].isSecret = isSecret;
      table[i][j].around = 0;
      table[i][j].note = Note::NONOTE;
      table[i][j].isVisited = false;
    }
  }

  // Zufällige Zahlen für die Stelle von Mines
  std::vector<int> mines;
  srand(time(0));

  for (int i = 0; i <= NumberOfMines; i++) {
    int count = 0;

    while (true) {
      bool found = true;
      int r = rand() % 100;
      for (int j = 0; j < i; j++) {
        if (mines[j] == r) {
          found = false;
          break;
        }
      }
      if (!found)
        continue;
      mines.push_back(r);
      count++;
      break;
    }
  }

  // Plazieren von Mines
  for (int i = 0; i < NumberOfMines; i++) {
    table[mines[i] / 10][mines[i] % 10].content = Content::BOMB;
  }

  // write arounds
  for (int i = 0; i < NumberOfMines; i++) { // für jede Mine
    int row = mines[i] / 10;                // wird die Position ausgerechnet
    int column = mines[i] % 10;
    /*die Nachbarn von Minen wird entsprechen aktualisiert*/
    /* indem Data.around für jede anliegende Mine inkrementiert wird*/
    if (row) {
      if (column)
        table[row - 1][column - 1].around += 1;
      table[row - 1][column].around += 1;
      if (!(column == 9))
        table[row - 1][column + 1].around += 1;
    }
    if (column)
      table[row][column - 1].around += 1;
    if (!(column == 9))
      table[row][column + 1].around += 1;

    if (!(row == 9)) {
      if (column)
        table[row + 1][column - 1].around += 1;
      table[row + 1][column].around += 1;
      if (!(column == 9))
        table[row + 1][column + 1].around += 1;
    }
  }
}

// Table::Table(Table &OldTable) {
//  for (int i = 0; i < 10; i++) {
//    for (int j = 0; j < 10; j++) {
//      table[i][j] = OldTable.table[i][j];
//    }
//  }
//}

void Table::putNoteToPoint(int row, int column, Note type) {
  table[row][column].note = type;
}

void Table::setVisibleforAllTable(bool isVisible) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      table[i][j].isSecret = !isVisible;
    }
  }
}

Status Table::controlAction(int row, int column) {
  Status status = Status::SUCCESS;

  if (table[row][column].content == Content::SAFE &&
      !table[row][column].isVisited) {   // wenn die Stelle sicher ist
    table[row][column].isSecret = false; // nicht mehr Geheim
    table[row][column].isVisited = true;

    // wenn diese stelle keine Mine als Nachbar hat,
    // werden diese Stellen auch recursive geöffnet
    if (!table[row][column].around) {
      // recursion

      if (row) {
        if (column)
          if (table[row - 1][column - 1].content == Content::SAFE)
            this->controlAction(row - 1, column - 1);
        if (table[row - 1][column].content == 0)
          this->controlAction(row - 1, column);
        if (!(column == 9))
          if (table[row - 1][column + 1].content == Content::SAFE)
            this->controlAction(row - 1, column + 1);
      }
      if (column)
        if (table[row][column - 1].content == Content::SAFE)
          this->controlAction(row, column - 1);
      if (!(column == 9))
        if (table[row][column + 1].content == Content::SAFE)
          this->controlAction(row, column + 1);

      if (!(row == 9)) {
        if (column)
          if (table[row + 1][column - 1].content == Content::SAFE)
            this->controlAction(row + 1, column - 1);
        if (table[row + 1][column].content == Content::SAFE)
          this->controlAction(row + 1, column);
        if (!(column == 9))
          if (table[row + 1][column + 1].content == Content::SAFE)
            this->controlAction(row + 1, column + 1);
      }
    }
    //

  } else if (table[row][column].content == Content::BOMB) { // wenn an dieser
                                                            // Stelle mine ist
    table[row][column].isSecret = false;
    status = Status::GAMEOVER;
    return status;
  } else if (table[row][column].isVisited == true) {
    status = Status::MULTIPEL;
    return status;
  }

  for (int i = 0; i < 10; i++) { // letztes Kontroll ob es noch
    bool flag = false;           // keine geöffnete Stellen gibt
    for (int j = 0; j < 10; j++) {
      if (table[i][j].content == 0) {
        status = Status::CONTINUE;
        flag = true;
        break;
      }
    }
    if (flag)
      break;
  }
  return status;
}

void Table::printTable(int points) {
  system("clear");
  cout << "\n Mini Mine Sweeper      Score: " << points << "\n" << endl;
  cout << "     A B C D E F G H I J" << endl << endl;
  for (int i = 0; i < 10; i++) {
    cout << (i == 9 ? " " : "  ") << i + 1 << " ";
    for (int j = 0; j < 10; j++) {

      if (table[i][j].isSecret) // prinzipiell alles ist geheim
      {
        if (table[i][j].note == Note::NONOTE)
          cout << " *";
        else if (table[i][j].note == Note::NOTESAFE)
          cout << " p";
        else if (table[i][j].note == Note::NOTEBOMB)
          cout << " b";
      } else if (table[i][j].content == Content::SAFE) // für sichere Stelle
      {
        if (table[i][j].around) // falls anligende Stelle mines haben
          cout << " " << table[i][j].around; // diese Anzahl wird geschrieben
        else
          cout << " _";
      }                                                // sonst _ wird angezeigt
      else if (table[i][j].content == Content::BOMB) { // für Mines "o"
        cout << " o";
      }
    }
    cout << endl << endl;
  }
}
