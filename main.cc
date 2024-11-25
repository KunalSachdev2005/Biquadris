#include <iostream>
#include "CommandInterpreter.h"

int main() {
    CommandInterpreter ci;

    std::cout << "=== Command Interpreter Test ===" << std::endl;
    std::cout << "Valid commands: left, right, down, clockwise, counterclockwise, drop, "
                 "levelup, leveldown, norandom, random, sequence, restart, I, J, L, O, S, Z, T"
              << std::endl;
    std::cout << "Type 'quit' to exit the test." << std::endl;

    std::string input;
    while (true) {
        std::cout << "\nEnter a command: ";
        std::cin >> input;

        if (input == "quit") break;

        std::string result = ci.interpretCommand(input);
        if (result == "Invalid command") {
            std::cout << "Error: Invalid command!" << std::endl;
        } else {
            std::cout << "Interpreted Command: " << result << std::endl;
        }
    }

    std::cout << "=== Test Completed ===" << std::endl;
    return 0;
}
