#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <SFML/Window.hpp>

extern const long double width , height;

long double scale_screen_width(long double current_position);
long double scale_screen_height(long double current_position);
long double scale_screen_base(long double current_position);

void load_scale_factor(long double scale);

void movement_event(sf::Event &e);

#endif // MOVEMENT_H
