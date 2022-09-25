#pragma once
#include <string>
//d>b 10010

enum ConvertType{
    UNKNOWN_TYPE,
    DECIMAL_TO_BINARY,
    DECIMAL_TO_HEX,
    BINARY_TO_DECIMAL,
    BINARY_TO_HEX,
    HEX_TO_DECIMAL,
    HEX_TO_BINARY,
};

struct Convert{
    ConvertType type;
    std::string value;
};


Convert parseExpression(std::string expr);

std::string fromDecimalToBinary(std::string number);
std::string fromDecimalToHex(std::string number);

std::string fromBinaryToDecimal(std::string number);
std::string fromBinaryToHex(std::string number);

std::string fromHexToDecimal(std::string number);
std::string fromHexToBinary(std::string number);

std::string convert(Convert data);