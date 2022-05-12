#ifndef NHF2_PATTERN_H
#define NHF2_PATTERN_H

#include "characteroccurrence.h"
#include <list>
#include <set>
#include <algorithm>

class Pattern final {
    std::list<CharacterOccurrence> letters;
    const size_t length;

public:

    explicit Pattern(size_t length) : length(length) {}

    bool operator==(const Pattern &other) const;

    bool operator!=(const Pattern &other) const;

    Pattern &operator+=(const CharacterOccurrence &occurrence);

    bool matches(const std::string &string) const;

    friend std::ostream &operator<<(std::ostream &, const Pattern &);

    bool contains(char c) const;

    bool isComplete() const;
};


#endif //NHF2_PATTERN_H