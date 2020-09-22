#include "Tokenizer.h"

Token Tokenizer::state_0() {

    if (isEOF()) {
        if (input.size() > 0) skipChar();
        tokenLine = lineCount;
        return foundTokenType(EOF_TYPE, false);
    }

    if (isspace(currChar())) {
        skipChar();
        return state_0();
    }

    emptyInput = false;
    tokenLine = lineCount;

    switch (currChar()) {
        // Special Characters
        case ',':
            return try_COMMA();
        case '.':
            return try_PERIOD();
        case '?':
            return try_Q_MARK();
        case '(':
            return try_LEFT_PAREN();
        case ')':
            return try_RIGHT_PAREN();
        case ':':
            return try_COLON();
        case '*':
            return try_MULTIPLY();
        case '+':
            return try_ADD();
        case '\'':
            return try_STRING();
        case '#':
            return try_COMMENT();

        case 'S':
            return try_SCHEMES();
        case 'F':
            return try_FACTS();
        case 'Q':
            return try_QUERIES();
        case 'R':
            return try_RULES();

        default:
            if (isalpha(currChar())) return try_ID();
            else return foundTokenType(UNDEFINED);
            break;
    }
}


Token Tokenizer::try_COMMA() {
    return foundTokenType(COMMA);
}

Token Tokenizer::try_PERIOD() {
    return foundTokenType(PERIOD);
}

Token Tokenizer::try_Q_MARK() {
    return foundTokenType(Q_MARK);
}

Token Tokenizer::try_LEFT_PAREN() {
    return foundTokenType(LEFT_PAREN);
}

Token Tokenizer::try_RIGHT_PAREN() {
    return foundTokenType(RIGHT_PAREN);
}

Token Tokenizer::try_COLON() {
    if (nextChar() == '-') {
        pushChar();
        return foundTokenType(COLON_DASH);
    } else return foundTokenType(COLON);
}

Token Tokenizer::try_MULTIPLY() {
    return foundTokenType(MULTIPLY);
}

Token Tokenizer::try_ADD() {
    return foundTokenType(ADD);
}

Token Tokenizer::try_STRING() {
    pushChar();


    if (currChar() == '\'' && nextChar() == '\'') {
        pushChar();
        return try_STRING();
    }

    if (currChar() == '\'' && nextChar() != '\'') return foundTokenType(STRING);
    else if (isEOF()) return foundTokenType(UNDEFINED, (currChar() == '\n'));
    else return try_STRING();
}

Token Tokenizer::try_COMMENT() {
    bool commentEnd = false;

    // MultiLine Comment
    if (nextChar() == '|') {
        pushChar(); // Push #

        do {
            pushChar();
            if ((currChar() == '|' && nextChar() == '#') || isEOF()) commentEnd = true;
        } while (!commentEnd);

        if (currChar() == '|') {
            pushChar(); // Push |
            return foundTokenType(COMMENT);
        } else return foundTokenType(UNDEFINED, (currChar() == '\n'));
    } else {
        do {
            pushChar();
            if (nextChar() == '\n' || isEOF()) commentEnd = true;
        } while (!commentEnd);

        if (nextChar() == '\n') {
            pushChar(); // Push last char of comment before \n
            return foundTokenType(COMMENT, false);
        } else return foundTokenType(UNDEFINED, (currChar() == '\n'));
    }

}




// KEYWORDS

Token Tokenizer::try_SCHEMES() {
    pushChar();

    if (currChar() == 'c') pushChar();
    else return try_ID();

    if (currChar() == 'h') pushChar();
    else return try_ID();

    if (currChar() == 'e') pushChar();
    else return try_ID();

    if (currChar() == 'm') pushChar();
    else return try_ID();

    if (currChar() == 'e') pushChar();
    else return try_ID();

    if (currChar() == 's' && (nextChar() == ':' || isspace(nextChar()))) return foundTokenType(SCHEMES);
    else return try_ID();
}

Token Tokenizer::try_FACTS() {
    pushChar();

    if (currChar() == 'a') pushChar();
    else return try_ID();

    if (currChar() == 'c') pushChar();
    else return try_ID();

    if (currChar() == 't') pushChar();
    else return try_ID();

    if (currChar() == 's' && (nextChar() == ':' || isspace(nextChar()))) return foundTokenType(FACTS);
    else return try_ID();
}

Token Tokenizer::try_QUERIES() {
    pushChar();

    if (currChar() == 'u') pushChar();
    else return try_ID();

    if (currChar() == 'e') pushChar();
    else return try_ID();

    if (currChar() == 'r') pushChar();
    else return try_ID();

    if (currChar() == 'i') pushChar();
    else return try_ID();

    if (currChar() == 'e') pushChar();
    else return try_ID();

    if (currChar() == 's' && (nextChar() == ':' || isspace(nextChar()))) return foundTokenType(QUERIES);
    else return try_ID();
}

Token Tokenizer::try_RULES() {
    pushChar();

    if (currChar() == 'u') pushChar();
    else return try_ID();

    if (currChar() == 'l') pushChar();
    else return try_ID();

    if (currChar() == 'e') pushChar();
    else return try_ID();

    if (currChar() == 's' && (nextChar() == ':' || isspace(nextChar()))) return foundTokenType(RULES);
    else return try_ID();
}

Token Tokenizer::try_ID() {
    if (isEOF() || isspace(currChar())) return foundTokenType(ID, false);

    switch (currChar()) {
        // Special Characters
        case ',':
            return foundTokenType(ID, false);
        case '.':
            return foundTokenType(ID, false);
        case '?':
            return foundTokenType(ID, false);
        case '(':
            return foundTokenType(ID, false);
        case ')':
            return foundTokenType(ID, false);
        case ':':
            return foundTokenType(ID, false);
        case '*':
            return foundTokenType(ID, false);
        case '+':
            return foundTokenType(ID, false);
        case '\'':
            return foundTokenType(ID, false);
        case '#':
            return foundTokenType(ID, false);
        default:
            pushChar();
            return try_ID();
    }
}



