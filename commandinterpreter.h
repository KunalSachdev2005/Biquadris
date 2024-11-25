#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include<string>
#include<vector>

class CommandInterpreter {
    private:
        std::vector<std::string> commands;

    public:
        CommandInterpreter();
        void addCommand(const std::string &command);
        void removeCommand(const std::string &command);
        std::string interpretCommand(const std::string &input);
};

#endif
