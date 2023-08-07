#pragma once

#include <vector>
#include <memory>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "Planet.h"
#include "PlanetsThread.h"
#include "Options.h"
#include "PositionTransformer.h"
#include "Console.h"
#include "Font.h"
#include "FileFormat.h"
#include "Settings.h"
	
const extern std::unordered_map<sf::Keyboard::Key, char> key_map;
class MainWindow {
	std::unique_ptr<PlanetsThread> core;
	PTransformer transformer;
	sf::RenderWindow window;
	size_t width, height;

	bool console_e = false;
	bool text_e = false;
	bool move_mode = false;
	int last_x = 0;
	int last_y = 0;

	Console console;
	const std::vector<FileFormat*> &file_formats;
	std::vector<Planet> planets;
	std::vector<std::filesystem::path> filenames;

	void EventHandle(sf::Event& e);
	void OnCommand(const std::vector<std::string>& argc) {

		if (argc.front() == "stop" || argc.front() == "pause") {
			core->Stop();
		}
		if (argc.front() == "start" || argc.front() == "play") {
			core->Play(std::stof(argc[1]));
		}
		if (argc.front() == "skip" || argc.front() == "playto") {
			core->PlayFor(std::stof(argc[1]));
		}
		if (argc.front() == "skipuntil" || argc.front() == "playuntil") {
			core->PlayUntil(std::stof(argc[1]));
		}
		if (argc.front() == "precision" || argc.front() == "p") {
			core->SetPrecision(PlanetsThread::duration(std::stof(argc[1])));
		}
	};

public:
	MainWindow(const std::vector<FileFormat*>& file_formats, size_t width, size_t height) :
		file_formats(file_formats),
		transformer(width, height),
		window(sf::VideoMode(width, height), "Main"),
		width(width),
		height(height),
		console(std::bind(&MainWindow::OnCommand, this, std::placeholders::_1))
	{
		window.setFramerateLimit(60);
	}

	operator bool() {
		return window.isOpen();
	}

	void DrawText(std::string txt, sf::Color color, size_t size, sf::Vector2f position = { 0,0 }, sf::Vector2f relative_origin = { 0,0 }) {
		sf::Text text(txt, mfont, size);
		text.setFillColor(color);
		text.setStyle(sf::Text::Bold);

		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.width * relative_origin.x, textRect.height * relative_origin.y);
		text.setPosition(position.x, position.y);
		window.draw(text);
	}
	void RenderFileMenu() {
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::MouseButtonReleased) {
				auto name = filenames[e.mouseButton.y / 25];
				for (auto addon : file_formats) {
					auto formats = addon->Formats();
					if (std::count(formats.begin(), formats.end(), name.extension()) == 1) {
						core.reset(new PlanetsThread(addon->Load(name.string())));

						auto state = core->LoadState();
						auto x = std::minmax_element(state.begin(), state.end(), [](const Planet& t1, const Planet& t2) {return t1.x < t2.x; });
						auto y = std::minmax_element(state.begin(), state.end(), [](const Planet& t1, const Planet& t2) {return t1.y < t2.y; });
						auto dx = x.second->x - x.first->x;
						auto dy = y.second->y - y.first->y;

						transformer.SetScale(dx, dy);

						return;
					}
				}
			}
			if (e.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		filenames.clear();
		for (auto&& file : std::filesystem::directory_iterator(std::filesystem::current_path()))
			if (file.is_regular_file())
				for (auto&& addon : file_formats) {
					auto&& formats = addon->Formats();
					if (std::count(formats.begin(), formats.end(), file.path().extension()) == 1)
						filenames.push_back(file.path().string());
				}
		for (size_t i = 0; i < filenames.size(); i++) {
			DrawText(filenames[i].filename().string(), sf::Color::Yellow, 20, { width / 2.0f, i * 25.0f }, { .5f, 0 });
		}


		window.display();
	}

	void Render()
	{

		if (core.get() == nullptr) {
			RenderFileMenu();
			return;
		}

		std::string time_dump;

		sf::Event e;
		while (window.pollEvent(e))
		{

			if (!console_e) {
				EventHandle(e);
				if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::T)
					text_e = !text_e;
			}
			else {
				if (e.type == sf::Event::KeyPressed && console_e == true && key_map.count(e.key.code) == 1)
					console.PushLetter(key_map.at(e.key.code));
				if (e.type == sf::Event::KeyPressed && console_e == true && e.key.code == sf::Keyboard::Backspace)
					console.BackSpace();
			}
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter)
			{
				if (console_e)
					console.Enter();
				console_e = !console_e;
			}
			if (e.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		if (core->IsLoading()) {
			DrawText(std::to_string(core->GetProgress()), sf::Color::Red, 40, { width / 2.0f , height / 2.0f }, { 0.5 , 0.5 });
			window.display();
			return;
		}

		DrawText(core->GetTimeDump(), sf::Color::White, 20);

		if (console_e)
			DrawText(console.Text(), sf::Color::White, 20, { 0, 400 });


		if (core->SlowDownWarning())
			DrawText("Slow down error", sf::Color::Red, 40, { width / 2.0f, height / 2.0f }, { 0.5 , 1.35 });

		DrawText(std::to_string(core->GetSpeed()), sf::Color::Red, 20, { static_cast<float>(width)  , 0 }, { 1 , 0 });

		RenderPlanets();

		window.display();
	}
private:
	void RenderPlanets() {
		planets = std::move(core->LoadState());

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
	}

};