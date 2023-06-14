#pragma once
#include <SFML/Window.hpp>
class HandleSFML
{
public:
	HandleSFML();
	void Init(const sf::Event &e);
	void HandleAllSFML();
	void Update(const sf::Event &e);

private:
	sf::Event event;
};
