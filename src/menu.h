#pragma once

#include <string>
#include "parser.h"
#include "converter.h"


const std::string menu[] = {
    "Calculator",
    "Converter",
    "Exit",
};


bool showMenu();
void openCalculator();
void openConverter();