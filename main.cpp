#include <iostream>
#include <string>
#include <fstream>

#include "Lexer.h"

using namespace std;

int main(int argc, char *argv[]) {

    ifstream in(argv[1]);

/*********************************** Project 1 - Scanner/Tokenizer ***********************************/

    string content((istreambuf_iterator<char>(in)), (istreambuf_iterator<char>()));

    Lexer lexer(content);

    lexer.tokenizeInput();


    return 0;
}
