#include "Coin.h"
#include "../Engine/Engine.h"
#include "Stage1.h"
#include "Inventory_Anims.h"

Coin::Coin(DataType::fvec2 pos) : UI()
{
	AddGOComponent(new Sprite("assets/data/Coin1.spt", this));

	//coin----
	Engine::GetFont().SetText(std::to_string(Stage1::player_coin).c_str());
	//Engine::GetFont().Setting("test", 10, 255, 255, 255, 255);
	testFont = Texture(Engine::GetFont().GetTexture());

	////timer-----
	//Engine::GetFont().SetText(std::to_string(Stage1::totalGameTimer).c_str());
	//timerFont = Texture(Engine::GetFont().GetTexture());

	SetPosition(pos);
	//SetScale({ 0.6f,0.6f });
}

void Coin::Update(double /*dt*/)
{

	if (Stage1::IsCoinUpdated) {

		Engine::GetFont().SetText(std::to_string(Stage1::player_coin).c_str());
		testFont = Texture(Engine::GetFont().GetTexture());

		Stage1::IsCoinUpdated = false;
	}


}

void Coin::Draw(mat3 NDCmatrix)
{
	DataType::fvec2 text_pos{ GetPosition().x + 100.f, GetPosition().y };
	NDCmatrix = UI::ToNDC(text_pos);
	testFont.Draw(NDCmatrix, "Test", 1.0f);
	UI::Draw(NDCmatrix);

	////timer---------------------
	//text_pos = { GetPosition().x+100.f , GetPosition().y + 50.f };
	//NDCmatrix = UI::ToNDC(text_pos);

	//std::ostringstream oss;
	//oss << std::fixed << std::setprecision(2) << Stage1::totalGameTimer;
	//std::string timer_str = oss.str();

	//Engine::GetFont().SetText(timer_str.c_str());
	//timerFont = Texture(Engine::GetFont().GetTexture());
	//timerFont.Draw(NDCmatrix, "Test", 1.0f);
}

void Coin::Draw(float scroll)
{
	DataType::fvec2 text_pos{ GetPosition().x + 100.f, GetPosition().y};
	mat3 displayMatrix = UI::ToNDC(text_pos);
	displayMatrix *= mat3::build_translation({ 0.0f,scroll });
	testFont.Draw(displayMatrix, "", 1.0f);
	UI::Draw(scroll);
}

//`````````````````````````````````````````````````````````````````

Timer::Timer(DataType::fvec2 pos) : UI()
{

	//timer-----
	Engine::GetFont().SetText(std::to_string(Stage1::totalGameTimer).c_str());
	timerFont = Texture(Engine::GetFont().GetTexture());

	SetPosition(pos);
	//SetScale({ 0.6f,0.6f });
}

void Timer::Update(double /*dt*/)
{

}

void Timer::Draw(mat3 NDCmatrix)
{
	DataType::fvec2 text_pos{ GetPosition().x + 100.f, GetPosition().y };

	//timer---------------------
//	text_pos = { GetPosition().x + 100.f , GetPosition().y + 50.f };
	NDCmatrix = UI::ToNDC(text_pos);

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << Stage1::totalGameTimer;
	std::string timer_str = oss.str();

	Engine::GetFont().SetText(timer_str.c_str());
	timerFont = Texture(Engine::GetFont().GetTexture());
	timerFont.Draw(NDCmatrix, "Test", 1.0f);
}

void Timer::Draw(float scroll)
{
	DataType::fvec2 text_pos{ GetPosition().x + 100.f, GetPosition().y };

	mat3 displayMatrix = UI::ToNDC(text_pos);
	displayMatrix *= mat3::build_translation({ 0.0f,scroll });

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << Stage1::totalGameTimer;
	std::string timer_str = oss.str();

	Engine::GetFont().SetText(timer_str.c_str());
	timerFont = Texture(Engine::GetFont().GetTexture());
	timerFont.Draw(displayMatrix, "", 1.0f);
}


//`````````````````````````````````````````````````````````````````

LevelInfo::LevelInfo(DataType::fvec2 pos, double timer, std::string text) : UI() , visible_timer(timer), str(text)
{

	//timer-----
	Engine::GetFont().SetText(std::to_string(Stage1::totalGameTimer).c_str());
	levelFont = Texture(Engine::GetFont().GetTexture());

	SetPosition(pos);
	//SetScale({ 0.6f,0.6f });
}

void LevelInfo::Update(double dt)
{
	visible_timer -= dt;
	
	if(visible_timer <0 )
		Destory();

}

void LevelInfo::Draw(mat3 NDCmatrix)
{
	DataType::fvec2 text_pos{ GetPosition().x , GetPosition().y };

	NDCmatrix = UI::ToNDC(text_pos);

	Engine::GetFont().SetText(str.c_str(),50);
	levelFont = Texture(Engine::GetFont().GetTexture());
	levelFont.Draw(NDCmatrix, "Test", 1.0f);
}

void LevelInfo::Draw(float scroll)
{
	DataType::fvec2 text_pos{ GetPosition().x, GetPosition().y };

	mat3 displayMatrix = UI::ToNDC(text_pos);
	displayMatrix *= mat3::build_translation({ 0.0f,scroll });

	Engine::GetFont().SetText(str.c_str(),50);
	levelFont = Texture(Engine::GetFont().GetTexture());
	levelFont.Draw(displayMatrix, "", 1.0f);
}