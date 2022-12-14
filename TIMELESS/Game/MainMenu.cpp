#include "MainMenu.h"


Menu::Menu() : selectKey(InputKey::Keyboard::Enter), esc_key(InputKey::Keyboard::Escape), reload_key(InputKey::Keyboard::F5), upKey(InputKey::Keyboard::Up), downKey(InputKey::Keyboard::Down)
{

}

void Menu::Load()
{
	std::string back = "assets/images/MAIN.png";
	std::string button_p1 = "assets/images/start1_button_edit.png";
	std::string button_p2 = "assets/images/start2_button_edit.png";
	std::string button_t1 = "assets/images/tutorial1_button_edit.png";
	std::string button_t2 = "assets/images/tutorial2_button_edit.png";
	std::string button_o1 = "assets/images/option1_button_edit.png";
	std::string button_o2 = "assets/images/option2_button_edit.png";

	background = Texture(back);
	ButtonPlay_1 = Texture(button_p1);
	ButtonPlay_2 = Texture(button_p2);
	ButtonTutorial_1 = Texture(button_t1);
	ButtonTutorial_2 = Texture(button_t2);
	ButtonOption_1 = Texture(button_o1);
	ButtonOption_2 = Texture(button_o2);
}

void Menu::Update(double)
{
	Engine::GetWindow().Clear();

	if (esc_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().Shutdown();
	}

	if (reload_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().ReloadState();
	}
	if (upKey.IsKeyReleased())
	{
		if (selectedIndex == static_cast<int>(Options::Play))
		{
			selectedIndex = static_cast<int>(Options::Play);
		}
		else
		{
			selectedIndex--;
		}
	}
	if (downKey.IsKeyReleased())
	{
		if (selectedIndex == static_cast<int>(Options::Option))
		{
			selectedIndex = static_cast<int>(Options::Option);
		}
		else
		{
			selectedIndex++;
		}
	}
	if (selectKey.IsKeyReleased())
	{
		switch (selectedIndex)
		{
		case static_cast<int>(Options::Play):
			Engine::GetGameStateManager().SetNextState("Stage 1");
			break;
		case static_cast<int>(Options::Tutorial):
			Engine::GetGameStateManager().SetNextState("Tutorial");
			break;
		case static_cast<int>(Options::Option):
			Engine::GetGameStateManager().SetNextState("Option");
			break;
		}
	}
}

void Menu::Unload()
{
	
}

void Menu::Draw()
{
	Engine::GetWindow().ClearBackground(0.4f, 0.4f, 0.4f, 255.f);
	background.Draw(mat3::build_translation({ 0, 0 }), true, 0.8f);
	//ButtonPlay_1.Draw(mat3::build_translation({ 0,0.4f }));
	//ButtonPlay_2.Draw(mat3::build_translation({ 0,0.4f }), true, 1.0f);

	if (selectedIndex == static_cast<int>(Options::Play))
	{
		//ButtonPlay_2.Draw(mat3::build_translation({ 0, 0.4f }), true, 1.f);
		ButtonPlay_2.Draw(mat3::build_translation({ 0,0.4f }), true, 1.f);
	}
	else
	{
		ButtonPlay_1.Draw(mat3::build_translation({ 0, 0.4f }));
	}

	if (selectedIndex == static_cast<int>(Options::Tutorial))
	{
		ButtonTutorial_2.Draw(mat3::build_translation({ 0, 0 }), true, 1.f);
	}
	else
	{
		ButtonTutorial_1.Draw(mat3::build_translation({ 0, 0 }), true, 1.f);
	}

	if (selectedIndex == static_cast<int>(Options::Option))
	{
		ButtonOption_2.Draw(mat3::build_translation({ 0, -0.4f }), true, 1.f);
	}
	else
	{
		ButtonOption_1.Draw(mat3::build_translation({ 0, -0.4f }), true, 1.f);
	}

}