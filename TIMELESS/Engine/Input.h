#pragma once
#include <vector>

class InputKey
{
public:
	enum class Keyboard
	{
		None,
		Enter,
		Escape,
		Space,
		Left,
		Up,
		Right,
		Down,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		Tilde,
		F5,
		F1,
		F2,
		F3,
		Count
	};

	InputKey(Keyboard button);
	bool IsKeyDown() const;
	bool IsKeyReleased() const;

private:
	Keyboard button;
};

class InputMouse
{
public:
	enum class Mouse
	{
		None,
		Left,
		Right,
		Middle,
		Count
	};

	InputMouse(Mouse button);
	bool IsButtonDown() const;
	bool IsButtonReleased() const;

private:
	Mouse button;
};

class Input
{
public:
	Input();
	bool IsKeyDown(InputKey::Keyboard key) const;
	bool IsButtonDown(InputMouse::Mouse button) const;
	bool IsKeyReleased(InputKey::Keyboard key) const;
	bool IsButtonReleased(InputMouse::Mouse button) const;
	void SetKeyDown(InputKey::Keyboard key, bool value);
	void SetButtonDown(InputMouse::Mouse button, bool value);
	void Update();

private:
	std::vector<bool> keyDown;
	std::vector<bool> wasKeyDown;
	std::vector<bool> buttonDown;
	std::vector<bool> wasbuttonDown;
};