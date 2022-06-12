#pragma once
#include <string>

template <typename T>
class Console
{
    std::string command;
public:
    Console(T& controller){};

    void PushLetter(char character) { command.push_back(character); };
    void Enter() { command.clear(); };
    std::string Text() { return command; };
};
