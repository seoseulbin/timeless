#pragma once
#include<string>
#include"Vec2.h"
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

using namespace std;



class Window
	{
	public:
		void Init(string windowTitle, const sf::Event &e);
		void Update();
		void Resize(int newWidth, int newHeight);
		void Clear(const sf::Color& color = { 255,255,255,255 });
		bool isOpen();
		void Draw(const sf::Color& color, const sf::Drawable& drawble);
		void Draw(sf::Drawable& drawable);
		void pollEvents(sf::Event& e);
		void checkForClose(const sf::Event& e);
		void SetView(sf::View view_w);
		DataType::ivec2 GetSize()
		{
			return windowSize;
		}
	private:
		DataType::ivec2 windowSize = { 1300, 800 };
		sf::RenderWindow window;
		sf::Event window_e;
		sf::View view;
	};

