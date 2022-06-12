#include <movement.h>
#include "vector2f.h"
#include <algorithm>
#include "settings.h"

const double scrool_speed = SCALE_SPEED;
const double key_scale_delta = KEY_SCALE_SPEED;

struct epos
{
    long double x , y;
};

epos eposition[2] = {{-width, -height },{width,height}};

inline long double transform_p(long double current_position , long double max_position , long double proect_max_pos)
{
    return current_position / max_position * proect_max_pos;
};
long double scale_screen_width(long double current_position)
{
    return transform_p(current_position - eposition[0].x , eposition[1].x-eposition[0].x , width );
};
long double scale_screen_height(long double current_position)
{
    return transform_p(current_position - eposition[0].y , eposition[1].y-eposition[0].y , height );
};
long double scale_screen_base(long double current_position)
{
    return transform_p(current_position , eposition[1].y-eposition[0].y , height );
};

#include <iostream>

void movement_event(sf::Event &e , init_result &sys)
{
    static bool move_mode = false;
    static int last_x = 0;
    static int last_y = 0;

    static Planet *current_p = nullptr;

    long double delta_x = eposition[1].x - eposition[0].x;
    long double delta_y = eposition[1].y - eposition[0].y;

    if(e.type == sf::Event::MouseWheelScrolled)
    {
        eposition[0].x -= -delta_x * scrool_speed * e.mouseWheelScroll.delta;
        eposition[0].y -= -delta_y  * scrool_speed * e.mouseWheelScroll.delta;
        eposition[1].x += -delta_x * scrool_speed * e.mouseWheelScroll.delta;
        eposition[1].y += -delta_y * scrool_speed * e.mouseWheelScroll.delta;
    }

    if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::O)
    {
        eposition[0].x -= transform_p( key_scale_delta  , scrool_speed , delta_x);
        eposition[0].y -= transform_p( key_scale_delta  , scrool_speed , delta_y);
        eposition[1].x += transform_p( key_scale_delta  , scrool_speed , delta_x);
        eposition[1].y += transform_p( key_scale_delta  , scrool_speed , delta_y);
    }
    if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::P)
    {
        eposition[0].x -= transform_p( -key_scale_delta  , scrool_speed , delta_x);
        eposition[0].y -= transform_p( -key_scale_delta  , scrool_speed , delta_y);
        eposition[1].x += transform_p( -key_scale_delta  , scrool_speed , delta_x);
        eposition[1].y += transform_p( -key_scale_delta  , scrool_speed , delta_y);
    }

    if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
    {
        move_mode = true;
        last_x = e.mouseButton.x ;
        last_y = e.mouseButton.y ;
    }
    if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
        move_mode = false;


    if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right && sys.cycle == false)
    {
            auto m_position = Vector2f(get_real_x(e.mouseButton.x),get_real_y(e.mouseButton.y));
            for(auto p : sys.planets)
            {
                if((p->GetPosition()-m_position).Module() <= std::max(p->Radius()*3.0,scale_real(4)))
                {
                    current_p = p;
                    break;
                }
            }
    }
    if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Right)
        current_p = nullptr;

    if(e.type == sf::Event::MouseMoved && move_mode)
    {
        eposition[0].x -= transform_p( (e.mouseMove.x - last_x ) , width , delta_x);
        eposition[0].y -= transform_p( (e.mouseMove.y - last_y ) , height , delta_y);
        eposition[1].x -= transform_p( (e.mouseMove.x - last_x ) , width , delta_x);
        eposition[1].y -= transform_p( (e.mouseMove.y - last_y ) , height , delta_y);
        last_x = e.mouseMove.x ;
        last_y = e.mouseMove.y ;
    }
    if(e.type == sf::Event::MouseMoved)
    {
        if(current_p!=nullptr)
            current_p->SetPosition(current_p->GetPosition()+Vector2f(scale_real(e.mouseMove.x - last_x),scale_real(e.mouseMove.y - last_y)));

        last_x = e.mouseMove.x ;
        last_y = e.mouseMove.y ;
    }

}

void load_scale_factor(long double scale)
{
    eposition[0] = {-width*scale, -height*scale };
    eposition[1] = { width *scale, height*scale };
}

long double get_real_x(unsigned screen_x)
{
   return eposition[0].x + (eposition[1].x - eposition[0].x)*((long double)screen_x / width);
}

long double get_real_y(unsigned screen_y)
{
   return eposition[0].y + (eposition[1].y - eposition[0].y)*((long double)screen_y / height);
}

long double scale_real(long double num)
{
    return (eposition[1].y - eposition[0].y)*((long double)num / height);
}
