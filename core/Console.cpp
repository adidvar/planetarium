#include "Console.h"
/*
Console::Console(init_result &res, std::mutex &mutex):
    th(&Console::thread,this),
    init(res),
    mutex(mutex)
{
    th.detach();
}


long double to_seconds(std::stringstream &ss)
{
    TimeCounter time;
    while(ss)
    {
        std::string name;
        long double value;
        ss >> name >>value;

        if(name == "y")
            time.years = value;
        else if (name == "d")
            time.days = value;
        else if (name == "m")
            time.minutes= value;
        else if (name == "h")
            time.hours = value;
        else if (name == "s")
            time.second = value;

    }
    return time.ToSeconds();
}

void Console::thread()
{
    while(true)
    {
        std::cout << ">";
        char data[256];
        std::cin.getline(data,256);
        std::stringstream ss;
        ss << data;

        std::string name;
        ss >> name;

        if(name == "clear")
        {
            std::lock_guard<std::mutex> guard(mutex);
            for(auto i : this->init.planets)
            {
                i->GetOrbit().clear();
            }
        } else if (name == "pause")
        {
            std::lock_guard<std::mutex> guard(mutex);
            init.cycle = !init.cycle;
        } else if (name == "speed")
        {
            std::lock_guard<std::mutex> guard(mutex);
            long double scale; ss >> scale;
            this->init.delta_time = scale;
        } else if (name == "speedd")
        {
            std::lock_guard<std::mutex> guard(mutex);
            long double scale; ss >> scale;
            init.delta_time*=scale;
        } else if (name == "accuracy")
        {
            std::lock_guard<std::mutex> guard(mutex);
            int scale; ss >> scale;
            this->init.calc_per_graphic_tick = scale;

        }  else if (name == "accuracyd")
        {
            std::lock_guard<std::mutex> guard(mutex);
            int scale; ss >> scale;
            this->init.calc_per_graphic_tick *= scale;
        } else if (name == "shipspeed")
        {
            std::lock_guard<std::mutex> guard(mutex);
            long double scale; ss >> scale;
            this->init.trackingStar->ChangeSpeed(scale);
        } else if (name == "shipvect")
        {
            std::lock_guard<std::mutex> guard(mutex);
            long double x , y; ss >> x >> y;
            this->init.trackingStar->addSpeed({x,y});
        }else if (name == "dump")
        {
            std::lock_guard<std::mutex> guard(mutex);
            dump(init.planets);
        } else if ( name == "skip")
        {
            std::lock_guard<std::mutex> guard(mutex);

            auto sec = to_seconds(ss);
            auto sec_begin = sec;
            long double scale = init.calc_per_graphic_tick;

            while(sec >= 0)
            {
                for(long double i=0;i<scale;i+=1)
                {
                    if(sec < 0)break;

                    for(auto &p : init.planets){
                        p->CalcAcceleration(init.planets);
                        p->MovePosition(init.delta_time/scale);
                    }
                    init.time.TickUp(1);
                    init.time.TimeUp(init.delta_time/scale,init.delta_time);
                    sec-=init.delta_time/scale;

                }
                for(auto &p : init.planets){
                    p->GetOrbit().clear();

                }

                std::cout << "Progress " << (int)(100-sec/sec_begin *100.0) << "%" << std::endl;
            }

        } else
        {
            std::cout << "error!" << std::endl;
        }
    }

}
*/

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
