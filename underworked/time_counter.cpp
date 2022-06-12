#include "time_counter.h"
#include <sstream>

using namespace std;

std::string TimeCounter::time_dump()
{
    std::stringstream ss;
    ss << "Ticks:" << ticks << endl
       << "Time scale:" << time_scale << endl
       << "Years:  " << years << endl
       << "Days:   " << days << endl
       << "Hours:  " << hours << endl
       << "Minutes:" << minutes << endl
       << "Second: " << second << endl;
    return ss.str();
}

long double TimeCounter::ToSeconds()
{
    long double second = 0;
    second = years*365;
    second = (days+second)*24.0;
    second = (hours+second)*60.0;
    second = (minutes+second)*60.0;
    second += this->second;
    return second;
}

void TimeCounter::TimeUp(float delta_time, float time_scale)
{
    this->time_scale = time_scale;

    second+=delta_time;
    minutes += (unsigned)(second/60.0);
    hours += minutes/60;
    days += hours/24;
    years += days/365;

    second = second - ((unsigned)(second/60.0))*60.0;
    minutes = minutes % 60;
    hours = hours % 24;
    days = days % 365;
}
