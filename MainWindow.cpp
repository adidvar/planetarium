#include "MainWindow.h"

const std::unordered_map<sf::Keyboard::Key, char> MainWindow::key_map
    {
		{sf::Keyboard::Q , 'q'},
		{sf::Keyboard::W , 'w'},
		{sf::Keyboard::E , 'e'},
		{sf::Keyboard::R , 'r'},
		{sf::Keyboard::T , 't'},
		{sf::Keyboard::Y , 'y'},
		{sf::Keyboard::U , 'u'},
		{sf::Keyboard::I , 'i'},
		{sf::Keyboard::O , 'o'},
		{sf::Keyboard::P , 'p'},
		{sf::Keyboard::A , 'a'},
		{sf::Keyboard::S , 's'},
		{sf::Keyboard::D , 'd'},
		{sf::Keyboard::F , 'f'},
		{sf::Keyboard::G , 'g'},
		{sf::Keyboard::H , 'h'},
		{sf::Keyboard::J , 'j'},
		{sf::Keyboard::K , 'k'},
		{sf::Keyboard::L , 'l'},
		{sf::Keyboard::Z , 'z'},
		{sf::Keyboard::X , 'x'},
		{sf::Keyboard::C , 'c'},
		{sf::Keyboard::V , 'v'},
		{sf::Keyboard::B , 'b'},
		{sf::Keyboard::N , 'n'},
		{sf::Keyboard::M , 'm'},
		{sf::Keyboard::Num1 , '1'},
		{sf::Keyboard::Num2 , '2'},
		{sf::Keyboard::Num3 , '3'},
		{sf::Keyboard::Num4 , '4'},
		{sf::Keyboard::Num5 , '5'},
		{sf::Keyboard::Num6 , '6'},
		{sf::Keyboard::Num7 , '7'},
		{sf::Keyboard::Num8 , '8'},
		{sf::Keyboard::Num9 , '9'},
		{sf::Keyboard::Num0 , '0'},
		{sf::Keyboard::Period   , '.'},
		{sf::Keyboard::Space   , ' '}
	};

void MainWindow::EventHandle(sf::Event &e)
	{

		if(e.type == sf::Event::MouseWheelScrolled)
		{
			transformer.ScaleCamera(e.mouseWheelScroll.delta);
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
			transformer.MoveCameraP(e.mouseMove.x - last_x, e.mouseMove.y - last_y);
			last_x = e.mouseMove.x ;
			last_y = e.mouseMove.y ;
		}
		if(e.type == sf::Event::MouseMoved)
		{
			last_x = e.mouseMove.x ;
			last_y = e.mouseMove.y ;
		}
	}