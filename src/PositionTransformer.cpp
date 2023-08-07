#include "PositionTransformer.h"

static const unsigned scrool_speed = 30;

number PTransformer::transform_p(number current_position, number max_position, number proect_max_pos)
{
	return current_position / max_position * proect_max_pos;
};
PTransformer::PTransformer(size_t width, size_t height) :
	width(width),
	height(height)
{
};
number PTransformer::ScaleW(number current_position) const {
	return transform_p(current_position - cposition[0].x, cposition[1].x - cposition[0].x, width);
}
number PTransformer::ScaleH(number current_position) const {
	return transform_p(current_position - cposition[0].y, cposition[1].y - cposition[0].y, height);
}
number PTransformer::Scale(number current_position) const {
	return transform_p(current_position, cposition[1].y - cposition[0].y, height);
}
void PTransformer::MoveCameraP(number x, number y) {
	cposition[0].x -= transform_p(x, width, cposition[1].x - cposition[0].x);
	cposition[0].y -= transform_p(y, height, cposition[1].y - cposition[0].y);
	cposition[1].x -= transform_p(x, width, cposition[1].x - cposition[0].x);
	cposition[1].y -= transform_p(y, height, cposition[1].y - cposition[0].y);
}
void PTransformer::ScaleCamera(number factor) {
	number dx = cposition[1].x - cposition[0].x, dy = cposition[1].y - cposition[0].y;
	cposition[0].x += dx * factor / scrool_speed;
	cposition[0].y += dy * factor / scrool_speed;
	cposition[1].x -= dx * factor / scrool_speed;
	cposition[1].y -= dy * factor / scrool_speed;
}
void PTransformer::SetScale(number dwidth, number dheight) {
	number dw = std::max(dwidth, dheight * width / height);
	cposition[0].x = -1 * dw;
	cposition[0].y = -1 * dw * height / width;
	cposition[1].x = 1 * dw;
	cposition[1].y = 1 * dw * height / width;
}
