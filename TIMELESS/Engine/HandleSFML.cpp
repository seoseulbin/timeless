#include "HandleSFML.h"
#include "Engine.h"

HandleSFML::HandleSFML()
{
}

void HandleSFML::Init(const sf::Event &e)
{
	event = e;
}

void HandleSFML::HandleAllSFML()
{
	if (event.type == sf::Event::Closed)
	{
		Engine::GetWindow().checkForClose(event);
	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			Engine::GetLogger().LogEvent("Enter Key Pressed");
			// Engine::GetInput().SetKeyDown(InputKey::Keyboard::Enter, true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			Engine::GetLogger().LogEvent("Escape Key Pressed");
			// Engine::GetInput().SetKeyDown(InputKey::Keyboard::Escape, true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Engine::GetLogger().LogEvent("Right Key Pressed");
			// Engine::GetInput().SetKeyDown(InputKey::Keyboard::Right, true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Engine::GetLogger().LogEvent("Left Key Pressed");
			// Engine::GetInput().SetKeyDown(InputKey::Keyboard::Left, true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			Engine::GetLogger().LogEvent("Up Key Pressed");
			// Engine::GetInput().SetKeyDown(InputKey::Keyboard::Up, true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			Engine::GetLogger().LogEvent("Down Key Pressed");
			// Engine::GetInput().SetKeyDown(InputKey::Keyboard::Down, true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			Engine::GetLogger().LogEvent("A key pressed");
		}
	}
}

void HandleSFML::Update(const sf::Event &e)
{
	event = e;
	HandleAllSFML();
}