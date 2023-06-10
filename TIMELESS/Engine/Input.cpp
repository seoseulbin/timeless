#include"Input.h"
#include"Engine.h"


InputKey::InputKey(Keyboard _button) : button(_button) {}


bool InputKey::IsKeyDown() const
{
	return Engine::GetInput().IsKeyDown(InputKey::button);
	//return Engine::GetInput().IsKeyDown(InputKey::button_2);
}

bool InputKey::IsKeyReleased() const
{
	return Engine::GetInput().IsKeyReleased(InputKey::button);
}

InputMouse::InputMouse(Mouse _button) : button(_button){}

bool InputMouse::IsButtonDown() const
{
	return Engine::GetInput().IsButtonDown(InputMouse::button);
}

bool InputMouse::IsButtonReleased() const
{
	return Engine::GetInput().IsButtonReleased(InputMouse::button);
}

Input::Input()
{
	keyDown.resize(static_cast<int>(InputKey::Keyboard::Count));
	wasKeyDown.resize(static_cast<int>(InputKey::Keyboard::Count));
	buttonDown.resize(static_cast<int>(InputMouse::Mouse::Count));
	wasbuttonDown.resize(static_cast<int>(InputMouse::Mouse::Count));
}

void Input::Update()
{
	wasKeyDown = keyDown;
	wasbuttonDown = buttonDown;
}

bool Input::IsKeyDown(InputKey::Keyboard key) const
{
	return keyDown[static_cast<int>(key)];
}

bool Input::IsButtonDown(InputMouse::Mouse button) const
{
	return buttonDown[static_cast<int>(button)];
}


bool Input::IsKeyReleased(InputKey::Keyboard key) const
{
	return wasKeyDown[static_cast<int>(key)] == true && keyDown[static_cast<int>(key)] == false;
}


bool Input::IsButtonReleased(InputMouse::Mouse button) const
{
	return wasbuttonDown[static_cast<int>(button)] == true && buttonDown[static_cast<int>(button)] == false;
}

void Input::SetKeyDown(InputKey::Keyboard key, bool value)
{
	keyDown[static_cast<int>(key)] = value;
}

void Input::SetButtonDown(InputMouse::Mouse button, bool value)
{
	buttonDown[static_cast<int>(button)] = value;
}