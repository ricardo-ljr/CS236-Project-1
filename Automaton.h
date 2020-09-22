

#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include <string>

#include "Tokens.h"

using namespace std;

class Automaton {
public:
    Automaton() {};

    virtual ~Automaton() = default;

    virtual int Read(string &input) = 0;

    TOKENS type = UNDEFINED;

    string lastRead();

protected:
    size_t readIndex = 0;

    char currCharOf(string &input) {
        return input[readIndex];
    }

    char nextCharOf(string &input) {
        return input[readIndex + 1];
    }

    void advanceChar() {
        readIndex++;
    }
};

#endif //AUTOMATON_H
