#include "commandinterpreter.h"
#include <algorithm>

// Constructor: Initializes the command list with predefined commands.
CommandInterpreter::CommandInterpreter() {
    commands = {"left", "right", "down", "clockwise", "counterclockwise",
                "drop", "levelup", "leveldown", "norandom", "random",
                "sequence", "restart", "I", "J", "L", "O", "S", "Z", "T"};
}

// Method to add a new command if it doesn't already exist in the list.
void CommandInterpreter::addCommand(const std::string &command) {
    // Only add the command if it's not already in the list
    if (std::find(commands.begin(), commands.end(), command) == commands.end()) {
        commands.push_back(command);
    }
}

// Method to remove a command from the list.
void CommandInterpreter::removeCommand(const std::string &command) {
    // Find and remove the command from the list
    commands.erase(std::remove(commands.begin(), commands.end(), command), commands.end());
}

// Method to interpret the input command and return the matched command or an error message.
std::string CommandInterpreter::interpretCommand(const std::string &input) {
    std::string matchedCommand;
    int matchCount = 0;

    // Iterate through the commands to find a match for the input
    for (const auto &command : commands) {
        if (command.substr(0, input.size()) == input) {
            matchedCommand = command;
            ++matchCount;

            // Return error if there are multiple matches (ambiguous command)
            if (matchCount > 1) {
                return "Invalid command (ambiguous)";
            }
        }
    }

    // Return the matched command or an error if no match was found
    return (matchCount == 1) ? matchedCommand : "Invalid command";
}
