#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

class Hangman {
private:
  std::string word;
  std::vector<char> guessedLetters;
  std::vector<char> falseLetters;
  int attempts;

public:
  Hangman(std::string word) : word(word), attempts(word.length()) {}

  bool guess(char letter) {

    if (word.find(letter) != std::string::npos) {
      if (std::find(guessedLetters.begin(), guessedLetters.end(), letter) !=
          guessedLetters.end()) {
        std::cout << std::endl
                  << "YOU ALREADY ENTERED THE CHARACTER: " << letter
                  << std::endl;
      } else {
        guessedLetters.push_back(letter);
      }
      return true;
    }
    if (!(std::find(falseLetters.begin(), falseLetters.end(), letter) !=
          falseLetters.end())) {
      falseLetters.push_back(letter);
    }
    attempts--;
    return false;
  }

  bool isGameOver() { return attempts <= 0 || isWordGuessed(); }

  bool isWordGuessed() {
    for (char c : word) {
      if (std::find(guessedLetters.begin(), guessedLetters.end(), c) ==
          guessedLetters.end()) {
        return false;
      }
    }
    return true;
  }

  void displayStatus() {
    std::cout << std::endl; // Added extra line break
    for (char c : word) {
      if (std::find(guessedLetters.begin(), guessedLetters.end(), c) !=
          guessedLetters.end()) {
        std::cout << c << ' ';
      } else {
        std::cout << "_ ";
      }
    }
    std::cout << "  //  ";
    for (char c : falseLetters) {
      std::cout << c;
    }
    std::cout << std::endl; // Added extra line break
    std::cout << "Attempts remaining: " << attempts << std::endl;
  }

  int GetGuesses() { return attempts; }

  std::string getWord() {
    if (word.length()) {
      return word;
    }
    return "";
  }
};

int main() {
  // ASCII representation of hangman
  std::string artman[] = {"  +---+\n"
                          "      |\n"
                          "      |\n"
                          "      |\n"
                          "      |\n"
                          "      |\n"
                          "=========",

                          "  +---+\n"
                          "  |   |\n"
                          "      |\n"
                          "      |\n"
                          "      |\n"
                          "      |\n"
                          "=========",

                          "  +---+\n"
                          "  |   |\n"
                          "  O   |\n"
                          "      |\n"
                          "      |\n"
                          "      |\n"
                          "=========",

                          "  +---+\n"
                          "  |   |\n"
                          "  O   |\n"
                          "  |   |\n"
                          "      |\n"
                          "      |\n"
                          "=========",

                          "  +---+\n"
                          "  |   |\n"
                          "  O   |\n"
                          " /|   |\n"
                          "      |\n"
                          "      |\n"
                          "=========",

                          "  +---+\n"
                          "  |   |\n"
                          "  O   |\n"
                          " /|\\  |\n"
                          "      |\n"
                          "      |\n"
                          "=========",

                          "  +---+\n"
                          "  |   |\n"
                          "  O   |\n"
                          " /|\\  |\n"
                          " /    |\n"
                          "      |\n"
                          "=========",

                          "  +---+  ,___________________________ \n"
                          "  |   |  | You are the worst lawyer. )\n"
                          "  O   | <___________________________/ \n"
                          " /|\\  |\n"
                          " / \\  |\n"
                          "      |\n"
                          "========="};
  Hangman game("hangman");
  char guess;

  while (!game.isGameOver()) {
    if (game.GetGuesses() <= 7) {
      std::cout << artman[7 - game.GetGuesses()] << std::endl;
    }
    game.displayStatus();
    std::cout << "Enter your guess: ";
    std::cin >> guess;
    std::cout << std::endl;
    game.guess(guess);

    std::cout << std::endl; // Added line break after each guess
  }

  if (game.isWordGuessed()) {
    std::cout << "The word was: " << game.getWord() << std::endl;
    std::cout << "Congratulations, you won!\n";
  } else {
    std::cout << "Game over, better luck next time!\n" << std::endl;
    std::cout << artman[7 - game.GetGuesses()] << std::endl;
  }

  return 0;
}
