#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <string>
#include <vector>

class CommandInterpreter {
    private:
        std::vector<std::string> commands;                          // Vector to hold the list of available commands

    public:
        CommandInterpreter();                                       // Constructor: Initializes the command list
        void addCommand(const std::string &command);                // Method to add a new command to the list
        void removeCommand(const std::string &command);             // Method to remove a command from the list
        std::string interpretCommand(const std::string &input);     // Method to interpret command and return matched command or error message
};

#endif
