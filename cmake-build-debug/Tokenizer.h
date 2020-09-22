

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cctype>
#include "../Token.h"

// NEEDS: isEOF? currChar, nextChar, lastChar, pushChar to vector, skipChar?, isEmpty?

class Tokenizer {
public:
    Tokenizer() {}

    Tokenizer(string &input) {
        this->input = input;
    }

    Token getNextToken() {
        tokenValue = "";
        return state_0();
    }

private:
    string input;
    string tokenValue = "";
    int lineCount = 1;
    int tokenLine = 1;
    char lastChar;
    bool emptyInput = true;

    bool isEOF() {
        if (input.size() == 0 || (isspace(currChar()) && input.size() == 1)) {
            return true;
        }
    }

    char currChar() {
        return input[0];
    }

    char nextChar() {
        return input[1];
    }


    void pushChar() {
        tokenValue += input[0];
        skipChar();
    }

    void skipChar() {
        if (currChar() == '\n') {
            lineCount++;
        }
        lastChar = currChar();
        input = input.substr(1, input.size() - 1);
    }

    Token foundTokenType(TOKENS type, bool shouldPush = true) {
        if (shouldPush) {
            pushChar();
            return Token(type, tokenValue, tokenLine);
        }
    }

    // Tokens

    Token state_0();

    Token try_COMMA();

    Token try_PERIOD();

    Token try_Q_MARK();

    Token try_LEFT_PAREN();

    Token try_RIGHT_PAREN();

    Token try_COLON();

    Token try_MULTIPLY();

    Token try_ADD();

    Token try_STRING();

    Token try_COMMENT();

    Token try_SCHEMES();

    Token try_FACTS();

    Token try_QUERIES();

    Token try_RULES();

    Token try_ID(); // Identifier

};


#endif //TOKENIZER_H
