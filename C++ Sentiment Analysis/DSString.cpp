/*
 * Ideas for implementing additional functions:
 * https://www.analyticsvidhya.com/blog/2021/07/10-useful-python-string-functions-every-data-scientist-should-know-about/
 */

#include "DSString.h"



DSString::DSString(const char *x) {
    size_t size = strlen(x);
    resize(size);

    for (size_t i = 0; i < size; ++i) {
        (*this)[i] = x[i];
    }
}

// When creating DSString and assigning it to char array, this operator converts it to a C-String
DSString &DSString::operator=(const char *rhs) {
    size_t size = strlen(rhs);
    resize(size);

    for (size_t i = 0; i < size; ++i)
    {
        (*this)[i] = rhs[i];
    }

    return *this;
}

// Plus operator acts as a concatenater, adding values to a string
DSString DSString::operator+(const DSString &rhs) const {

    size_t newSize = this->size() + rhs.size();
    size_t newCapacity = this->capacity() + rhs.capacity();

    DSString tmp;
    tmp.reserve(newCapacity);
    tmp.resize(newSize);

    for (size_t i = 0; i < newCapacity; ++i) {
        if (i < size())
            tmp[i] = (*this)[i];
        else
            tmp[i] = rhs[i-size()];
    }

    return tmp;
}

// Overload plus operator with a char parameter.
DSString DSString::operator+(const char rhs) const {

    size_t newCapacity = this->capacity() + 1;
    size_t newSize = this->size() + 1;

    DSString tmp;
    tmp.resize(newCapacity);
    for (size_t i = 0; i < newCapacity; ++i) {
        if (i < size())
            tmp[i] = (*this)[i];
        else
            tmp[i] = rhs;
    }

    return tmp;
}


/**
 * Standard relational operators.
 **/

bool DSString::operator==(const DSString &rhs) const {
    if (size() != rhs.size())
        return false;

    for (size_t i = 0; i < size(); ++i)
        if ((*this)[i] != rhs[i])
            return false;

    return true;
}

bool DSString::operator!=(const DSString &rhs) const {
    return !operator==(rhs);
}

bool DSString::operator<(const DSString &rhs) const {
    size_t compSize = min(size(), rhs.size());

    // Double check this, this feels wrong
    for (size_t i = 0; i < compSize; ++i) {
        if ((*this)[i] < rhs[i])
            return true;
        if ((*this)[i] > rhs[i])
            return false;
    }

    // all were the same so far. We define the shorter string as <
    if (size() < rhs.size())
        return true;

    return false;
}

bool DSString::operator>(const DSString &rhs) const {
    // Utilize logical operators based on the two previous relational operators to implement operator>
    if ((!operator<(rhs)) && (!operator==(rhs))) {
        return true;
    }
    else {
        return false;
    }
}

bool DSString::operator>=(const DSString &rhs) const {
    // Utilize logical operators based on the two previous relational operators to implement operator>
    if ((!operator<(rhs)) && (operator==(rhs))) {
        return true;
    }
    else {
        return false;
    }
}

bool DSString::operator<=(const DSString &rhs) const {
    // Utilize logical operators based on the two previous relational operators to implement operator>
    if (!operator>(rhs)) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * The substring method returns a string object that contains a
 * sequence of characters from this string object.
 *
 * param start - the index of where to start
 * param numChars - the number (count) of characters to copy into
 *    the substring
 * @return a DSString object containing the requested substring
 **/
DSString DSString::substring(size_t start, size_t numChars) const {
    if (start + numChars > size())
        throw std::runtime_error("Out of bounds! Substring entered is larger than ");

    DSString tmp;
    tmp.resize(numChars);

    for (size_t i = 0; i < numChars; ++i) {
        tmp[i] = (*this)[start + i];
    }
    return tmp;
}

/**
 * the c_str function returns a null-terminated c-string holding the
 * contents of this object.
 **/
const char* DSString::c_str() const {
    // I would need to keep an extra `\0` to make this work.
    char* tmp = new char[this->size()];

    for (size_t i = 0; i < size(); ++i) {
        tmp[i] = (*this)[i];
    }

    tmp[size()] = '\0';


    return tmp;
}

/**
 * Overloaded stream insertion operator to print the contents of this
 * string to the output stream in the first argument.
 **/
std::ostream &operator<<(std::ostream &out, const DSString &x) {
    for (const auto &c : x)
        out << c;

    return out;
}

/*
 * The to_lower() function makes every upper-case character lower-case
 * from the DSString parameter.
 *
 * param - the DSString where all upper-case letters will transform
 * and become lower-case
 * @return a fully lower-case DSString
 */

DSString DSString::to_lower() {
    for (size_t i = 0; i < size(); ++i) {
        if (((*this)[i] >= 'A') && ((*this)[i] <= 'Z'))
            // ASCII number for 'a' is 97 and for 'A' is 65
            // Therefore, adding 32 to any lowercase letter will make an upper-case letter lower-case
            (*this)[i] = (*this)[i] + 32;
        else
            // If not within that range, set equal.
            (*this)[i] = (*this)[i];
    }

    return *this;
}

/*
 * The to_upper() function makes every lower-case character upper-case
 * from the DSString parameter.
 *
 * @return a fully lower-case DSString
 */

DSString DSString::to_upper() {
    for (size_t i = 0; i < size(); ++i) {
        if (((*this)[i] >= 'a') && ((*this)[i] <= 'z'))
            // ASCII number for 'a' is 97 and for 'A' is 65
            // Therefore, subtracting 32 from any lowercase letter will make a lower-case letter upper-case
            (*this)[i] = (*this)[i] - 32;
        else
            // If not within that range, set equal.
            (*this)[i] = (*this)[i];
    }

    return *this;
}


/*
 * The split() function evaluates DSString, divides it into multiple
 * elements based off a user-specified delimiter that is automatically
 * set to ' ' if not changed, then inputs every single one of these
 * elements into a DSVector.
 *
 *
 * param dlm - a character automatically set to ' ' but can be changed
 *      to any other user-specified char, dlm is a separator that is how
 *      the program stops reading in a DSString and starts another
 *
 * @return a DSVector that includes all separated parts of the original
 *      DSString
 */
DSVector<DSString> DSString::split(char dlm) const {
    DSVector<DSString> tmpVector;

    // Start off this function by creating vectorIndex variable then
    DSString tmpString = "";
    size_t dlmCount = 0;

    for (size_t i = 0; i < this->size(); ++i) {
        if ((*this)[i] != dlm) {
            tmpString = tmpString + (*this)[i];
        }
        else {
            dlmCount++; // Add 1 every time program encounters a dlm so this will be subtracted later
            tmpVector.push_back(tmpString); // Push back DSVector with completed tmpString
            tmpString = DSString(""); // Restart tmpString
        }
    }

    return tmpVector;
}

/*  OVERLOADED split() FUNCTION!!!!
  * The split() function evaluates DSString, divides it into multiple
  * elements based off a user-specified delimiter that is automatically
  * set to ' ' if not changed, then inputs every single one of these
  * elements into a DSVector.
  *
  *
  * param dlm - a character automatically set to ' ' but can be changed
  *      to any other user-specified char, dlm is a separator that is how
  *      the program stops reading in a DSString and starts another
  * param limit - stops iterating through the DSString once limit has been
  *      exceeded
  *
  * @return a DSVector that includes all separated parts of the original
  *      DSString
  */

DSVector<DSString> DSString::split(char dlm, size_t limit) const {
    DSVector<DSString> tmpVector;

    // Start off this function by creating vectorIndex variable then
    DSString tmpString = "";
    size_t dlmCount = 0;

    size_t colNum = 1;

    for (size_t i = 0; i < this->size(); ++i) {
        // If statement used for case where column limit has been reached
        if (colNum >= limit) {
            for (i = i; i < this->size(); ++i) {
                tmpString = tmpString + (*this)[i];
            }
            tmpVector.push_back(tmpString);
            break;
        }

        // Normal iteration in search of dlm char
        if ((*this)[i] != dlm) {
            tmpString = tmpString + (*this)[i];
        }
        else {
            dlmCount++; // Add 1 every time program encounters a dlm so this will be subtracted later
            tmpVector.push_back(tmpString); // Push back DSVector with completed tmpString
            tmpString = DSString(""); // Restart tmpString
            colNum++;
        }
    }

    return tmpVector;
}


/*
 * The remove_punctuation() function gets rid of all '!', '.', and '?'
 * chars in a DSString and also ',' depending on whether the user specifies
 * it.
 *
 *
 * param remove_commas - a bool that evaluates whether commas will
 *      be removed. DEFAULT: false
 *
 * @return a DSString with these chars eliminated.
 */
DSString DSString::remove_punctuation(bool remove_commas) {
    switch (remove_commas) {
        // User indicates to remove commas
        case true:
            for (int i = 0; i < this->size(); ++i) {
                // Logic: (~(p/\q) /\ ~(r/\s)) /\ t
                if (!((*this)[i] >= 'A' && (*this)[i] <= 'Z') &&
                    !((*this)[i] >= 'a' && (*this)[i] <= 'z') &&
                    ((*this)[i] != ' '))
                {
                    (*this).remove(i);
                    i--; // This line is for the case when two punctuation char's are next to each other
                }
            } // end for-loop
            break;
        // User indicates to NOT remove commas (DEFAULT: false)
        case false:
            for (int i = 0; i < this->size(); ++i) {
                // Logic: (~(p/\q) /\ ~(r/\s)) /\ t /\ u
                if (!((*this)[i] >= 'A' && (*this)[i] <= 'Z') &&
                    !((*this)[i] >= 'a' && (*this)[i] <= 'z') &&
                    ((*this)[i] != ' ') && ((*this)[i] != ','))
                {
                    (*this).remove(i);
                    i--; // This line is for the case when two punctuation char's are next to each other
                }
            } // end for-loop
            break;
    }

    return *this;
}

/*
 * The remove_word_after_char() function gets rid of all characters
 * after a specified char, including that char.
 *
 *
 * param indicator - the character that will cause all other char's
 *      to die. DEFAULT: '@'
 *
 * @return a DSString without the characters after it.
 */
DSString DSString::remove_word_after_char(char indicator) {
    for (int i = 0; i < this->size(); ++i)
        if ((*this)[i] == indicator)
            resize(i);

    return *this;
}

/*
 * The stemming() function gets rid of characters like 'ing', 's', and
 * repeated characters at the end of every individual DSString.
 *
 * NOTE: This function will only work when it's applied to regular strings
 *      without space chars.
 *
 * INSPIRATION: https://towardsdatascience.com/stemming-corpus-with-nltk-7a6a6d02d3e5
 *
 * @RETURN a stemmed DSString.
 */

DSString DSString::stemming() {

    // Remove 's' or 'es' at end of word
    if (size() > 2) {
        if ((*this)[-1] == 's') {
            if((*this)[-2] == 'e') {
                pop_back();
                pop_back();
            }
            else {
                pop_back();
            }
        }
    }

    // Remove 'ed' at the end of word
    if (size() > 5) {
        if ((*this)[-4] == 'a'
        &&  (*this)[-3] == 't'
        &&  (*this)[-2] == 'e'
        &&  (*this)[-1] == 'd') {
            pop_back();
            pop_back();
            pop_back();
            pop_back();
        }

        else if ((*this)[-2] == 'e' && (*this)[-1] == 'd') {
            pop_back();
        }
    }

    if(size() > 4) {
        if((*this)[-2] == 'e'
        && (*this)[-1] == 'r') {
            pop_back();
            pop_back();
        }
    }


    // Remove 'ly' at the end of word, or 'ally' if that's at the end
    if(size() > 5) {
        if ((*this)[-4] == 'a'
        &&  (*this)[-3] == 'l'
        &&  (*this)[-2] == 'l'
        &&  (*this)[-1] == 'y'){
            pop_back();
            pop_back();
            pop_back();
            pop_back();
        }
        else if((*this)[-2] == 'l' && (*this)[-1] == 'y') {
            pop_back();
            pop_back();
        }
        else if((*this)[-1] == 'y') {
            pop_back();
        }
    }

    // Remove 'ing' at the end of word
    if (size() > 3) {
        if((*this)[-3] == 'i'
        && (*this)[-2] == 'n'
        && (*this)[-1] == 'g') {
            pop_back();
            pop_back();
            pop_back();
        }
    }

    if(size() > 5) {
        if((*this)[-3] == 'o'
        && (*this)[-2] == 'u'
        && (*this)[-1] == 's') {
            pop_back();
            pop_back();
            pop_back();
        }
    }

    if (size() > 5) {
        if((*this)[-4] == 'm'
        && (*this)[-3] == 'e'
        && (*this)[-2] == 'n'
        && (*this)[-1] == 't') {
            pop_back();
            pop_back();
            pop_back();
            pop_back();
        }

        if((*this)[-2] == 'a'
        && (*this)[-1] == 'l') {
            pop_back();
            pop_back();
        }

    }


    return *this;
}


/*
 * The remove_repeat_chars() function deletes a character if it happens to be the exact same as the 
 * previous char in a DSString. 
 *
 * @RETURN a DSString that has no equal characters right next to each other. 
 */
DSString DSString::remove_repeat_chars() {
    int totalIterations = size() - 1;
    for (int i = 0; i < totalIterations; ++i) {
        if ((*this)[i] == (*this)[i+1]) {
            this->remove(i);
            i--;
            totalIterations--;
        }
    }

    return *this;
}
