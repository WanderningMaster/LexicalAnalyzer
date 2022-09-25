#pragma once

#include <string>
#include "parser.h"
#include "converter.h"


const std::string menu[] = {
    "Calculator",
    "Converter",
    "Exit",
};


bool showMenu(std::string ENV_MODE);
void openCalculator(std::string ENV_MODE);
void openConverter();