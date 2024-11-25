#include "commandinterpreter.h"
#include <algorithm>

CommandInterpreter::CommandInterpreter() {
    commands = {"left", "right", "down", "clockwise", "counterclockwise",
                "drop", "levelup", "leveldown", "norandom", "random",
                "sequence", "restart", "I", "J", "L", "O", "S", "Z", "T"};
}

void CommandInterpreter::addCommand(const std::string &command) {
    if (std::find(commands.begin(), commands.end(), command) == commands.end()) {
        commands.push_back(command);
    }
}

void CommandInterpreter::removeCommand(const std::string &command) {
    commands.erase(std::remove(commands.begin(), commands.end(), command), commands.end());
}

std::string CommandInterpreter::interpretCommand(const std::string &input) {
    std::string matchedCommand;
    int matchCount = 0;

    for (const auto &command : commands) {
        if (command.substr(0, input.size()) == input) {
            matchedCommand = command;
            ++matchCount;

            if (matchCount > 1) {
                return "Invalid command (ambiguous)";
            }
        }
    }
    return (matchCount == 1) ? matchedCommand : "Invalid command";
}