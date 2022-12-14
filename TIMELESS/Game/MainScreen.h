//#pragma once
//
//#include"../Engine/GameState.h"
//#include<SFML/Graphics.hpp>
//#include"../Engine/Input.h"
//#include"../Engine/Texture.h"
//#include"../Engine/Font.h"
//class MainScreen : public GameState
//{
//public:
//	enum class Options {
//		Play,
//		Special,
//		Tutorial,
//		Option,
//		Count,
//	};
//
//	MainScreen();
//	void Load() override;
//	void Update(double) override;
//	void Unload() override;
//	void Draw() override;
//
//	string GetName() override
//	{
//		return "MainScreen";
//	}
//private:
//	struct OptionData
//	{
//		std::string text;
//		//DataType::vec2 positionPercent;
//		Texture texture;
//		bool isHighlighted;
//	};
//	void Render(OptionData& data);
//	static OptionData optionData[static_cast<int>(MainScreen::Options::Count)];
//	int selectedIndex;
//	Texture test_texture;
//	InputKey esckey;
//	InputKey upKey;
//	InputKey downKey;
//	InputKey selectKey;
//	Texture texture;
//	Texture Neon_title;
//};
//
