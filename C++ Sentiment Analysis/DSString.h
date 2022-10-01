#ifndef DSSTRING_H
#define DSSTRING_H

#include "DSVector.h"
#include <cstring>

#include <iostream>

// Also adding functionality to DSVector.h

class DSString : public DSVector<char> {
private:
    // ALL PRIVATE VARIABLES INHERITED FROM DSVector
public:
    /**
     * Constructors and destructor call the base class
     *
     * Make sure you use proper memory management.
     **/

    // we get those from DSVector and can say default in C++11
    DSString() = default;
    DSString(const DSString &) = default;
    DSString(DSString &&rhs) = default;
    ~DSString() = default;

    // we need to implement this.
    DSString(const char *);

    /**
     * Overloaded Assignment Operators
     * See: https://en.cppreference.com/w/cpp/language/operators
     */

    // these are already provided by DSVector (default in C++11)
    DSString &operator=(const DSString &) = default;
    DSString &operator=(DSString &&) = default;

    // Added this on our own.
    DSString &operator=(const char *);

    /**
     * Overloaded non-modifying string concat
     */
    DSString operator+(const DSString &) const;
    DSString operator+(const char) const;
    DSString operator+=(const DSString &); // NOT WORKING YET
    DSString operator+=(const char); // NOT WORKING YET

    /**
     * Standard relational operators.  Feel free to add additional.
     **/
    bool operator==(const DSString &) const;
    bool operator!=(const DSString &rhs) const;
    bool operator<(const DSString &) const; // total order of strings to sort from smallest to largest
    bool operator>(const DSString &) const; // implement logic based on logical operator responses of == and < operators
    bool operator>=(const DSString &) const;
    bool operator<=(const DSString &) const;


    /**
     * The substring method returns a string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     * @return a DSString object containing the requested substring
     **/

    DSString substring(size_t start, size_t numChars) const; // generate 

    /**
     * the c_str function returns a pointer a null-terminated c-string holding the
     * contents of this object. It would be smart to always have an extra `\0`
     * at the end of the string in DSString so you can just return a pointer to the
     * objects. You can make objects protected in DSVector, so
     * DSString can see it or you can realize that an iterator is actually also a
     * pointer.
     **/
    const char* c_str() const;

    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument. `DSString&`
     * could be const, but then we would have to implement a const interator in
     * DSVector.
     **/
    friend std::ostream &operator<<(std::ostream &, const DSString &);

    // ADDITIONAL HELPER FUNCTIONS:

    /*
     * The to_lower() function makes every upper-case character lower-case
     * from the DSString object that this function is attached to.
     *
     *
     * @return a fully lower-case DSString
     */
    DSString to_lower();

    /*
     * The to_upper() function makes every lower-case character upper-case
     * from the DSString object that this function is attached to.
     *
     *
     * @return a fully upper-case DSString
     */
    DSString to_upper();

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
    DSVector<DSString> split(char dlm = ' ') const;


    /*  OVERLOADED split() FUNCTION!!!!
      * The split() function evaluates DSString, divides it into multiple
      * elements based off a user-specified delimiter, then inputs every single
      * one of these elements into a DSVector.
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
    DSVector<DSString> split(char dlm, size_t limit) const;

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
    DSString remove_punctuation(bool remove_commas = true);


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
    DSString remove_word_after_char(char indicator = '@');

    /*
     * The stemming() function chops off additional parts of a word (e.g.
     * 's', 'es', 'ing') to form the original word. The method is not perfect
     * by any means, but its attention in ensuring that
     */
    DSString stemming();


    DSString remove_repeat_chars();


};

#endif