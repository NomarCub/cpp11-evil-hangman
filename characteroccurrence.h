#ifndef NHF2_CHARACTEROCCURRENCE_H
#define NHF2_CHARACTEROCCURRENCE_H


#include <string_view>
#include <set>

class CharacterOccurrence final {
    std::set<int> positions_;
public:
    const size_t length;
    const char character;

    CharacterOccurrence(std::string_view string, char c);

    bool operator==(const CharacterOccurrence &other) const;

    bool operator!=(const CharacterOccurrence &other) const;

    const std::set<int> &positions() const { return positions_; }

    bool matches(const std::string &string) const;

    bool operator<(const CharacterOccurrence &other) const;

    std::string print() const;
};

#endif //NHF2_CHARACTEROCCURRENCE_H