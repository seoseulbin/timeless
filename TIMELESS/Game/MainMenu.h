#pragma once
#include"../Engine/GameState.h"
#include"GLShader.h"
#include"GLVertexArray.h"
#include"GLTexture.h"
#include"..\Engine\Texture.h"
#include"../Engine/Input.h"
#include"../Engine/GameObjectManager.h"
#include"Player.h"
#include"CameraView.h"
#include"../Engine/Font.h"


//class Player;


class Menu : public GameState
{
	enum class Options {
		Play,
		Tutorial,
		Option,
		Count,
	};

public:
	Menu();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "Menu";
	}


private:
	Texture test_font;
	Texture test_font2;

	Texture background;

	Texture ButtonPlay_1;
	Texture ButtonPlay_2;
	Texture ButtonTutorial_1;
	Texture ButtonTutorial_2;
	Texture ButtonOption_1;
	Texture ButtonOption_2;

	int selectedIndex;
	//InputKey next_stage_key;
	InputKey esc_key;
	InputKey reload_key;
	InputKey upKey;
	InputKey downKey;
	InputKey rightKey;
	InputKey leftKey;
	InputKey selectKey;

	InputMouse left_button;
};