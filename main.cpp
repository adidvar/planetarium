#include <iostream>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include <FileFormat.h>
#include <MainWindow.h>
#include "PluginManager.h"

#include <boost/dll/import.hpp>

const size_t width = 1280 , height = 720;

/*
void load_scale_factor(number scale)
{
    cposition[0] = {-width*scale, -height*scale };
    cposition[1] = { width *scale, height*scale };
}
*/

PluginManager manager;

int main(int argc, char *argv[])
{

	mfont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
    Options opt;
    MainWindow window( manager.formats(), width, height);
    while (window) {
        window.Render();
    }
	return 0;
}

