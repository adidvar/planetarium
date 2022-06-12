#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <SFML/Window.hpp>
#include "init.h"

/**
 * @file
 * @brief описує методи переведення координат з екраних в реальні
 */

extern const long double width , height;

long double scale_screen_width(long double current_position);
long double scale_screen_height(long double current_position);
long double scale_screen_base(long double current_position);

long double get_real_x(unsigned screen_x);
long double get_real_y(unsigned screen_y);
long double scale_real(long double num);

void load_scale_factor(long double scale);

void movement_event(sf::Event &e, init_result &sys);

#endif // MOVEMENT_H
