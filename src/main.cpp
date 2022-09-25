#include <iostream>
#include <string>
#include "menu.h"
#include <cstdlib>

std::string getEnvMode(std::string args) {
    std::string params[] = {args.substr(0, args.find('=')), args.substr(args.find('=')+1, args.length())};
    if(params[0] != "ENV_MODE") {
        return "";
    }
    
    return params[1];   
}

int main(int argc, char *argv[]){
    std::string ENV_MODE;
    try{
        ENV_MODE = getEnvMode(argv[1]);    
    }
    catch(const std::exception& e){
        ENV_MODE = "";
    }
    
    bool flag;

    do {
         flag = showMenu(ENV_MODE);
    } while (flag);   
}
