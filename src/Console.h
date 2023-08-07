#pragma once
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>

#include "Settings.h"

class Console
{
    std::string command;
    using callback_t = std::function<void(const std::vector<std::string>&)>;
    callback_t callback;
public:
    Console(callback_t callback);
    void PushLetter(char character);
    void BackSpace();
    void Enter();
    std::string Text();
};
