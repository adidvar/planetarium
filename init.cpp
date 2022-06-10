#include "init.h"
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include "ship.h"

//загружає з файлу конфігурації
init_result file_init(std::string filename)
{
    init_result planets;
    std::ifstream file(filename);

    int orbit_len;
    file >> planets.delta_time >> orbit_len >> planets.vector_scale >> planets.default_scale;
    do
    {
        std::string name;
        long double mass;
        long double density;
        Vector2f position(0,0);
        Vector2f speed(0,0);
        file >> name >> mass >> density >> position.x >> position.y >> speed.x >> speed.y;
        if(!file)break;
        if(name.front()=='_')
        {
            Ship* ship = new Ship(name,mass,density,position,speed,orbit_len);
            planets.planets.push_back(ship);
            planets.trackingStar = ship;
        }
        else
            planets.planets.push_back(new Planet(name,mass,density,position,speed,orbit_len));
    } while(file);
    file.close();
    return planets;
}

init_result random_init()
{
    init_result vect;
    for(int i=0;i<100;i++)
        vect.planets.push_back(new Planet( "None" , pow(10,rand()%10)*10000 , 5500 , Vector2f(rand()%2000-1000 , rand()%2000-1000 ) , Vector2f(0,0),-1));
    return vect;
}
//просто загружає
init_result initplanets()
{
    std::vector<std::string> configs;

    boost::filesystem::directory_iterator dir(boost::filesystem::current_path());
    for( const boost::filesystem::path &p : dir)
        if(p.filename().string().front()=='=')
            configs.push_back(p.filename().string());

    unsigned counter = 0;
    for(const auto &i : configs)
        std::cout << '(' << counter++ << ')' << "Finded new config---" << i << std::endl;
    std::cout << "Enter configuration number:";
    std::cin >> counter;

    return file_init(configs.at(counter));
}
