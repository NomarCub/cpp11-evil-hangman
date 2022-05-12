#include "pattern.h"

#include <ostream>
#include <algorithm>

bool Pattern::operator==(const Pattern &other) const {
    return length == other.length && letters == other.letters;
}

bool Pattern::operator!=(const Pattern &other) const {
    return !(*this == other);
}

Pattern &Pattern::operator+=(const CharacterOccurrence &occurrence) {
    if (length != occurrence.length)
        throw std::invalid_argument{"Non matching pattern length"};

    if (std::any_of(letters.begin(), letters.end(), [&occurrence](const CharacterOccurrence &co) {
        return co.character == occurrence.character;
    }))
        throw std::invalid_argument{"Character already present in pattern"};

    if (std::any_of(letters.begin(), letters.end(), [&occurrence](const CharacterOccurrence &co) {
        return std::any_of(occurrence.positions().begin(), occurrence.positions().end(),
                           [&occurrence, &co](size_t pos) {
                               return co.positions().count(pos) != 0;
                           });
    }))
        throw std::invalid_argument{"Character occurrence overlaps with existing patten"};

    letters.push_back(occurrence);
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Pattern &pattern) {
    std::string temp(pattern.length, '_');

    std::for_each(pattern.letters.begin(), pattern.letters.end(), [&temp](const CharacterOccurrence &co) {
        std::for_each(co.positions().begin(), co.positions().end(), [&temp, &co](size_t i) {
            temp[i] = co.character;
        });
    });
    os << temp;
    return os;
}

bool Pattern::contains(char c) const {
    return std::any_of(letters.begin(), letters.end(), [c](const CharacterOccurrence &co) {
        return co.character == c;
    });
}

bool Pattern::matches(const std::string &string) const {
    return string.length() == length &&
           std::all_of(letters.begin(), letters.end(), [&string, this](const CharacterOccurrence &co) {
               return co.matches(string);
           });
}

bool Pattern::isComplete() const {
    size_t i = 0;
    std::for_each(letters.begin(), letters.end(), [&i](const CharacterOccurrence &co) {
        i += co.positions().size();
    });
    return i == length;
}
