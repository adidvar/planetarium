#include <iostream>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "FileFormat.h"
#include "MainWindow.h"

const size_t width = 1280 , height = 720;

/*
void load_scale_factor(number scale)
{
    cposition[0] = {-width*scale, -height*scale };
    cposition[1] = { width *scale, height*scale };
}
*/

int main()
{
	mfont.loadFromFile("font.otf");
    FileFormat* fileformat = new OldFileFormat();
    auto system = fileformat->Load("solarsystem.oldsystem");

    Options opt;
    MainWindow window(std::move(system), width, height);
    while (window) {
        window.Render();
    }
}

