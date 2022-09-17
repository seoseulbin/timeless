#include"Input.h"
#include"Engine.h"


InputKey::InputKey(Keyboard _button) : button(_button) {}

bool InputKey::IsKeyDown() const
{
	return Engine::GetInput().IsKeyDown(InputKey::button);
}

bool InputKey::IsKeyReleased() const
{
	return Engine::GetInput().IsKeyReleased(InputKey::button);
}

Input::Input()
{
	keyDown.resize(static_cast<int>(InputKey::Keyboard::Count));
	wasKeyDown.resize(static_cast<int>(InputKey::Keyboard::Count));
}

void Input::Update()
{
	wasKeyDown = keyDown;
}

bool Input::IsKeyDown(InputKey::Keyboard key) const
{
	return keyDown[static_cast<int>(key)];
}

bool Input::IsKeyReleased(InputKey::Keyboard key) const
{
	return wasKeyDown[static_cast<int>(key)] == true && keyDown[static_cast<int>(key)] == false;
}

void Input::SetKeyDown(InputKey::Keyboard key, bool value)
{
	keyDown[static_cast<int>(key)] = value;
}