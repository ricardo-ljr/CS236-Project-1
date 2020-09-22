

#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>

#include "Token.h"
#include "Automaton.h"
#include "MatcherAutomaton.h"

using namespace std;


class Lexer {
public:
    Lexer(string &input) {
        this->input = input;
    }

    ~Lexer() {
        for (size_t i = 0; i < machines.size(); i++) {
            delete machines[i];
        }
    }

    void tokenizeInput() {
        lineNumber = 1;
        tokens.clear();

        do {
            tokens.push_back(findNextToken());
        } while (tokens.back().getType() != EOF_TYPE);
        printTokens();
    }

    vector<Token> getTokenList() {
        return tokens;
    }

    void printTokens() {
        for (size_t i = 0; i < tokens.size(); i++) {
            cout << tokens[i].toString() << endl;
        }
        cout << "Total Tokens = " << tokens.size() << endl;
    }

    Token findNextToken();

private:
    string input;
    int lineNumber = 1;

    // FSA Machines for string recognition

    vector<Automaton *> machines = {
            new FSA_COMMA(),
            new FSA_PERIOD(),
            new FSA_Q_MARK(),
            new FSA_LEFT_PAREN(),
            new FSA_RIGHT_PAREN(),
            new FSA_COLON(),
            new FSA_MULTIPLY(),
            new FSA_ADD(),
            new FSA_COMMENT_LONG(),
            new FSA_COMMENT(),
            new FSA_STRING(),
            new FSA_SCHEMES(),
            new FSA_FACTS(),
            new FSA_RULES(),
            new FSA_QUERIES(),
            new FSA_ID(),
    };

    vector<Token> tokens;

    void checkWhiteSpace() {
        while (input.length() > 0 && isspace(input.front())) {
            if (input.front() == '\n') {
                lineNumber++;
            }
            input = input.substr(1);
        }
    }

};

/*********** FUNCTIONS OUTSIDE OF CLASS DECLARATION ***********/

Token Lexer::findNextToken() {
    int maxRead = 0;

    checkWhiteSpace();
    if (input.length() <= 0) return Token(EOF_TYPE, "", lineNumber);
    size_t maxMachine;
    for (size_t i = 0; i < machines.size(); i++) {
        int inputRead = machines[i]->Read(input);
        if (inputRead > maxRead) {
            maxRead = inputRead;
            maxMachine = i;
        }
    }
    Token token;
    if (maxRead > 0) token = Token(machines[maxMachine]->type, input.substr(0, maxRead), lineNumber);
    else {
        token = Token(UNDEFINED, input.substr(0, 1), lineNumber);
    }

    for (size_t c = 0; c < token.getValue().length(); c++) {
        if (input[c] == '\n') lineNumber++;
    }

    input = input.substr(token.getValue().length());

    return token;
}

#endif //LEXER_H
