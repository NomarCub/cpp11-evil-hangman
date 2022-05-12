#include "hangman.h"

#include <map>
#include <iostream>
#include <algorithm>
#include <fstream>

void Hangman::startGame(size_t wordlength) {
    if (wordlength < 2)
        throw std::invalid_argument{"Minimum word length is 2"};

    inGameWords.clear();
    for (auto s :wordlist) {
        if (s.size() == wordlength)
            inGameWords.push_back(std::move(s));
    }

    if (inGameWords.empty())
        throw std::out_of_range{"No words exist with the specified wordcount"};

    mistakes = 0;
    pattern.emplace(wordlength);
}

void Hangman::loadWords(const std::string &path) {
    wordlist.clear();
    std::ifstream from(path);
    std::string line;
    while (std::getline(from, line)) {
        wordlist.insert(std::move(line));
    }
}

void Hangman::play(size_t wordLength) {
    startGame(wordLength);
    while (!(*pattern).isComplete() && mistakes <= difficulty) {
        std::cout << std::endl;
        displayState();
        char c;

        //TODO exit character
        do {
            std::cout << "Guess a letter: ";
        } while (!(std::cin >> c) || !std::isalpha(c) || charactersTried.count(c) == 1);

        charactersTried.insert(c);


        std::map<CharacterOccurrence, size_t> patterns;
        for (const std::string &s : inGameWords) {
            patterns[CharacterOccurrence(s, c)]++;
        }

        CharacterOccurrence co = std::max_element(patterns.begin(), patterns.end(),
                                                  [](const std::pair<CharacterOccurrence, size_t> &p1,
                                                     const std::pair<CharacterOccurrence, size_t> &p2) {
                                                      return p1.second < p2.second;
                                                  })->first;

        if (co.positions().empty())
            mistakes++;
        *pattern += co;

        inGameWords.erase(
                std::remove_if(inGameWords.begin(), inGameWords.end(), [&co](const std::string &s) {
                    return !co.matches(s);
                }), inGameWords.end());
    }

    std::cout << "\nCongratulations\nThe word was " << inGameWords[0] << ".\n";
}

void Hangman::displayState() {
    std::cout << *pattern << std::endl;
    std::cout << "Mistakes: " << mistakes << std::endl;
    std::for_each(charactersTried.begin(), charactersTried.end(), [](char c) { std::cout << c << " "; });
    std::cout << std::endl;
}