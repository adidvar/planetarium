#pragma once

#include "Number.h"

constexpr unsigned scrool_speed = 30;

class PTransformer {
    size_t width, height;
    struct position
	{
		number x , y;
	} cposition[2] = {{-(number)width, -(number)height },{(number)width,(number)height}};

	constexpr static number transform_p(number current_position , number max_position , number proect_max_pos)
	{
		return current_position / max_position * proect_max_pos;
	};
public:
    PTransformer(size_t width, size_t height) :
        width(width),
        height(height) {};
    number ScaleW(number current_position) const {
        return transform_p(current_position - cposition[0].x , cposition[1].x-cposition[0].x , width );
    }
    number ScaleH(number current_position) const {
		return transform_p(current_position - cposition[0].y , cposition[1].y-cposition[0].y , height );
    }
    number Scale(number current_position) const {
		return transform_p(current_position , cposition[1].y-cposition[0].y , height );
    }
    void MoveCameraP(number x, number y) {
        cposition[0].x -= transform_p( x , width , cposition[1].x - cposition[0].x);
        cposition[0].y -= transform_p( y , height , cposition[1].y - cposition[0].y);
        cposition[1].x -= transform_p( x , width , cposition[1].x - cposition[0].x);
        cposition[1].y -= transform_p( y , height , cposition[1].y - cposition[0].y);
    }
    void ScaleCamera(number factor) {
        number dx = cposition[1].x - cposition[0].x, dy = cposition[1].y - cposition[0].y;
        cposition[0].x += dx * factor / scrool_speed;
        cposition[0].y += dy * factor / scrool_speed;
		cposition[1].x -= dx * factor / scrool_speed;
        cposition[1].y -= dy * factor / scrool_speed;
    }
};
