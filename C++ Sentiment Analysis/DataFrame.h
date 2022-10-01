//
// Created by Reece Iriye on 9/14/22.
//

#ifndef ASSIGNMENT2_SENTIMENT_DATAFRAME_H
#define ASSIGNMENT2_SENTIMENT_DATAFRAME_H

#include "DSVector.h"
#include "DSString.h"

class DataFrame : public DSVector<DSVector<DSString>> {
public:
    DataFrame() = default;
    DataFrame(const DataFrame &) = default;
    DataFrame(DataFrame &&rhs) = default;
    ~DataFrame() = default;

    // these are already provided by DSVector (default in C++11)
    DataFrame &operator=(const DataFrame &) = default;
    DataFrame &operator=(DataFrame &&) = default;

};


#endif //ASSIGNMENT2_SENTIMENT_DATAFRAME_H
