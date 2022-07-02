#pragma once

#include <SFML/Graphics.hpp>

#include "Planet.h"
#include "PlanetsThread.h"
#include "Options.h"
#include "PositionTransformer.h"
#include "Console.h"
#include "Font.h"

class MainWindow {
	PlanetsThread core;
	PTransformer transformer;
	sf::RenderWindow window;
	size_t width, height;

	bool console_e = false;
	bool text_e = false;
	bool move_mode = false;
	int last_x = 0;
	int last_y = 0;

	Console console;
	std::vector<Planet> planets;

	const static std::unordered_map<sf::Keyboard::Key, char> key_map;

	void EventHandle(sf::Event& e);
	void OnCommand(const std::vector<std::string>& argc){};

public:
	MainWindow(PlanetsController&& controller, size_t width, size_t height) :
		core(std::move(controller)),
		transformer(width, height),
		window(sf::VideoMode(width, height), "Main"),
		width(width),
		height(height),
		console(std::bind(&MainWindow::OnCommand, this, std::placeholders::_1))
	{
		window.setFramerateLimit(60);
		core.SetFrameTime(PlanetsThread::duration{ 3600*24 });
	}

	operator bool() {
		return window.isOpen();
	}

	void DrawText(std::string txt, sf::Color color, size_t size, sf::Vector2f position = {0,0}, sf::Vector2f relative_origin = {0,0}) {
		sf::Text text(txt, mfont, size);
		text.setFillColor(color);
		text.setStyle(sf::Text::Bold);

		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.width * relative_origin.x, textRect.height * relative_origin.y);
		text.setPosition(position.x, position.y);
		window.draw(text);
	}


	void Render() {
		//load_scale_factor(sys.default_scale);
	//    Console console(sys,mutex);
		std::string time_dump;

		sf::Event e;
		while (window.pollEvent(e))
		{
			if (!console_e) {
				EventHandle(e);
				if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::T)
					text_e = !text_e;
				if (e.type == sf::Event::KeyPressed && console_e == true && key_map.count(e.key.code) == 1)
					console.PushLetter(key_map.at(e.key.code));
				if (e.type == sf::Event::KeyPressed && console_e == true && e.key.code == sf::Keyboard::Backspace)
					console.BackSpace();
				if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter)
				{
					if (console_e)
						console.Enter();
					console_e = !console_e;
				}
				if (e.type == sf::Event::Closed)
					window.close();
			}

			window.display();
			window.clear();

			if (core.IsLoading()) {
				DrawText(std::to_string(core.GetProgress()), sf::Color::Red, 40, { width / 2.0f , height / 2.0f }, { 0.5 , 0.5 });
				return;
			}

			if (core.SlowDownWarning())
				DrawText("Slow down error", sf::Color::Red, 40, { width / 2.0f, height / 2.0f }, { 0.5 , 1.35 });

			DrawText(std::to_string(core.GetSimulationFrequency()), sf::Color::Red, 20, { static_cast<float>(width)  , 0 }, { 1 , 0 });

			planets = std::move(core.LoadState());

			for (auto&& p : planets)
			{
				auto pos = p.GetPositionV();
				number radius = std::max<number>(1.0, transformer.Scale(p.GetRadius()));
				sf::CircleShape shape(radius, std::min<number>(radius + 4, 30));
				shape.setOrigin(radius, radius);
				sf::Vector2f after(transformer.ScaleW(pos.x),
					transformer.ScaleH(pos.y));
				if (after.x < 0.0 || after.x > width || after.y < 0.0 || after.y > height)
					continue;
				shape.setPosition(after);
				window.draw(shape);
				auto radius_transform = [=]() -> number {
					if (radius > 15)
						return radius;
					return 15;
				};
				if (text_e)
					DrawText(p.name, sf::Color::Red, radius_transform(), { after.x, after.y - (float)radius }, { 0.5 , 1.35 });
			}
			DrawText(core.GetTimeDump(), sf::Color::White, 20);

			if (console_e) 
				DrawText(console.Text(), sf::Color::White, 20, { 0, 400 });
		}

	}
};