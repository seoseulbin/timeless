#include "Option.h"

#include "../Engine/Input.h"
#include "../Engine/Input.h"
#include "../Engine/Input.h"
#include "../Engine/Input.h"
#include"..\Engine\Engine.h"

int Option::neon_color = 2;
string Option::neon_file_path = "assets/data/neon_yellow.spt";
string Option::neon_warning_file_path = "assets/data/neon_warning.spt";

Option::Option() : exit(InputKey::Keyboard::Escape), adjustVol(0.f), selectKey(InputKey::Keyboard::Enter),
RightKey(InputKey::Keyboard::Right), leftKey(InputKey::Keyboard::Left), upKey(InputKey::Keyboard::Up), downKey(InputKey::Keyboard::Down)
{
	selected_bgm = 2;
	selected_sfx = 2;
	selected_neon = 1;
	selected_menu_item = 0;
}

void Option::Load()
{
	std::string back = "assets/images/OptionScreen.png";
	std::string soundTittle = "assets/images/sound.png";

	std::string soundEno1 = "assets/images/sound_emo.png";
	std::string soundEno2 = "assets/images/sound_emo2.png";

	std::string notSelected = "assets/images/no_sound.png";
	std::string selectedS1 = "assets/images/sound_selected.png";
	std::string selectedS2 = "assets/images/sound_selected2.png";

	std::string selection_dir = "assets/images/option_select.png";

	std::string BGM_ = "assets/images/bgm.png";
	std::string SFX_ = "assets/images/sfx.png";
	std::string NEON_COLOR_ = "assets/images/neon_color.png";

	std::string RED = "assets/images/red.png";
	std::string YELLOW = "assets/images/yellow.png";
	std::string GREEN = "assets/images/green.png";
	std::string BLUE = "assets/images/blue.png";
	std::string PINK = "assets/images/pink.png";

	std::string select_item = "assets/images/black_outline_choose_option.png";

	background = Texture(back);
	Tittle = Texture(soundTittle);

	sound1 = Texture(soundEno1);
	sound2 = Texture(soundEno2);

	NotSelected = Texture(notSelected);
	Selected1 = Texture(selectedS1);
	Selected2 = Texture(selectedS2);

	selection = Texture(selection_dir);

	BGM = Texture(BGM_);
	SFX = Texture(SFX_);
	NEON_COLOR = Texture(NEON_COLOR_);

	Red = Texture(RED);
	Yellow = Texture(YELLOW);
	Green = Texture(GREEN);
	Blue = Texture(BLUE);
	Pink = Texture(PINK);

	option_select_item = Texture(select_item);

	BGMVol = 0.0f;
	SFXVol = 0.0f;
}

void Option::Update(double)
{
	Engine::GetWindow().Clear();
	if (exit.IsKeyReleased())
	{
		Engine::GetGameStateManager().SetNextState("Menu");
		//Audio* audioPtr = Engine::GetSFXManager().Load("assets/sounds/Esc_key_select.wav");
		//audioPtr->Play();
		Engine::GetSFXManager().Load("assets/sounds/Esc_key_select.wav")->Play();
		neon_color = selected_neon + 1;
		switch (neon_color)
		{
		case 1:
			neon_file_path = "assets/data/neon_red.spt";
			neon_warning_file_path = "assets/data/neon_warning_red.spt";
			break;
		case 2:
			neon_file_path = "assets/data/neon_yellow.spt";
			neon_warning_file_path = "assets/data/neon_warning.spt";
			break;
		case 3:

			neon_file_path = "assets/data/neon_green.spt";
			neon_warning_file_path = "assets/data/neon_warning_green.spt";
			break;
		case 4:

			neon_file_path = "assets/data/neon_blue.spt";
			neon_warning_file_path = "assets/data/neon_warning_blue.spt";
			break;
		case 5:

			neon_file_path = "assets/data/neon_pink.spt";
			neon_warning_file_path = "assets/data/neon_warning_pink.spt";
			break;
		default:
			break;
		}
	}
	if (upKey.IsKeyReleased())
	{
		if (selected_menu_item == 0)
		{
			selected_menu_item = 0;
		}
		else
		{
			selected_menu_item -= 1;
		}
		Engine::GetSFXManager().Load("assets/sounds/Menu_Select_effect.wav")->Play();
	}

	if (downKey.IsKeyReleased())
	{
		if (selected_menu_item == 2)
		{
			selected_menu_item = 2;
		}
		else
		{
			selected_menu_item += 1;
		}
		Engine::GetSFXManager().Load("assets/sounds/Menu_Select_effect.wav")->Play();
	}

	if (RightKey.IsKeyReleased())
	{
		if (selected_menu_item == 0)
		{
			if (selected_bgm == static_cast<int>(Sound_BGM::level5))
			{
				selected_bgm = static_cast<int>(Sound_BGM::level5);
			}
			else
			{
				selected_bgm++;
			}
			Engine::GetSFXManager().BGMController((selected_bgm) * 11.f, true);
		}

		else if (selected_menu_item == 1)
		{
			if (selected_sfx == static_cast<int>(Sound_SFX::level5))
			{
				selected_sfx = static_cast<int>(Sound_SFX::level5);
			}
			else
			{
				selected_sfx++;
			}
			Engine::GetSFXManager().SEController((selected_sfx) * 11.f, false);
		}

		else if (selected_menu_item == 2)
		{
			if (selected_neon == static_cast<int>(Neon_Color::pink))
			{
				selected_neon = static_cast<int>(Neon_Color::pink);
			}
			else
			{
				selected_neon++;
			}
		}
		Engine::GetSFXManager().Load("assets/sounds/Menu_Select_effect.wav")->Play();
	}

	if (leftKey.IsKeyReleased())
	{
		if (selected_menu_item == 0)
		{
			if (selected_bgm == static_cast<int>(Sound_BGM::level1))
			{
				selected_bgm = static_cast<int>(Sound_BGM::level1);
			}
			else
			{
				selected_bgm--;
			}
			Engine::GetSFXManager().BGMController((selected_bgm) * 11.f, true);
		}

		else if (selected_menu_item == 1)
		{
			if (selected_sfx == static_cast<int>(Sound_SFX::level1))
			{
				selected_sfx = static_cast<int>(Sound_SFX::level1);
			}
			else
			{
				selected_sfx--;
			}
			Engine::GetSFXManager().SEController((selected_sfx) * 11.f, false);
		}

		else if (selected_menu_item == 2)
		{
			if (selected_neon == static_cast<int>(Neon_Color::red))
			{
				selected_neon = static_cast<int>(Neon_Color::red);
			}
			else
			{
				selected_neon--;
			}
		}
		Engine::GetSFXManager().Load("assets/sounds/Menu_Select_effect.wav")->Play();
	}

}

void Option::Unload()
{
	selected_menu_item = 0;
	ClearGSComponent();
}

void Option::Draw()
{
	background.Draw(mat3::build_translation({ 0, 0 }), true, 0.5f);
	Tittle.Draw(mat3::build_translation({ 0, 0.6f }), true, 1.f);

	BGM.Draw(mat3::build_translation({ -0.7f, 0.2f }), true, 1.f);
	sound1.Draw(mat3::build_translation({ -0.43f, 0.2f }), true, 1.f);

	if (selected_bgm == static_cast<int>(Sound_BGM::level1))
	{
		Selected1.Draw(mat3::build_translation({ -0.25f, 0.2f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ -0.25f,0.2f }), true, 1.f);
	}
	else
		NotSelected.Draw(mat3::build_translation({ -0.25f, 0.2f }), true, 1.f);

	if (selected_bgm == static_cast<int>(Sound_BGM::level2))
	{
		Selected1.Draw(mat3::build_translation({ -0.05f, 0.2f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ -0.05f, 0.2f }), true, 1.f);
	}
	else
		NotSelected.Draw(mat3::build_translation({ -0.05f, 0.2f }), true, 1.f);

	if (selected_bgm == static_cast<int>(Sound_BGM::level3))
	{
		Selected1.Draw(mat3::build_translation({ 0.15f, 0.2f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ 0.15f,0.2f }), true, 1.f);
	}
	else
		NotSelected.Draw(mat3::build_translation({ 0.15f, 0.2f }), true, 1.f);


	if (selected_bgm == static_cast<int>(Sound_BGM::level4))
	{
		Selected1.Draw(mat3::build_translation({ 0.35f, 0.2f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ 0.35f,0.2f }), true, 1.f);
	}
	else
		NotSelected.Draw(mat3::build_translation({ 0.35f, 0.2f }), true, 1.f);


	if (selected_bgm == static_cast<int>(Sound_BGM::level5))
	{
		Selected1.Draw(mat3::build_translation({ 0.55f, 0.2f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ 0.55f,0.2f }), true, 1.f);
	}
	else
		NotSelected.Draw(mat3::build_translation({ 0.55f, 0.2f }), true, 1.f);


	SFX.Draw(mat3::build_translation({ -0.7f, -0.2f }), true, 1.f);
	sound2.Draw(mat3::build_translation({ -0.43f, -0.2f }), true, 1.f);


	if (selected_sfx == static_cast<int>(Sound_SFX::level1))
	{
		Selected2.Draw(mat3::build_translation({ -0.25f, -0.2f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ -0.25f,-0.2f }), true, 1.f);
	}
	else
		NotSelected.Draw(mat3::build_translation({ -0.25f, -0.2f }), true, 1.f);


	if (selected_sfx == static_cast<int>(Sound_SFX::level2))
	{
		Selected2.Draw(mat3::build_translation({ -0.05f, -0.2f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ -0.05f,-0.2f }), true, 1.f);
	}
	else
		NotSelected.Draw(mat3::build_translation({ -0.05f, -0.2f }), true, 1.f);


	if (selected_sfx == static_cast<int>(Sound_SFX::level3))
	{
		Selected2.Draw(mat3::build_translation({ 0.15f, -0.2f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ 0.15f,-0.2f }), true, 1.f);
	}
	else
		NotSelected.Draw(mat3::build_translation({ 0.15f, -0.2f }), true, 1.f);


	if (selected_sfx == static_cast<int>(Sound_SFX::level4))
	{
		Selected2.Draw(mat3::build_translation({ 0.35f, -0.2f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ 0.35f,-0.2f }), true, 1.f);
	}

	else
		NotSelected.Draw(mat3::build_translation({ 0.35f, -0.2f }), true, 1.f);


	if (selected_sfx == static_cast<int>(Sound_SFX::level5))
	{
		Selected2.Draw(mat3::build_translation({ 0.55f, -0.2f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ 0.55f,-0.2f }), true, 1.f);
	}

	else
		NotSelected.Draw(mat3::build_translation({ 0.55f, -0.2f }), true, 1.f);



	NEON_COLOR.Draw(mat3::build_translation({ -0.6f, -0.6f }), true, 1.f);


	if (selected_neon == static_cast<int>(Neon_Color::red))
	{
		Red.Draw(mat3::build_translation({ -0.25f, -0.6f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ -0.25f,-0.6f }), true, 1.f);
	}

	else
		NotSelected.Draw(mat3::build_translation({ -0.25f, -0.6f }), true, 1.f);


	if (selected_neon == static_cast<int>(Neon_Color::yellow))
	{
		Yellow.Draw(mat3::build_translation({ -0.05f, -0.6f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ -0.05f,-0.6f }), true, 1.f);
	}

	else
		NotSelected.Draw(mat3::build_translation({ -0.05f, -0.6f }), true, 1.f);


	if (selected_neon == static_cast<int>(Neon_Color::green))
	{
		Green.Draw(mat3::build_translation({ 0.15f, -0.6f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ 0.15f,-0.6f }), true, 1.f);
	}

	else
		NotSelected.Draw(mat3::build_translation({ 0.15f, -0.6f }), true, 1.f);


	if (selected_neon == static_cast<int>(Neon_Color::blue))
	{
		Blue.Draw(mat3::build_translation({ 0.35f, -0.6f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ 0.35f,-0.6f }), true, 1.f);
	}

	else
		NotSelected.Draw(mat3::build_translation({ 0.35f, -0.6f }), true, 1.f);


	if (selected_neon == static_cast<int>(Neon_Color::pink))
	{
		Pink.Draw(mat3::build_translation({ 0.55f, -0.6f }), true, 1.f);
		option_select_item.Draw(mat3::build_translation({ 0.55f,-0.6f }), true, 1.f);
	}

	else
		NotSelected.Draw(mat3::build_translation({ 0.55f, -0.6f }), true, 1.f);

	std::string exitText = "Press ESC to go to the main menu!";
	Engine::GetFont().SetText(exitText.c_str(), 25);
	font = Texture(Engine::GetFont().GetTexture());
	font.Draw(mat3::build_translation({ 0.0f,-0.9f }), "", 1.0f);

	DataType::fvec2 select_pos{ 0,0 };
	switch (selected_menu_item)
	{
	case 0:
		select_pos = { 0.f, 0.2f };
		break;
	case 1:
		select_pos = { -0.f, -0.2f };
		break;
	case 2:
		select_pos = { -0.f, -0.6f };
		break;
	default:
		break;
	}
	selection.Draw(mat3::build_translation({ select_pos.x, select_pos.y }), true, 1.f);

}
