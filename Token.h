#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <vector>
#include "Tokens.h"

using namespace std;

class Token {
private:
    TOKENS type = EOF_TYPE;
    string value = "";
    int line = 0;
public:
    Token() {};

    Token(TOKENS type, string value, int line) {
        this->type = type;
        this->value = value;
        this->line = line;
    }

    TOKENS getType() {
        return type;
    }

    string getValue() {
        return value;
    }

    int getLine() {
        return line;
    }

    string toString() {
        return "(" + TOKEN_STRINGS[type] + ",\"" + value + "\"," + to_string(line) + ")";
    }

    vector<string> TOKEN_STRINGS = {
            "COMMA",
            "PERIOD",
            "Q_MARK",
            "LEFT_PAREN",
            "RIGHT_PAREN",
            "COLON",
            "COLON_DASH",
            "MULTIPLY",
            "ADD",
            "SCHEMES",
            "FACTS",
            "RULES",
            "QUERIES",
            "ID",
            "STRING",
            "COMMENT",
            "UNDEFINED",
            "EOF"
    };
};

#endif