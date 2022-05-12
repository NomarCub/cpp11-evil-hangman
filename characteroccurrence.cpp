#include "characteroccurrence.h"

#include <algorithm>

bool CharacterOccurrence::operator==(const CharacterOccurrence &other) const {
    return length == other.length && character == other.character
           && positions_ == other.positions_;
}

bool CharacterOccurrence::operator!=(const CharacterOccurrence &other) const {
    return !(*this == other);
}

CharacterOccurrence::CharacterOccurrence(std::string_view string, char c)
        : length(string.length()), character(std::toupper(c)) {
    for (size_t i = 0; i < length; i++) {
        if (std::toupper(string[i]) == character) {
            positions_.insert(i);
        }
    }
}

bool CharacterOccurrence::matches(const std::string &string) const {
    if (string.length() != length) return false;
    for (size_t i = 0; i < length; i++) {
        if (toupper(string[i]) == character && positions_.count(i) == 0)
            return false;
    }
    return std::all_of(positions_.begin(), positions_.end(), [&string, this](size_t i) {
        return std::toupper(string[i]) == character;
    });
}

bool CharacterOccurrence::operator<(const CharacterOccurrence &other) const {
    return this->character < other.character || other.positions_ < this->positions_;
}

std::string CharacterOccurrence::print() const {
    std::string temp(length, '_');

    std::for_each(positions_.begin(), positions_.end(), [&temp, this](size_t s) {
        temp[s] = character;
    });
    return temp;
}
