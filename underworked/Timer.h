#ifndef TIMER_H
#define TIMER_H
#include <chrono>
/**
 * @brief Таймер реального часу
 */
class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using msec_t = std::chrono::duration<double, std::ratio<1,1000> >;
    std::chrono::time_point<clock_t> begin;
public:
    Timer() : begin(clock_t::now())
    {}

    void reset()
    {
        begin = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<msec_t>(clock_t::now() - begin).count();
    }
};


#endif // INIT_H
