#include "MainMenu.h"


Menu::Menu() : selectKey(InputKey::Keyboard::Enter), esc_key(InputKey::Keyboard::Escape), reload_key(InputKey::Keyboard::F5), 
upKey(InputKey::Keyboard::Up), downKey(InputKey::Keyboard::Down), left_button(InputMouse::Mouse::Left), leftKey(InputKey::Keyboard::Left), rightKey(InputKey::Keyboard::Right)
{

}

void Menu::Load()
{
	std::string back = "assets/images/MenuScreen_2.png";
	std::string button_p1 = "assets/images/start_off2.png";
	std::string button_p2 = "assets/images/start_on2.png";
	std::string button_t1 = "assets/images/tutorial_off2.png";
	std::string button_t2 = "assets/images/tutorial_on2.png";
	std::string button_o1 = "assets/images/option_off2.png";
	std::string button_o2 = "assets/images/option_on2.png";

	background = Texture(back);
	ButtonPlay_1 = Texture(button_p1);
	ButtonPlay_2 = Texture(button_p2);
	ButtonTutorial_1 = Texture(button_t1);
	ButtonTutorial_2 = Texture(button_t2);
	ButtonOption_1 = Texture(button_o1);
	ButtonOption_2 = Texture(button_o2);
	//Engine::GetFont().Setting("Testing Font");
	//Engine::GetFont().SetFontSize(60);
}

void Menu::Update(double)
{
	Engine::GetWindow().Clear();
	/*Engine::GetWindow().GetMousePosition();*/
	if (esc_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().Shutdown();
		Engine::GetSFXManager().Load("assets/sounds/Menu_Select_effect.wav")->Play();
	}

	if (reload_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().ReloadState();
	}
	if (upKey.IsKeyReleased())
	{
		if (selectedIndex == static_cast<int>(Options::Tutorial) || selectedIndex == static_cast<int>(Options::Option))
		{
			selectedIndex = static_cast<int>(Options::Play);
		}
		Engine::GetSFXManager().Load("assets/sounds/Menu_Select_effect.wav")->Play();
	}
	if (downKey.IsKeyReleased())
	{
		if (selectedIndex == static_cast<int>(Options::Play))
		{
			selectedIndex = static_cast<int>(Options::Tutorial);
		}
		Engine::GetSFXManager().Load("assets/sounds/Menu_Select_effect.wav")->Play();
	}
	if (leftKey.IsKeyReleased())
	{
		if (selectedIndex == static_cast<int>(Options::Option))
		{
			selectedIndex = static_cast<int>(Options::Tutorial);
		}
		Engine::GetSFXManager().Load("assets/sounds/Menu_Select_effect.wav")->Play();
	}
	if (rightKey.IsKeyReleased())
	{
		if(selectedIndex == static_cast<int>(Options::Tutorial))
		{
			
			selectedIndex = static_cast<int>(Options::Option);
		}
		Engine::GetSFXManager().Load("assets/sounds/Menu_Select_effect.wav")->Play();
	}
	if (selectKey.IsKeyReleased())
	{
		switch (selectedIndex)
		{
		case static_cast<int>(Options::Play):
			//Engine::GetGameStateManager().SetNextState("Ending Story");
			Engine::GetGameStateManager().SetNextState("Stage 1");
			//Engine::GetGameStateManager().SetNextState("TestPage2");
			break;
		case static_cast<int>(Options::Tutorial): 
			Engine::GetGameStateManager().SetNextState("Tutorial");
			break;
		case static_cast<int>(Options::Option):
			Engine::GetGameStateManager().SetNextState("Option");
			break;
		} 
		Audio* audioPtr = Engine::GetSFXManager().Load("assets/sounds/Normal_select.wav");
		audioPtr->Play();
	}  
	 
	//0.52f,-0.15f
	if (Engine::GetWindow().GetMousePosition().x >= 0.52f - ButtonPlay_2.GetNDCSize().x / 2 && Engine::GetWindow().GetMousePosition().x <= 0.52f + ButtonPlay_2.GetNDCSize().x / 2 &&
		Engine::GetWindow().GetMousePosition().y >= -0.15f  - ButtonPlay_2.GetNDCSize().y / 2 && Engine::GetWindow().GetMousePosition().y <= -0.15f + ButtonPlay_2.GetNDCSize().y / 2)
	{
		selectedIndex = static_cast<int>(Options::Play);
		if (left_button.IsButtonReleased()) 
		{
			Engine::GetGameStateManager().SetNextState("Stage 1");
		} 
	}
	//0.35f, -0.6f 
	if (Engine::GetWindow().GetMousePosition().x >= 0.35f - ButtonTutorial_2.GetNDCSize().x / 2 && Engine::GetWindow().GetMousePosition().x <= 0.35f + ButtonTutorial_2.GetNDCSize().x / 2 &&
		Engine::GetWindow().GetMousePosition().y >= -0.6f - ButtonTutorial_2.GetNDCSize().y / 2 && Engine::GetWindow().GetMousePosition().y <= -0.6f + ButtonTutorial_2.GetNDCSize().y / 2)
	{
		selectedIndex = static_cast<int>(Options::Tutorial);
		if (left_button.IsButtonReleased())
		{
			Engine::GetGameStateManager().SetNextState("Tutorial");
		}
	}
	//0.7f, -0.6f
	if (Engine::GetWindow().GetMousePosition().x >= 0.7f - ButtonOption_2.GetNDCSize().x / 2 && Engine::GetWindow().GetMousePosition().x <= 0.7f + ButtonOption_2.GetNDCSize().x / 2 &&
		Engine::GetWindow().GetMousePosition().y >= -0.6f - ButtonOption_2.GetNDCSize().y / 2 && Engine::GetWindow().GetMousePosition().y <= -0.6f + ButtonOption_2.GetNDCSize().y / 2)
	{
		selectedIndex = static_cast<int>(Options::Option);
		if (left_button.IsButtonReleased())
		{
			Engine::GetGameStateManager().SetNextState("Option");
		}
	}
}

void Menu::Unload()
{

}

void Menu::Draw()
{
	Engine::GetWindow().ClearBackground(0.4f, 0.4f, 0.4f, 255.f);
	background.Draw(mat3::build_translation({ 0, 0 }), true, 1.0f);


	//ButtonPlay_1.Draw(mat3::build_translation({ 0,0.4f }));
	//ButtonPlay_2.Draw(mat3::build_translation({ 0,0.4f }), true, 1.0f);

	//Engine::GetFont().Draw(mat3::build_translation({ 0,0 }), 1.0f);




	if (selectedIndex == static_cast<int>(Options::Play))
	{
		//ButtonPlay_2.Draw(mat3::build_translation({ 0, 0.4f }), true, 1.f);
		ButtonPlay_2.Draw(mat3::build_translation({ 0.52f,-0.15f }), true, 1.f);
		//Engine::GetLogger().LogDebug("StartButton Position" + std::to_string(0 + ButtonPlay_2.GetNDCSize().x) + " " + std::to_string(0.4f + ButtonPlay_2.GetNDCSize().y));
	}
	else
	{
		ButtonPlay_1.Draw(mat3::build_translation({ 0.52f, -0.15f }));
	}

	if (selectedIndex == static_cast<int>(Options::Tutorial))
	{
		ButtonTutorial_2.Draw(mat3::build_translation({ 0.35f, -0.6f }), true, 1.f);
	}
	else
	{
		ButtonTutorial_1.Draw(mat3::build_translation({ 0.35f, -0.6f }), true, 1.f);
	}

	if (selectedIndex == static_cast<int>(Options::Option))
	{
		ButtonOption_2.Draw(mat3::build_translation({ 0.7f, -0.6f }), true, 1.f);
	}
	else
	{
		ButtonOption_1.Draw(mat3::build_translation({ 0.7f, -0.6f }), true, 1.f);
	}

}