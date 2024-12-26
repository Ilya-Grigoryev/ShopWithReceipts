#include "ShopSystem.h"

int main() {
    ShopSystem shopSystem;

    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    while (cmd != "exit") {
        if (!shopSystem.command(cmd, iss))
            std::cout << "(make sure the command is entered correctly)\nCMD --> ";
        line.clear();
        std::getline(std::cin, line);
        iss = std::istringstream(line);
        iss >> cmd;
    }
    return 0;
}