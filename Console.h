#pragma once
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>

class Console
{
    std::string command;
    using callback_t = std::function<void(const std::vector<std::string>&)>;
    callback_t callback;
public:
    Console(callback_t callback):
        callback(callback)
    {};
    void PushLetter(char character) { command.push_back(character); };
    void BackSpace() { if(command.size())command.pop_back(); };
    void Enter()
    {
        if (!command.size())return;
        std::vector < std::string > commands;

        std::string::iterator bit, eit = command.begin();
        do {
            bit = eit;
			eit = std::find(eit+1, command.end(), ' ');
			commands.emplace_back(bit, eit);
        } while (eit != command.end());

        callback(commands);
        command.clear();
    };
    std::string Text() { return std::string(">>>")+command; };
};
