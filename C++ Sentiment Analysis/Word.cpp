//
// Created by Reece Iriye on 9/20/22.
//

#include "Word.h"

Word::Word(DSString theWord, int positive, int negative) {
    this->theWord = theWord;
    this->positive = positive;
    this->negative = negative;
}


const DSString &Word::getTheWord() const {
    return theWord;
}

// Getters and Setters

void Word::setTheWord(const DSString &theWord) {
    Word::theWord = theWord;
}

int Word::getPositive() const {
    return positive;
}

void Word::setPositive(int positive) {
    Word::positive = positive;
}

int Word::getNegative() const {
    return negative;
}

void Word::setNegative(int negative) {
    Word::negative = negative;
}
