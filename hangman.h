#ifndef NHF2_HANGMAN_H
#define NHF2_HANGMAN_H

#include "pattern.h"
#include <vector>

class Hangman final{
    std::set<std::string> wordlist;
    std::vector<std::string> inGameWords;
    const size_t difficulty = 20;
    std::optional<Pattern> pattern;
    std::set<char> charactersTried;
    size_t mistakes = 0;

    void startGame(size_t wordlength);

public:

    void loadWords(const std::string &path);

    void play(size_t wordLength);

    void displayState();
};


#endif //NHF2_HANGMAN_H