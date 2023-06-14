// #include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Input.h"
#include "Engine.h" // GetLogger, GetInput

InputKey::Keyboard SFMLkeyToEngine([[maybe_unused]] sf::Keyboard::Key button)
{
	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	//{
	//	return InputKey::Keyboard::Enter;
	// }
	if (button == sf::Keyboard::Enter)
	{
		return InputKey::Keyboard::Enter;
	}
	else if (button == sf::Keyboard::Escape)
	{
		return InputKey::Keyboard::Escape;
	}
	else if (button == sf::Keyboard::Space)
	{
		return InputKey::Keyboard::Space;
	}
	else if (button == sf::Keyboard::Left)
	{
		return InputKey::Keyboard::Left;
	}
	else if (button == sf::Keyboard::Right)
	{
		return InputKey::Keyboard::Right;
	}
	else if (button == sf::Keyboard::Up)
	{
		return InputKey::Keyboard::Up;
	}
	else if (button == sf::Keyboard::Down)
	{
		return InputKey::Keyboard::Down;
	}
	else if (button >= sf::Keyboard::A && button <= sf::Keyboard::Z)
	{
		int offset = static_cast<int>(button) - static_cast<int>(sf::Keyboard::A);
		return static_cast<InputKey::Keyboard>(static_cast<int>(InputKey::Keyboard::A) + offset);
	}
	return InputKey::Keyboard::None;
}

// bool sf::Keyboard::isKeyPressed(Key key)
//{
//	InputKey::Keyboard button = SFMLkeyToEngine(key);
//	if (button != InputKey::Keyboard::None) {
//		Engine::GetLogger().LogDebug("on_key_pressed");
//		Engine::GetInput().SetKeyDown(button, true);
//	}
//	return true;
// }
// InputKey::Keyboard button = SFMLkeyToEngine(sfmlButton);
// if (button != InputKey::Keyboard::None) {
//	Engine::GetLogger().LogDebug("on_key_pressed");
//	Engine::GetInput().SetKeyDown(button, true);
// }
// return true;

bool isKeyPressed(sf::Keyboard::Key key)
{
	InputKey::Keyboard button = SFMLkeyToEngine(key);
	if (button != InputKey::Keyboard::None)
	{
		Engine::GetLogger().LogDebug("KeyPressed");
		Engine::GetInput().SetKeyDown(button, true);
		return true;
	}
	return false;
}

void on_key_released(sf::Keyboard::Key sfmlButton)
{
	InputKey::Keyboard button = SFMLkeyToEngine(sfmlButton);
	if (button != InputKey::Keyboard::None)
	{
		Engine::GetLogger().LogDebug("on_key_released");
		Engine::GetInput().SetKeyDown(button, false);
	}
}
