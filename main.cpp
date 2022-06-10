#include <iostream>
#include "SFML/Graphics.hpp"
#include "planet.h"
#include "init.h"
#include "movement.h"
#include "dump.h"

const long double width = 1280 , height = 720;

int main()
{
    init_result sys = initplanets();
    load_scale_factor(sys.default_scale);

    sf::Font mfont; mfont.loadFromFile("font.ttf");
    sf::RenderWindow w(sf::VideoMode(width,height),"planets");
    w.setFramerateLimit(60);

    bool control_mode = false;

    bool cycle = true;
    while(w.isOpen())
    {
        sf::Event e;
        while(w.pollEvent(e))
        {
            movement_event(e);
            if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Middle)
                cycle = !cycle;

            if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right)
                control_mode = true;
            if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Right)
                control_mode = false;

            if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::A)
                sys.trackingStar->ChangeSpeed(0.8);
            if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::S)
                sys.trackingStar->ChangeSpeed(1.25);
            if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Q)
                load_scale_factor(sys.default_scale);





            if(e.type == sf::Event::Closed)
                w.close();
            if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::D)
                dump(sys.planets);

        }

         //обрахунок координат
        for(auto &p : sys.planets)
            if(cycle){
                p->CalcAcceleration(sys.planets);
                p->MovePosition(sys.delta_time);
            }

        w.clear();
        for(auto &p : sys.planets)
        {

            auto pos = p->GetPosition();

            double radius = std::max ( static_cast<long double>(1.0) , scale_screen_base( pow(  3.0*(p->GetMass() / p->GetDestiny() )/4.0 /M_PI, 0.333333) ) );

            sf::CircleShape shape(radius);

            Vector2f after(scale_screen_width(pos.x) - radius,
                           scale_screen_height(pos.y)  - radius);

            if(after.x < 0.0 || after.x > width || after.y < 0.0 || after.y > height)
                continue;

            shape.setPosition(after);

            sf::VertexArray array(sf::PrimitiveType::Lines);

            array.append(sf::Vertex(sf::Vector2f(after.x + radius  ,after.y + radius), sf::Color(sf::Color::Blue)));
            array.append(sf::Vertex(sf::Vector2f(
                                        scale_screen_width( pos.x + p->GetSpeed().Nomalize().x * sys.vector_scale ),
                                        scale_screen_height( pos.y + p->GetSpeed().Nomalize().y * sys.vector_scale )),
                                        sf::Color(sf::Color::Blue)));

            array.append(sf::Vertex(sf::Vector2f(after.x + radius  ,after.y + radius), sf::Color(sf::Color::Red)));
            array.append(sf::Vertex(sf::Vector2f(
                                        scale_screen_width( pos.x + p->GetAccel().Nomalize().x  * sys.vector_scale ),
                                        scale_screen_height(pos.y + p->GetAccel().Nomalize().y  * sys.vector_scale )),
                                        sf::Color(sf::Color::Red)));

            sf::VertexArray orbit(sf::PrimitiveType::LineStrip);
            for(auto orbit_p : p->GetOrbit())
                orbit.append(sf::Vertex(sf::Vector2f(scale_screen_width(orbit_p.x),scale_screen_height(orbit_p.y)),sf::Color::Green));

            w.draw(orbit);

            w.draw(shape);

            w.draw(array);
            if(p->GetName() != "None")
            {
                sf::Text text(p->GetName(),mfont, 40);
                text.setFillColor(sf::Color::Red);
                text.setPosition(after.x,after.y-radius);

                w.draw(text);
            }
        }
        w.display();
    }

    for(auto &p : sys.planets)
        delete p;

    return 0;
}

