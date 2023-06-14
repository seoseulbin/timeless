#pragma once

#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/Input.h"
#include "../Engine/SFXManager.h"

class Option : public GameState
{
	enum class Sound_BGM
	{
		level1,
		level2,
		level3,
		level4,
		level5
	};
	enum class Sound_SFX
	{
		level1,
		level2,
		level3,
		level4,
		level5
	};

	enum class Neon_Color
	{
		red,
		yellow,
		green,
		blue,
		pink
	};

public:
	Option();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "Option";
	}

	static int neon_color;
	static string neon_file_path;
	static string neon_warning_file_path;

private:
	Texture background;
	Texture Tittle;
	Texture sound1;
	Texture sound2;
	Texture NotSelected;
	Texture Selected1;
	Texture Selected2;

	Texture selection;

	Texture BGM;
	Texture SFX;
	Texture NEON_COLOR;

	Texture Red;
	Texture Yellow;
	Texture Green;
	Texture Blue;
	Texture Pink;

	Texture option_select_item;

	InputKey exit;
	InputKey RightKey;
	InputKey leftKey;
	InputKey upKey;
	InputKey downKey;
	InputKey selectKey;

	int selected_menu_item;

	int selected_bgm;
	int selected_sfx;
	int selected_neon;

	SFXManager *audio;
	sf::Sound playsound;

	float adjustVol;

	float BGMVol = 0;
	float SFXVol = 0;

	Texture font;
};
