#include <cmath>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <iostream>
#include "converter.h"

std::string fromHexToDecimal(std::string number){
    int base = 0;
    int dec_val = 0;

    for (int i = number.size() - 1; i >= 0; i--) {
        if (number[i] >= '0' && number[i] <= '9') {
            dec_val += std::pow(16, base) * (number[i] - '0');
        }
        else if (number[i] >= 'A' && number[i] <= 'F') {
            dec_val += std::pow(16, base) * (int(number[i]) - 55);
        } 
        else { 
            throw std::runtime_error("Unexpected character: '"+std::string(1, number[i])+"' at position: "+std::to_string(i));
        }
        base++;
    }
    return std::to_string(dec_val);
}
std::string fromHexToBinary(std::string number){
    std::string decimal = fromHexToDecimal(number);

    return fromDecimalToBinary(decimal);
}

std::string fromBinaryToDecimal(std::string number){
    int base = 0;
    int dec_val = 0;

    for (int i = number.size() - 1; i >= 0; i--) {
        if (number[i] >= '0' && number[i] <= '1') {
            dec_val += std::pow(2, base) * (number[i] - '0');
        }
        else { 
            throw std::runtime_error("Unexpected character: '"+std::string(1, number[i])+"' at position: "+std::to_string(i));
        }
        base++;
    }
    return std::to_string(dec_val);
}
std::string fromBinaryToHex(std::string number){
    std::string decimal = fromBinaryToDecimal(number);

    return fromDecimalToHex(decimal);
}

std::string fromDecimalToBinary(std::string number){
    std::string binary = "";
    for (int i = number.size() - 1; i >= 0; i--) {
        if ( !(number[i] >= '0' && number[i] <= '9') ) {
            throw std::runtime_error("Unexpected character: '"+std::string(1, number[i])+"' at position: "+std::to_string(i));
        }
    }
    int decimal = std::stoi(number);
    while (decimal != 0) {
        int remainder = decimal % 2;
        
        binary += std::to_string(remainder);
        decimal /= 2;
    }

    return std::string(binary.rbegin(), binary.rend());
}
std::string fromDecimalToHex(std::string number){
    std::string hex = "";
    for (int i = number.size() - 1; i >= 0; i--) {
        if ( !(number[i] >= '0' && number[i] <= '9') ) {
            throw std::runtime_error("Unexpected character: '"+std::string(1, number[i])+"' at position: "+std::to_string(i));
        }
    }
    int decimal = std::stoi(number);
    while (decimal != 0) {
        int remainder = decimal % 16;
        if(remainder >= 10){
            hex += char(55 + remainder);
        } else hex += std::to_string(remainder);
        decimal /= 16;
    }

    return std::string(hex.rbegin(), hex.rend());
}


Convert parseExpression(std::string expr){
    std::istringstream iss(expr);
    std::string arr[3];
    int i = 0;
    while ( std::getline( iss, arr[i], ' ' )) {
        i++;
        if(i == 3){
            throw std::runtime_error("Unknown instruction");
        }
    }
    
    ConvertType type = UNKNOWN_TYPE;
    if(arr[0] == "d>b"){
        type = DECIMAL_TO_BINARY;
    }
    if(arr[0] == "d>h"){
        type = DECIMAL_TO_HEX;
    }
    if(arr[0] == "b>d"){
        type = BINARY_TO_DECIMAL;
    }
    if(arr[0] == "b>h"){
        type = BINARY_TO_HEX;
    }
    if(arr[0] == "h>d"){
        type = HEX_TO_DECIMAL;
    }
    if(arr[0] == "h>b"){
        type = HEX_TO_BINARY;
    }
    if(type == UNKNOWN_TYPE){
        throw std::runtime_error("Unknown instruction");
    }

    Convert data = {.type=type, .value=arr[1]};

    return data;
}

std::string convert(Convert data){
    std::string convertedNumber;
    switch (data.type){
        case DECIMAL_TO_BINARY:{
            convertedNumber = fromDecimalToBinary(data.value);
            break;
        }
        case DECIMAL_TO_HEX:{
            convertedNumber = fromDecimalToHex(data.value);
            break;    
        }
        case BINARY_TO_DECIMAL:{
            convertedNumber = fromBinaryToDecimal(data.value);
            break;
        }
        case BINARY_TO_HEX:{
            convertedNumber = fromBinaryToHex(data.value);
            break;
        }
        case HEX_TO_DECIMAL:{
            convertedNumber = fromHexToDecimal(data.value);
            break;
        }
        case HEX_TO_BINARY:{
            convertedNumber = fromHexToBinary(data.value);
            break;
        }
        default:
            break;
    }

    return convertedNumber;
}
