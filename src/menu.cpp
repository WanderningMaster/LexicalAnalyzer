#include <iostream>
#include "menu.h"

bool showMenu(std::string ENV_MODE){
    bool flag = true;
    for(int i = 0; i<3; i++){
        std::cout<<i+1<<". "<<menu[i]<<std::endl;
    }
    std::cout<<std::endl;

    //making request 
    int index;
    std::cout<<"> ";
    std::cin>>index;

    switch (index){
        case 1:{
            getchar();
            system("clear");
            openCalculator(ENV_MODE);
            system("clear");

            break;
        }
        case 2:{
            getchar();
            system("clear");
            openConverter();
            system("clear");

            break;
        }
        case 3:
            getchar();
            system("clear");
            flag = false;

            break;
        default:
            break;
    }

    return flag;
}
void openCalculator(std::string ENV_MODE){
    std::string help = "lsfn\t\t- see all commands\nquit\t\t- exits the calculator\n";
    std::string lsfn = "sin\ncos\ntg\nctg\nsec\ncosec\n";

    std::cout<<"Type 'help' for available commands"<<std::endl;
    do
    {
        std::string expr;
        std::cout<<"> ";
        std::getline(std::cin, expr);
        if(expr == "quit") break;
        if(expr == "help"){
            std::cout<<help;
            continue;
        }
        if(expr == "lsfn"){
            std::cout<<lsfn;
            continue;
        }
        try{
            std::vector<Lexeme> lexemes = lexemeAnalyze(expr);
            
            if(ENV_MODE == "debug") {
                for(auto lexeme: lexemes){
                    std::cout<<"{ Type: "<<lexeme.type<<" Value: "<<lexeme.value<<"}\n";
                }
            }
            int pos = 0;
            std::cout<<expression(lexemes, pos)<<std::endl;
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    } while (true);
}
void openConverter(){
    std::string help = "lsfn\t\t- see all commands\nquit\t\t- exits the convertor\n";
    std::string lsfn = "d>b\t\t- Convert from decimal to binary\nd>h\t\t- Convert from decimal to hex\nb>d\t\t- Convert from binary to decimal\nb>h\t\t- Convert from Binary to hex\nh>d\t\t- Convert from hex to decimal\nh>b\t\t- Convert from hex to binary\n";

    do{
        std::string expr;
        std::cout<<"> ";
        std::getline(std::cin, expr);
        if(expr == "quit") break;
        if(expr == "help"){
            std::cout<<help;
            continue;
        }
        if(expr == "lsfn"){
            std::cout<<lsfn;
            continue;
        }
        try{
            Convert data = parseExpression(expr);

            std::string convertedNumber = convert(data);
            std::cout<<convertedNumber<<std::endl;
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    } while (true);
}