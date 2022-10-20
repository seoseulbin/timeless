#pragma once

#include"../Engine/GameState.h"
#include<SFML/Graphics.hpp>
#include"../Engine/Input.h"
#include"../Engine/Texture.h"
class MainScreen : public GameState
{
public:
	

	MainScreen();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "MainScreen";
	}
private:
	sf::CircleShape shape;
	InputKey esckey;
	InputKey NextStage;
	Texture texture;
};

