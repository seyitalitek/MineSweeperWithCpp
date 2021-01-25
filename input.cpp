#include "input.h"
using std::cin;
using std::cout;
using std::endl;
using std::regex;
using std::string;

input getInputForSpiel() {
  input fromUser;
  regex re("[Xx]|(?:[A-Ja-j](?:10|\\d))");
  while (true) {
    string input;
    int first;
    int second;
    string temp;
    cout
        << "\n Bitte geben Sie ein Feld in der Form [A][1] ein, Abbruch mit X:";
    getline(cin, input);
    temp = input;
    if (!regex_match(input, re)) {
      cout << "            Invalid Input" << endl;
      continue;
    } else {
      if (temp.length() == 1) {
        fromUser.flag = inputFlag::EXIT;
      } else if (temp.length() == 2 || temp.length() == 3) {
        first = int(temp.at(0));
        second = int(temp.at(1));
        if ((first > 64) && (first < 75)) {
          fromUser.column = first - 65;
        } else if ((first > 96) && (first < 107)) {
          fromUser.column = first - 97;
        } else {
          cout << "Unknown Error" << endl;
        }
        if (temp.length() == 2) {
          fromUser.row = second - 49;
        } else if (temp.length() == 3) {
          fromUser.row = 9;
        } else {
          cout << "Unknown Error" << endl;
        }
      } else {
        cout << "Unknown Error" << endl;
      }
      break;
    }
  }
  regex re2("[OoPpBbRrXx]");
  while (fromUser.flag != inputFlag::EXIT) {
    string input;
    cout << " Öffnen : 'o', Markieren; sicher: 'p', gefährlich: b\n"
            " Notiz zurücksetzen: r, exit: 'x':  ";
    getline(cin, input);
    if (!regex_match(input, re2)) {
      cout << "            Invalid Input" << endl;
      continue;
    } else {

      switch (input.at(0)) {
      case 79: // Oo
      case 111:
        fromUser.flag = inputFlag::OPENINPUT;
        break;
      case 80: // Pp
      case 112:
        fromUser.flag = inputFlag::NOTESAFEINPUT;
        break;
      case 66: // Bb
      case 98:;
        fromUser.flag = inputFlag::NOTEBOMBINPUT;
        break;
      case 82: // Rr
      case 114:
        fromUser.flag = inputFlag::NOTERESETINPUT;
        break;
      case 88: // Xx
      case 120:
        fromUser.flag = inputFlag::EXIT;
        break;
      default:;
      }
      break;
    }
  }
  return fromUser;
}

int getInputFromMenu() {
  while (true) {
    cout << "\n Geben Sie die Nummer der Wahl ein: ";
    string input;
    getline(cin, input);
    if ((input.length() > 1) || (int(input[0]) > 53) || (int(input[0]) < 49)) {
      cout << "            " << input << endl;
      cout << "            Invalid Input";
    } else {
      return int(input[0]) - 48;
    }
  }
}

int getInputAfterSpiel() {
  regex re("[123]");
  string input;
  while (true) {
    cout << "       Geben Sie die Nummer der Wahl ein: ";
    getline(cin, input);
    if (regex_match(input, re))
      return int(input.at(0)) - 48;
    else {
      cout << endl << "       Invalid Input " << endl;
      continue;
    }
  }
};

int getInputFromHighScore() {
  regex re("[123]");
  string input;
  while (true) {
    cout << "       Geben Sie die Nummer der Wahl ein: ";
    getline(cin, input);
    if (regex_match(input, re))
      return int(input.at(0)) - 48;
    else {
      cout << endl << "       Invalid Input " << endl;
      continue;
    }
  }
};

string getUserName() {
  cout << "Geben Sie Ihren Namen, um Score zu speichern: ";
  string name;
  getline(cin, name);
  return name;
}

int getInputLevel() {
  while (true) {
    cout << "\n Geben Sie die Nummer der Wahl ein: ";
    string input;
    getline(cin, input);
    if ((input.length() > 1) || (int(input[0]) > 51) || (int(input[0]) < 49)) {
      cout << "            Invalid Input";
    } else {
      return int(input[0]) - 49; // 0 für LOW, 1, 2 so on
    }
  }
}

int getInputFromMenus(int max) {
  while (true) {
    cout << "\n Geben Sie die Nummer der Wahl ein: ";
    string input;
    getline(cin, input);
    if ((input.length() > 1) || (int(input[0]) > (48 + max)) ||
        (int(input[0]) < 49)) {
      cout << "            " << input << std::endl;
      cout << "            Invalid Input";
    } else {
      return int(input[0]) - 48; // 1-kurs 2-studenten 3-exit
    }
  }
};
