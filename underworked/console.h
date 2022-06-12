#ifndef CONSOLE_H
#define CONSOLE_H
#include <functional>
#include <thread>
#include "init.h"

/**
 * @brief Клас який керує системою з терміналу
 */
class Console
{
    std::thread th;
    init_result &init;
    std::mutex &mutex;
public:
    Console(init_result &init , std::mutex& mutex);
    ~Console() = default;
private:
    void thread();
};

#endif
