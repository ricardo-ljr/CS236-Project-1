

#ifndef MATCHERAUTOMATON_H
#define MATCHERAUTOMATON_H

#include "Automaton.h"

// Simple classes for collections of FSA

class FSA_COMMA : public virtual Automaton {
public:
    FSA_COMMA() { type = COMMA; };

    int Read(string &input) {
        readIndex = 0;
        if (currCharOf(input) == ',') {
            advanceChar();
        }
        return readIndex;
    }
};

class FSA_PERIOD : public virtual Automaton {
public:
    FSA_PERIOD() { type = PERIOD; };

    int Read(string &input) {
        readIndex = 0;
        if (currCharOf(input) == '.') {
            advanceChar();
        }
        return readIndex;
    }
};

class FSA_Q_MARK : public virtual Automaton {
public:
    FSA_Q_MARK() { type = Q_MARK; };

    int Read(string &input) {
        readIndex = 0;
        if (currCharOf(input) == '?') {
            advanceChar();
        }
        return readIndex;
    }
};

class FSA_MULTIPLY : public virtual Automaton {
public:
    FSA_MULTIPLY() { type = MULTIPLY; };

    int Read(string &input) {
        readIndex = 0;
        if (currCharOf(input) == '*') {
            advanceChar();
        }
        return readIndex;
    }
};

class FSA_ADD : public virtual Automaton {
public:
    FSA_ADD() { type = ADD; };

    int Read(string &input) {
        readIndex = 0;
        if (currCharOf(input) == '+') {
            advanceChar();
        }
        return readIndex;
    }
};

class FSA_LEFT_PAREN : public virtual Automaton {
public:
    FSA_LEFT_PAREN() { type = LEFT_PAREN; };

    int Read(string &input) {
        readIndex = 0;
        if (currCharOf(input) == '(') {
            advanceChar();
        }
        return readIndex;
    }
};

class FSA_RIGHT_PAREN : public virtual Automaton {
public:
    FSA_RIGHT_PAREN() { type = RIGHT_PAREN; };

    int Read(string &input) {
        readIndex = 0;
        if (currCharOf(input) == ')') {
            advanceChar();
        }
        return readIndex;
    }
};

class FSA_COLON : public virtual Automaton {
public:
    FSA_COLON() { type = COLON; };

    int Read(string &input) {
        readIndex = 0;
        type = COLON;

        if (currCharOf(input) == ':') {
            advanceChar();
            if (currCharOf(input) == '-') {
                type = COLON_DASH;
                advanceChar();
            }
        }
        return readIndex;
    }
};


class FSA_COMMENT : public virtual Automaton {
public:
    FSA_COMMENT() { type = COMMENT; };

    int Read(string &input) {
        readIndex = 0;

        if (currCharOf(input) == '#' && nextCharOf(input) != '|') {
            while (readIndex < input.length()) {
                if (currCharOf(input) == '\n') break;
                else advanceChar();
            }
        }
        return readIndex;
    }
};

class FSA_COMMENT_LONG : public virtual Automaton {
public:
    FSA_COMMENT_LONG() { type = COMMENT; };

    int Read(string &input) {
        readIndex = 0;
        type = COMMENT;

        if (currCharOf(input) == '#') {
            advanceChar();
        } else return readIndex;

        if (currCharOf(input) == '|') {
            advanceChar();

            while (readIndex < input.length()) {
                if (currCharOf(input) == '|') {
                    advanceChar();
                    if (currCharOf(input) == '#') {
                        advanceChar();
                        return readIndex;
                    }
                } else advanceChar();
            }
            type = UNDEFINED;
        }
        return readIndex;
    }
};


class FSA_STRING : public virtual Automaton {
public:
    FSA_STRING() { type = STRING; };

    int Read(string &input) {
        readIndex = 0;
        type = STRING;

        if (currCharOf(input) == '\'') {

            while (readIndex < input.length()) {
                advanceChar();


                if (currCharOf(input) == '\'' && nextCharOf(input) == '\'') {
                    advanceChar();
                    continue;
                }

                if (currCharOf(input) == '\'' && nextCharOf(input) != '\'') {
                    advanceChar();
                    return readIndex;
                }
            }
        }
        type = UNDEFINED;
        return readIndex;
    }
};


class FSA_SCHEMES : public virtual Automaton {
public:
    FSA_SCHEMES() { type = SCHEMES; };

    int Read(string &input) {
        readIndex = 0;
        string token = "Schemes";

        while (readIndex < token.length()) {
            if (currCharOf(input) == currCharOf(token)) advanceChar();
            else return 0;
        }

        return readIndex;
    }
};

class FSA_FACTS : public virtual Automaton {
public:
    FSA_FACTS() { type = FACTS; };

    int Read(string &input) {
        readIndex = 0;
        string token = "Facts";

        while (readIndex < token.length()) {
            if (currCharOf(input) == currCharOf(token)) advanceChar();
            else return 0;
        }

        return readIndex;
    }
};

class FSA_RULES : public virtual Automaton {
public:
    FSA_RULES() { type = RULES; };

    int Read(string &input) {
        readIndex = 0;
        string token = "Rules";

        while (readIndex < token.length()) {
            if (currCharOf(input) == currCharOf(token)) advanceChar();
            else return 0;
        }

        return readIndex;
    }
};

class FSA_QUERIES : public virtual Automaton {
public:
    FSA_QUERIES() { type = QUERIES; };

    int Read(string &input) {
        readIndex = 0;
        string token = "Queries";

        while (readIndex < token.length()) {
            if (currCharOf(input) == currCharOf(token)) advanceChar();
            else return 0;
        }

        return readIndex;
    }
};


class FSA_ID : public virtual Automaton {
public:
    FSA_ID() { type = ID; };

    ~FSA_ID() {};

    int Read(string &input) {
        readIndex = 0;

        if (!isalpha(currCharOf(input))) return readIndex;

        while (readIndex < input.length()) {
            if (isspace(currCharOf(input))) return readIndex;

            switch (currCharOf(input)) {

                case ',':
                    return readIndex;
                case '.':
                    return readIndex;
                case '?':
                    return readIndex;
                case '(':
                    return readIndex;
                case ')':
                    return readIndex;
                case ':':
                    return readIndex;
                case '*':
                    return readIndex;
                case '+':
                    return readIndex;
                case '\'':
                    return readIndex;
                case '#':
                    return readIndex;
                default:
                    advanceChar();
            }
        }

        return readIndex;
    }
};

#endif //MATCHERAUTOMATON_H
