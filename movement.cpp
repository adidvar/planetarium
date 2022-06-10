#include <movement.h>
const unsigned scrool_speed = 30;

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

void movement_event(sf::Event &e)
{
    static bool move_mode = false;
    static int last_x = 0;
    static int last_y = 0;

    if(e.type == sf::Event::MouseWheelScrolled)
    {
        eposition[0].x -= transform_p( -e.mouseWheelScroll.delta  , scrool_speed , eposition[1].x - eposition[0].x);
        eposition[0].y -= transform_p( -e.mouseWheelScroll.delta  , scrool_speed , eposition[1].y - eposition[0].y);
        eposition[1].x += transform_p( -e.mouseWheelScroll.delta  , scrool_speed , eposition[1].x - eposition[0].x);
        eposition[1].y += transform_p( -e.mouseWheelScroll.delta  , scrool_speed , eposition[1].y - eposition[0].y); // *** тута якиїсь лютий капець , походу аргументи мінялися місцями
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
        eposition[0].x -= transform_p( (e.mouseMove.x - last_x ) , width , eposition[1].x - eposition[0].x);
        eposition[0].y -= transform_p( (e.mouseMove.y - last_y ) , height , eposition[1].y - eposition[0].y);
        eposition[1].x -= transform_p( (e.mouseMove.x - last_x ) , width , eposition[1].x - eposition[0].x);
        eposition[1].y -= transform_p( (e.mouseMove.y - last_y ) , height , eposition[1].y - eposition[0].y);
        last_x = e.mouseMove.x ;
        last_y = e.mouseMove.y ;
    }
    if(e.type == sf::Event::MouseMoved)
    {
        last_x = e.mouseMove.x ;
        last_y = e.mouseMove.y ;
    }
}

void load_scale_factor(long double scale)
{
    eposition[0] = {-width*scale, -height*scale };
    eposition[1] = { width *scale, height*scale };
}
