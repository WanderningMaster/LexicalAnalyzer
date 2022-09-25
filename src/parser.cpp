#include <stdexcept>
#include <iostream>
#include <cmath>
#include "parser.h"

//1-(-1)-1
//"1", "-", "(", "-", "1", "), "-", "1"
/*
1) minus on first position
2) minus between ( and number
3) 
*/

std::vector<Lexeme> lexemeAnalyze(std::string expr){
    std::vector<Lexeme> lexemes = {};
    int pos = 0;
    while(pos<expr.length()){
        if(expr[pos] == '('){
            Lexeme lexeme = {.type=LEFT_BRACKET, .value=std::string(1, expr[pos])};
            lexemes.push_back(lexeme);
            pos++;
            continue;
        }
        if(expr[pos] == ')'){
            Lexeme lexeme = {.type=RIGHT_BRACKET, .value=std::string(1, expr[pos])};
            lexemes.push_back(lexeme);
            pos++;
            continue;
        }    
        if(expr[pos] == '+'){
            Lexeme lexeme = {.type=PLUS, .value=std::string(1, expr[pos])};
            lexemes.push_back(lexeme);
            pos++;
            continue;
        }
        if(expr[pos] == '-'){
            Lexeme lexeme = {.type=MINUS, .value=std::string(1, expr[pos])};
            lexemes.push_back(lexeme);
            pos++;
            continue;
        }
        if(expr[pos] == '*'){
            Lexeme lexeme = {.type=MUL, .value=std::string(1, expr[pos])};
            lexemes.push_back(lexeme);
            pos++;
            continue;
        }
        if(expr[pos] == '/'){
            Lexeme lexeme = {.type=DIV, .value=std::string(1, expr[pos])};
            lexemes.push_back(lexeme);
            pos++;
            continue;
        }
        if(expr[pos] == 's' || expr[pos] == 'c' || expr[pos] == 't'){
            Lexeme lexeme = parseTrigonometric(expr, pos);
            lexemes.push_back(lexeme);
            continue;
        }
        if(expr[pos] <= '9' && expr[pos] >= '0'){
            Lexeme lexeme = parseNumber(expr, pos);
            if(lexemes.size() != 0){
                if(lexemes[lexemes.size()-1].type == MINUS){
                    if(lexemes.size()-1 == 0){
                        lexemes.erase(lexemes.begin());
                        lexeme.value = "-" + lexeme.value;
                    }
                    else{
                        if(lexemes[lexemes.size()-2].type == LEFT_BRACKET){
                            lexemes.erase(lexemes.begin() + lexemes.size()-1);
                            lexeme.value = "-" + lexeme.value;   
                        }
                    }
                }
            }
            
            lexemes.push_back(lexeme);
        }
        else{
            if(expr[pos] != ' '){
                throw std::runtime_error("Unexpected character: '"+std::string(1, expr[pos])+"' at position: "+std::to_string(pos));
            }
            pos++;
        } 
        
    }
    Lexeme lexeme = {.type=EOF_, .value=""};
    lexemes.push_back(lexeme);

    return lexemes;
}

Lexeme parseNumber(std::string expr, int &pos){
    std::string num = "";
    do{
        num.append(std::string(1, expr[pos]));
        pos++;
        
        if(pos >= expr.length()){
            break;
        }
    } while(expr[pos] <= '9' && expr[pos] >= '0' || expr[pos] == '.');

    Lexeme lexeme = {.type=NUMBER, .value=num};
    return lexeme;
}

Lexeme parseTrigonometric(std::string expr, int &pos){
    Lexeme lexeme;
    if(expr.substr(pos, 3) == "sin"){
        lexeme = {.type=SIN, .value=expr.substr(pos, 3)};
        pos+=3;
        return lexeme;
    }
    if(expr.substr(pos, 5) == "cosec"){
        lexeme = {.type=COSEC, .value=expr.substr(pos, 5)};
        pos+=5;
        return lexeme;
    }
    if(expr.substr(pos, 3) == "cos"){
        lexeme = {.type=COS, .value=expr.substr(pos, 3)};
        pos+=3;
        return lexeme;
    }
    if(expr.substr(pos, 3) == "ctg"){
        lexeme = {.type=CTG, .value=expr.substr(pos, 3)};
        pos+=3;
        return lexeme;
    }
    if(expr.substr(pos, 2) == "tg"){
        lexeme = {.type=TG, .value=expr.substr(pos, 2)};
        pos+=2;
        return lexeme;
    }
    if(expr.substr(pos, 3) == "sec"){
        lexeme = {.type=SEC, .value=expr.substr(pos, 3)};
        pos+=3;
        return lexeme;
    }
    else throw std::runtime_error("Unexpected character: '"+std::string(1, expr[pos])
        +"' at position: "+std::to_string(pos));
}

//"1", "+", "sin", "(", "60", ")"
float factor(std::vector<Lexeme> lexemes, int &pos){

    Lexeme lexeme = lexemes[pos++];
    switch (lexeme.type){
        case SIN: {
            float value = factor(lexemes, pos);
            return std::sin(value);
        }
        case COS: {
            float value = factor(lexemes, pos);
            return std::cos(value);
        }
        case TG: {
            float value = factor(lexemes, pos);
            return std::sin(value)/std::cos(value);
        }
        case CTG: {
            float value = factor(lexemes, pos);
            return std::cos(value)/std::sin(value);
        }
        case SEC: {
            float value = factor(lexemes, pos);
            return 1.0 / std::cos(value);
        }
        case COSEC: {
            float value = factor(lexemes, pos);
            return 1.0 / std::sin(value);
        }
        case NUMBER: {
            return std::stof(lexeme.value);
        }
        case LEFT_BRACKET:{
            float value = plusminus(lexemes, pos);
            lexeme = lexemes[pos++];
            if(lexeme.type != RIGHT_BRACKET){
                throw std::runtime_error("Unexpected character: '" + lexeme.value
                    + "' at position: "+std::to_string(pos));
            }
            return value;
        }
        default:{
            throw std::runtime_error("Unexpected character: '" + lexeme.value
                + "' at position: "+std::to_string(pos));
            break;    
        }
    }
}

float multdiv(std::vector<Lexeme> lexemes, int &pos){
    float value = factor(lexemes, pos);
    while (true){
        Lexeme lexeme = lexemes[pos++];
        switch (lexeme.type){
            case MUL: {
                value *= factor(lexemes, pos);
                break;
            }
            case DIV: {
                value /= factor(lexemes, pos);
                break;
            }
            default:{
                pos--;
                return value;
            }
        }
    }   
}

float plusminus(std::vector<Lexeme> lexemes, int &pos){
    float value = multdiv(lexemes, pos);
    while (true){
        Lexeme lexeme = lexemes[pos++];
        switch (lexeme.type){
        case PLUS:
            value += multdiv(lexemes, pos);
            break;
        case MINUS:
            value -= multdiv(lexemes, pos);
            break;
        default:
            pos--;
            return value;
        }
    }
}

float expression(std::vector<Lexeme> lexemes, int &pos){
    Lexeme lexeme = lexemes[pos++];
    if(lexeme.type == EOF_){
        return 0;
    }
    else {
        pos--;
        return plusminus(lexemes, pos);
    }
}

