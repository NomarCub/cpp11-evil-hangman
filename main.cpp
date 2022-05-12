#include "hangman.h"
#include <iostream>

int main() {
    Hangman hangman;
    hangman.loadWords("dictionary.txt");

    size_t length = 1;
    do {
        std::cout << "Choose a length for guessing a word.\nWrite 0 if you want to quit.\n";
        try {
            std::cin >> length;
            hangman.play(length);
            std::cout << std::endl;
        } catch (...) {
            if (length != 0)
                std::cout << "Invalid number.\n\n";
        }
    } while (length != 0);
}