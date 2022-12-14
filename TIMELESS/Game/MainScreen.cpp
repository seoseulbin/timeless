//#include "MainScreen.h"
//#include"../Engine/Engine.h"
//#include"Screens.h"
//#include"../Engine/Fonts.h"
//#include<SFML/Graphics.hpp>
//
//
//
//MainScreen::MainScreen() : esckey(InputKey::Keyboard::Escape), upKey(InputKey::Keyboard::Up), downKey(InputKey::Keyboard::Down), selectKey(InputKey::Keyboard::Enter)
//, selectedIndex(static_cast<int>(Options::Play)) {}
//
//void MainScreen::Load()
//{
//	std::string texturePath = "assets/main.png";
//	texture.Load(texturePath);
//	//test_font_image.loadFromFile("assets/font.png");
//	//big_text.create(200, 68);
//	//test_font_2.loadFromImage(test_font_image, sf::IntRect({ 106,1,33,68 }));
//	//test_font_1.loadFromImage(test_font_image, sf::IntRect({ 139,1,33,68 }));
//	//big_text.update(test_font_2);
//	//big_text.update(test_font_1,33,0);
//	selectedIndex = static_cast<int>(Options::Play);
//	for (OptionData& data : optionData)
//	{
//		Render(data);
//	}
//	Neon_title.Load(Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Neon Timeless"));
//}
//
//void MainScreen::Update(double)
//{
//	if (esckey.IsKeyDown() == true)
//	{
//		Engine::GetGameStateManager().Shutdown();
//	}
//	if (upKey.IsKeyReleased())
//	{
//		if (selectedIndex == static_cast<int>(Options::Play))
//		{
//			selectedIndex = static_cast<int>(Options::Play);
//		}
//		else
//		{
//			selectedIndex--;
//			optionData[selectedIndex + 1].isHighlighted = false;
//			optionData[selectedIndex].isHighlighted = true;
//		}
//	}
//	if (downKey.IsKeyReleased())
//	{
//		if (selectedIndex == static_cast<int>(Options::Option))
//		{
//			selectedIndex = static_cast<int>(Options::Option);
//		}
//		else
//		{
//			selectedIndex++;
//			optionData[selectedIndex - 1].isHighlighted = false;
//			optionData[selectedIndex].isHighlighted = true;
//		}
//	}
//	if (selectKey.IsKeyDown())
//	{
//		switch (selectedIndex)
//		{
//		case static_cast<int>(Options::Play):
//			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Stage1));
//			break;
//		case static_cast<int>(Options::Special):
//			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Special));
//			break;
//		case static_cast<int>(Options::Tutorial):
//			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Tutorial));
//			break;
//		case static_cast<int>(Options::Option):
//			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Option));
//			break;
//		}
//	}
//
//}
//
//void MainScreen::Unload()
//{
//
//}
//
//void MainScreen::Draw()
//{
//	DataType::fvec2 winSize = Engine::GetWindow().GetSize();
//	texture.Draw(DataType::TranslateMatrix(winSize / 2));
//	//Neon_title.Draw(DataType::TranslateMatrix(winSize / 2) * DataType::ScaleMatrix(DataType::fvec2{ 1.f,1.f }), true); // ture�� �����ϸ� �׸��� ǥ��.
//	optionData[static_cast<int>(MainScreen::Options::Play)].texture.Draw(DataType::TranslateMatrix(DataType::fvec2{ winSize.x / 2, winSize.y * 0.67f }),
//		optionData[static_cast<int>(MainScreen::Options::Play)].isHighlighted, true);
//	optionData[static_cast<int>(MainScreen::Options::Special)].texture.Draw(DataType::TranslateMatrix(DataType::fvec2{ winSize.x / 2, winSize.y * 0.75f }),
//		optionData[static_cast<int>(MainScreen::Options::Special)].isHighlighted, true);
//	optionData[static_cast<int>(MainScreen::Options::Tutorial)].texture.Draw(DataType::TranslateMatrix(DataType::fvec2{ winSize.x / 2, winSize.y * 0.83f }),
//		optionData[static_cast<int>(MainScreen::Options::Tutorial)].isHighlighted, true);
//	optionData[static_cast<int>(MainScreen::Options::Option)].texture.Draw(DataType::TranslateMatrix(DataType::fvec2{ winSize.x / 2, winSize.y * 0.91f }),
//		optionData[static_cast<int>(MainScreen::Options::Option)].isHighlighted, true);
//
//	// ���� ����� ��ο��� �׸��ڰ� ǥ�ð� �� �ȵǴ� ����� �׸��� ������ ���� �ְ�� �÷�����.
//	// texture.Draw(displayMatrix, isHighlighted, drawShadow)
//	// ��ο� �Լ� ������ ���� ������ ���̶���Ʈ ������� �ΰ� ������
//	// isHighlighted = true �Ͻ� ȭ��Ʈ�� ǥ��, false �Ͻ� ȸ������ ǥ��
//	// drawShadow = true �Ͻ� �׸��� ǥ��, false �Ͻ� ���������� ǥ��(���� �ΰ��� ������ ������)
//}
//
//void MainScreen::Render(OptionData& data)
//{
//	data.texture.Load(Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(data.text));
//}
//
//MainScreen::OptionData MainScreen::optionData[static_cast<int>(MainScreen::Options::Count)] =
//{
//	{"Play",  {}, true},
//	{"Special",  {}, false},
//	{"Tutorial",  {}, false},
//	{"Option",  {}, false},
//};