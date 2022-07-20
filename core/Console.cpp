#include "Console.h"

 Console::Console(callback_t callback) :
    callback(callback)
{}

void Console::PushLetter(char character) { command.push_back(character); }

void Console::BackSpace() { if (command.size())command.pop_back(); }

void Console::Enter()
{
    if (!command.size())return;
    std::vector < std::string > commands;

    std::string::iterator bit, eit = command.begin();
    do {
        bit = eit;
        eit = std::find(eit + 1, command.end(), ' ');
        commands.emplace_back(bit, eit);
    } while (eit != command.end());

    callback(commands);
    command.clear();
}

std::string Console::Text() { return std::string(">>>") + command; }
