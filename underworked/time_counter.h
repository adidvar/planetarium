#ifndef TIME_COUNTER_H
#define TIME_COUNTER_H
#include <string>
#include <sstream>
/**
 * @brief Таймер уявоного часу
 */
class TimeCounter
{
    float second = 0;
    unsigned minutes = 0;
    unsigned hours = 0;
    unsigned days = 0;
    unsigned years = 0;
    float time_scale;
    unsigned long ticks = 0;
public:
    TimeCounter() = default;
    std::string time_dump();
    long double ToSeconds();
    void TickUp(unsigned c){ticks+=c;};
    void TimeUp(float delta_time , float time_scale);

    friend long double to_seconds(std::stringstream &ss);
};

#endif // DUMP_H
