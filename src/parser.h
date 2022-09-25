#pragma once

#include <string>
#include <vector>

enum LexemeType{
    LEFT_BRACKET,
    RIGHT_BRACKET,
    PLUS,
    MINUS,
    MUL,
    DIV,
    NUMBER,
    SIN,
    COS,
    TG,
    CTG,
    SEC,
    COSEC,
    EOF_,
};

struct Lexeme{
    LexemeType type;
    std::string value;
};

std::vector<Lexeme> lexemeAnalyze(std::string expr);
Lexeme parseNumber(std::string expr, int &pos);
Lexeme parseTrigonometric(std::string expr, int &pos);

float factor(std::vector<Lexeme> lexemes, int &pos);
float multdiv(std::vector<Lexeme> lexemes, int &pos);
float plusminus(std::vector<Lexeme> lexemes, int &pos);
float expression(std::vector<Lexeme> lexemes, int &pos);
