#pragma once
#include <string>
#include <algorithm>

template <typename T>
class Console
{
    std::string command;
    T& controller;
public:
    Console(T& controller):
        controller(controller)
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

        if (commands.front() == "stop") {
            controller.Stop();
        }
        if (commands.front() == "start") {
            controller.Play(std::stof(commands[1]), std::stof(commands[2]));
        }
        if (commands.front() == "skip") {
            controller.PlayFor(std::stof(commands[1]));
        }
        if (commands.front() == "precision") {
            controller.SetTaktTime( std::chrono::duration<T::number_t>(std::stof(commands[1])));
        }
        
        command.clear();
    };
    std::string Text() { return std::string(">>")+command; };
};
