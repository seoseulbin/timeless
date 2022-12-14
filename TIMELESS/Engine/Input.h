#pragma once
#include<vector>

class InputKey {
public:
	enum class Keyboard {
		None, Enter, Escape, Space, Left, Up, Right, Down,
		A, B, C, D, E, F, G, H, I, J,
		K, L, M, N, O, P, Q, R, S, T,
		U, V, W, X, Y, Z, Tilde, F5,
		Count
	};

	InputKey(Keyboard button);
	bool IsKeyDown() const;
	bool IsKeyReleased() const;
private:
	Keyboard button;
};

class Input {
public:
	Input();
	bool IsKeyDown(InputKey::Keyboard key) const;
	bool IsKeyReleased(InputKey::Keyboard key) const;
	void SetKeyDown(InputKey::Keyboard key, bool value);
	void Update();
private:
	std::vector<bool> keyDown;
	std::vector<bool> wasKeyDown;
};