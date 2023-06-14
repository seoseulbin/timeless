#include "ScoreScene.h"
#include "Stage1.h"
#include "..\Engine\Font.h"

ScoreScene::ScoreScene() : next_stage_key(InputKey::Keyboard::Enter)
{
	string texturePath = "assets/images/scoreBackground.png";
	background = Texture{texturePath};
}

void ScoreScene::Load()
{
	GameObjectManager *gameObjectManager = new GameObjectManager();
	AddGSComponent(gameObjectManager);

	Coin *coin = new Coin({550.f, 370.f});
	gameObjectManager->Add(coin);

	totalScore = Stage1::player_coin * 10 + Stage1::stage_level * 150;

	Engine::GetFont().SetText(("Score : " + std::to_string(totalScore)).c_str());
	scoreFont = Texture(Engine::GetFont().GetTexture());

	Engine::GetFont().SetText(("Level : " + std::to_string(Stage1::stage_level)).c_str());
	levelFont = Texture(Engine::GetFont().GetTexture());
}

void ScoreScene::Update(double dt)
{
	Engine::GetWindow().Clear();

	Engine::GetGSComponent<GameObjectManager>()->Update(dt);

	if (next_stage_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().SetNextState("Menu");
		Stage1::player_life = 3;
		Stage1::stage_level = 1;
		Stage1::isStoreStage = false;
		Stage1::player_inventory[0] = ItemType::Empty;
		Stage1::player_inventory[1] = ItemType::Empty;
		Stage1::player_coin = 0;
		Stage1::coinsEarnedInThisStage = 0;
		Stage1::IsCoinUpdated = true;
		Stage1::totalGameTimer = 0;
		Audio *audioPtr = Engine::GetSFXManager().Load("assets/sounds/Normal_select.wav");
		audioPtr->Play();
	}
}

void ScoreScene::Unload()
{
}

void ScoreScene::Draw()
{

	background.Draw(mat3::build_translation(0, 0), true, 255);
	GetGSComponent<GameObjectManager>()->Draw_UI();
	scoreFont.Draw(mat3::build_translation({0.0f, -0.15f}), "Test", 1.0f);
	levelFont.Draw(mat3::build_translation({0.0f, 0.3f}), "Test", 1.0f);
}