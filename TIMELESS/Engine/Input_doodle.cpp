#include <doodle/input.hpp>	
#include <SFML/Graphics.hpp>
#include "Input.h"
#include "Engine.h"			// GetLogger, GetInput

InputKey::Keyboard DoodleKeyToCS230Key(sf::Keyboard::Key button)
{
	if (button == sf::Keyboard::Enter)
	{
		return InputKey::Keyboard::Enter;
	}
	else if (button == sf::Keyboard::Escape) {
		return InputKey::Keyboard::Escape;
	}
	else if (button == sf::Keyboard::Space) {
		return InputKey::Keyboard::Space;
	}
	else if (button == sf::Keyboard::Left) {
		return InputKey::Keyboard::Left;
	}
	else if (button == sf::Keyboard::Right) {
		return InputKey::Keyboard::Right;
	}
	else if (button == sf::Keyboard::Up) {
		return InputKey::Keyboard::Up;
	}
	else if (button == sf::Keyboard::Down) {
		return InputKey::Keyboard::Down;
	}
	else if (button >= sf::Keyboard::A && button <= sf::Keyboard::Z) {
		int offset = static_cast<int>(button) - static_cast<int>(doodle::KeyboardButtons::A);
		return static_cast<InputKey::Keyboard>(static_cast<int>(InputKey::Keyboard::A) + offset);
	}
	return InputKey::Keyboard::None;
}

void on_key_pressed(sf::Keyboard::Key sfmlButton) {
	InputKey::Keyboard button = DoodleKeyToCS230Key(sfmlButton);
	if (button != InputKey::Keyboard::None) {
		Engine::GetLogger().LogDebug("on_key_pressed");
		Engine::GetInput().SetKeyDown(button, true);
	}
}

void on_key_released(sf::Keyboard::Key sfmlButton) {
	InputKey::Keyboard button = DoodleKeyToCS230Key(sfmlButton);
	if (button != InputKey::Keyboard::None) {
		Engine::GetLogger().LogDebug("on_key_released");
		Engine::GetInput().SetKeyDown(button, false);
	}
}
