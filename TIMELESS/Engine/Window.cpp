#include "Window.h"
#include "Engine.h"

#include<SFML/Window.hpp>

void Window::Init(string windowTitle, const sf::Event& e)
{
	window.create(sf::VideoMode(windowSize.x, windowSize.y), windowTitle);
	//window.setView(view);
	//view = window.getDefaultView();
	//window.setView(view);
	window_e = e;
	//window.setVerticalSyncEnabled(true);
}

void Window::Update()
{
	Window::pollEvents(window_e);
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	//Engine::GetLogger().LogEvent(std::to_string(view.getCenter().y));
	//Engine::GetLogger().LogEvent(std::to_string(pixelPos.x));
	//Engine::GetLogger().LogEvent(std::to_string(worldPos.x));
	window.display();
}
void Window::Draw(const sf::Color& color, const sf::Drawable& drawble)
{
	Engine::GetWindow().Clear(color);
	window.draw(drawble);
}
void Window::Draw(sf::Drawable& drawable)
{
	window.draw(drawable);
}

bool Window::isOpen()
{
	return window.isOpen();
}

void Window::Resize(int newWidth, int newHeight)
{
	windowSize.x = newWidth;
	windowSize.y = newHeight;
}

void Window::Clear(const sf::Color& color)
{
	window.clear(color);
}

void Window::checkForClose(const sf::Event& e)
{
	if (e.type == sf::Event::Closed)
	{
		Engine::GetGameStateManager().SetGameHasEnded();
		window.close();
	}
}

void Window::pollEvents(sf::Event& ea)
{
	while (window.pollEvent(ea))
	{
		Engine::GetHandle().Update(ea);
	}
}

void Window::SetView(sf::View view_w)
{
	window.setView(view_w);
}