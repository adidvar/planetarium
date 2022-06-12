#include <iostream>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "Planet.h"
#include "PlanetsThread.h"
#include "Timer.h"
#include "Options.h"
#include "PositionTransformer.h"
#include "Console.h"

constexpr size_t width = 1280 , height = 720;

using sf::Keyboard;
const std::unordered_map<sf::Keyboard::Key, char > key_map
{
    {Keyboard::Q , 'q'},
    {Keyboard::W , 'w'},
    {Keyboard::E , 'e'},
    {Keyboard::R , 'r'},
    {Keyboard::T , 't'},
    {Keyboard::Y , 'y'},
    {Keyboard::U , 'u'},
    {Keyboard::I , 'i'},
    {Keyboard::O , 'o'},
    {Keyboard::P , 'p'},
    {Keyboard::A , 'a'},
    {Keyboard::S , 's'},
    {Keyboard::D , 'd'},
    {Keyboard::F , 'f'},
    {Keyboard::G , 'g'},
    {Keyboard::H , 'h'},
    {Keyboard::J , 'j'},
    {Keyboard::K , 'k'},
    {Keyboard::L , 'l'},
    {Keyboard::Z , 'z'},
    {Keyboard::X , 'x'},
    {Keyboard::C , 'c'},
    {Keyboard::V , 'v'},
    {Keyboard::B , 'b'},
    {Keyboard::N , 'n'},
    {Keyboard::M , 'm'}
};

void movement_event(sf::Event &e , PTransformer<double,width,height> & pt)
{
    static bool move_mode = false;
    static int last_x = 0;
    static int last_y = 0;

    if(e.type == sf::Event::MouseWheelScrolled)
    {
        pt.ScaleCamera(e.mouseWheelScroll.delta);
    }

    if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
    {
        move_mode = true;
        last_x = e.mouseButton.x ;
        last_y = e.mouseButton.y ;
    }
    if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
        move_mode = false;
    if(e.type == sf::Event::MouseMoved && move_mode)
    {
        pt.MoveCameraP(e.mouseMove.x - last_x, e.mouseMove.y - last_y);
        last_x = e.mouseMove.x ;
        last_y = e.mouseMove.y ;
    }
    if(e.type == sf::Event::MouseMoved)
    {
        last_x = e.mouseMove.x ;
        last_y = e.mouseMove.y ;
    }
}
/*
void load_scale_factor(number scale)
{
    cposition[0] = {-width*scale, -height*scale };
    cposition[1] = { width *scale, height*scale };
}
*/

int main()
{
    auto core = PlanetsThread<double>::FromFile("test.txt");
    PTransformer<double, width, height> pt;

    using std::chrono_literals::operator""s;
    core->SetTaktTime(1s);
    core->Play(3600 * 60, 60);

    bool console_e = false;
    Console<PlanetsThread<double>> console(*core);

    //load_scale_factor(sys.default_scale);

//    Console console(sys,mutex);

    sf::Font mfont; mfont.loadFromFile("font.otf");
    sf::RenderWindow w(sf::VideoMode(width,height),"Planetarium");
    w.setFramerateLimit(60);

    while(w.isOpen())
    {
        sf::Event e;
        while(w.pollEvent(e))
        {
            movement_event(e,pt);
            /*
            if( (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Middle) || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space) )
                sys.cycle = !sys.cycle;
            if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Q)
                load_scale_factor(sys.default_scale);
            if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::T)
                render_text = !render_text;
            if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::R)
                draw_orbit = !draw_orbit;
            if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::D)
                dump(sys.planets);
                */
            if (e.type == sf::Event::KeyPressed && console_e == true && key_map.count(e.key.code) == 1)
                console.PushLetter(key_map.at(e.key.code));

            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter)
            {
                if(!console_e)
                console.Enter();
                console_e = !console_e;
            }

            if(e.type == sf::Event::Closed)
                w.close();
        }

        using std::chrono_literals::operator""h;
       // core->CalculateStep(1h);

        w.clear();


        for(size_t i = 0 ; i < core->Count() ; i++)
        {
            auto p = (*core)[i];
            auto pos = p.GetPositionV();

            double radius = std::max ( static_cast<decltype(p.x)>(1.0), pt.Scale(p.GetRadius()));

            sf::CircleShape shape(radius);

            sf::Vector2f after(pt.ScaleW(pos.x) - radius,
                           pt.ScaleH(pos.y)  - radius);

            if(after.x < 0.0 || after.x > width || after.y < 0.0 || after.y > height)
                continue;

            shape.setPosition(after);

            //sf::VertexArray array(sf::PrimitiveType::Lines);
            /*
            array.append(sf::Vertex(sf::Vector2f(after.x + radius  ,after.y + radius), sf::Color(sf::Color::Blue)));
            array.append(sf::Vertex(sf::Vector2f(
                                        pt.ScaleW( pos.x + p.GetSpeedV().Nomalize().x * sys.vector_scale ),
                                        pt.ScaleH( pos.y + p.GetSpeedV().Nomalize().y * sys.vector_scale )),
                                    sf::Color(sf::Color::Blue)));

            array.append(sf::Vertex(sf::Vector2f(after.x + radius  ,after.y + radius), sf::Color(sf::Color::Red)));
            array.append(sf::Vertex(sf::Vector2f(
                                        pt.ScaleW( pos.x + p->GetAccel().Nomalize().x  * sys.vector_scale ),
                                        pt.ScaleH(pos.y + p->GetAccel().Nomalize().y  * sys.vector_scale )),
                                    sf::Color(sf::Color::Red)));

           
            if(draw_orbit)
            {
                sf::VertexArray orbit(sf::PrimitiveType::LineStrip);
                for(auto orbit_p : p->GetOrbit())
                    orbit.append(sf::Vertex(sf::Vector2f(scalediwidiwi_screen_width(orbit_p.x),scale_screen_height(orbit_p.y)),sf::Color::Green));
                w.draw(orbit);
            }
            */

            w.draw(shape);

           // w.draw(array);
            /*
            if(p->GetName() != "None" && render_text)
            {
                sf::Text text(p->GetName(),mfont, 40);
                text.setFillColor(sf::Color::Red);
                text.setPosition(after.x,after.y-radius);

                w.draw(text);
            }
            */

        }

        sf::Text time_stat(core->GetTimeDump(), mfont, 20);
        w.draw(time_stat);

        if (console_e) {
            sf::Text c_text(console.Text(), mfont, 20);
            c_text.setPosition(0, 400);
            w.draw(c_text);
        }
/*
        sf::Text ship__stat(ship_stat(sys),mfont,25);
        ship__stat.setPosition(0,300);
        w.draw(ship__stat);
        sf::Text fps(std::to_string((int)(1.0/frame_timer.elapsed()*1000.0))+" fps",mfont,20);
        fps.setPosition(600,0);
        w.draw(fps);
        frame_timer.reset();
*/

        w.display();
    }
    return 0;
}

