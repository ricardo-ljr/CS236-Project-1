cmake_minimum_required(VERSION 3.16)
project(Project_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project_1 main.cpp Token.h Tokens.h cmake-build-debug/Tokenizer.h cmake-build-debug/Tokenizer.cpp Automaton.h MatcherAutomaton.h Lexer.h)