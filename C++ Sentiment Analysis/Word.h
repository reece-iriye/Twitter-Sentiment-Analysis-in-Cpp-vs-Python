//
// Created by Reece Iriye on 9/20/22.
//

#ifndef ASSIGNMENT2_SENTIMENT_WORD_H
#define ASSIGNMENT2_SENTIMENT_WORD_H

#include "DSString.h"
#include "DSVector.h"

class Word {
private:
    DSString theWord;
    int positive;
    int negative;
public:
    Word() = default;
    Word(const Word &) = default;
    Word(Word &&rhs) = default;
    ~Word() = default;
    Word(DSString theWord, int positive, int negative);

    // these are already provided by DSVector (default in C++11)
    Word &operator=(const Word &) = default;
    Word &operator=(Word &&) = default;

    // Getters and Setters
    const DSString &getTheWord() const;
    void setTheWord(const DSString &theWord);
    int getPositive() const;
    void setPositive(int positive);
    int getNegative() const;
    void setNegative(int negative);
};


#endif //ASSIGNMENT2_SENTIMENT_WORD_H
