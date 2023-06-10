#include "Stage1.h"
#include"../Engine/Engine.h"
#include"../Engine/Vec2.h"
#include "Item.h"
#include "Score.h"
#include"Light.h"
#include "ItemTypes.h"
#include <random>

DataType::fvec2 Stage1::portal_position = { 0.f,0.f };
int Stage1::stage_level =1;
int Stage1::player_life = 3;
ItemType Stage1::player_inventory[2] = { ItemType::Empty };

double Stage1::totalGameTimer = 0;
int Stage1::player_coin = 000;
int Stage1::coinsEarnedInThisStage = 0;
bool Stage1::IsCoinUpdated = false;

 
bool Stage1::isStoreStage  = false;
bool Stage1::hasResurrection = false;

//DataType::fvec2 Stage1::CamShakeOffset = {0.f, 0.f}; 
int Stage1::CamShakePower = 0;

bool Stage1::isGamePause = false;

Stage1::Stage1() : esc_key(InputKey::Keyboard::Escape), reload_key(InputKey::Keyboard::F5), item_eff_key(InputKey::Keyboard::Z), playerPtr(nullptr), stageClearTimer(0), cam_zoom( 1.f)
{
}

void Stage1::Load()
{
	stageClearTimer = 0;
	cam_zoom = 5.f;
	isBeforeStage = true;
	isGamePause = true;

	GameObjectManager* gameObjectManager = new GameObjectManager();
	AddGSComponent(gameObjectManager);
	playerPtr = new Player();

	std::string filePath2 = "assets/images/BackGround2.png";
	game_background = Texture(filePath2);


	//int this_stage_level;
	if (isStoreStage) { //Move to the store every 3 stages
		this_stage_level = 0;
	}
	else {
		this_stage_level = stage_level;
	}
	Engine::GetLogger().LogDebug("Stage : " + to_string(this_stage_level));

	NeonCreator* neoncreatorPtr = new NeonCreator(200, this_stage_level);
	AddGSComponent(neoncreatorPtr);
	gameObjectManager->Add(playerPtr);
	DrawMap* drawMapPtr = new DrawMap(this_stage_level);
	AddGSComponent(drawMapPtr);

	Camera* cameraPtr = new Camera(playerPtr->GetPosition());
	AddGSComponent(cameraPtr);
	camera_view.SetFramebufferSize(vec2(Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y));
	camera_view.SetZoom(cam_zoom);





	Player_light* plb = new Player_light();
	AddGSComponent(plb);


	AddGSComponent(new NeonParticles());
	AddGSComponent(new PlayerDieParticles());

	AddGSComponent(new PlayerExplodeParticle_1());
	AddGSComponent(new PlayerExplodeParticle_2());
	AddGSComponent(new PlayerExplodeParticle_3());

	AddGSComponent(new TempHPParticle_0());
	AddGSComponent(new TempHPParticle_1());
	AddGSComponent(new TempHPParticle_2());

	AddGSComponent(new GAME_Particle());
	AddGSComponent(new OVER_Particle());

	AddGSComponent(new SpeedUp_1());
	AddGSComponent(new BombExplode_1());
	AddGSComponent(new Dustparticle());
	AddGSComponent(new ChargeParticle());
	AddGSComponent(new SlowExplode_1());

	AddGSComponent(new 	CoinParticle());

	Inventory* inventory0 = new Inventory(0,{180.f,70.f});
	gameObjectManager->Add(inventory0);

	Inventory* inventory1 = new Inventory(1, { 70.f,70.f });
	gameObjectManager->Add(inventory1);

	inventory_eff_Ptr = new Inventory(2, { -180.f,-70.f });
	gameObjectManager->Add(inventory_eff_Ptr);
	
	HealthBar* hp_bar = new HealthBar({ 350.f, 60.f });
	gameObjectManager->Add(hp_bar);

	Coin* coin = new Coin({ 1100.f,70.f });
	gameObjectManager->Add(coin);

	Timer* timer_ = new Timer({ 1100.f,170.f });
	gameObjectManager->Add(timer_);

	_infoChecker_Ptr = nullptr;
	if (isStoreStage) { //change store Item positin here

		DataType::fvec2 checker_pos;
		checker_pos.x = Stage1::x_pos + (Stage1::grid_width / 2) + (Stage1::grid_width * 7);
		checker_pos.y = Stage1::y_pos + (Stage1::grid_width / 2) + ((Stage1::grid_width * 4));
		_infoChecker_Ptr = new ItemBox(checker_pos, ItemType::_ItemInfoChecker);
		gameObjectManager->Add(_infoChecker_Ptr);

		Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 2) + 40,  Stage1::grid_height * 4 + 40 }, ItemType::Invincible));

		Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 3) + 40,  Stage1::grid_height * 5 + 40 }, ItemType::SpeedUp));

		Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 4) + 40,  Stage1::grid_height * 6 + 40 }, ItemType::Bomb));

		Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 7) + 40,  Stage1::grid_height * 2 + 40 }, ItemType::Resurrection));

		Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 5) + 40,  Stage1::grid_height * 7 + 40 }, ItemType::PortalRader));

		Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 9) + 40,  Stage1::grid_height * 7 + 40 }, ItemType::NeonBaricade));

		Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 10) + 40,  Stage1::grid_height * 6 + 40 }, ItemType::NeonSlow));

		Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 11) + 40,  Stage1::grid_height * 5 + 40 }, ItemType::ViewExpand));

		Engine::GetGSComponent<GameObjectManager>()->Add(new ItemBox({ (Stage1::grid_width * 12) + 40,  Stage1::grid_height * 4 + 40 }, ItemType::EnergyAttack));

		LevelInfo* levelText = new LevelInfo({ 650.f,280.f }, 2.0, "STORE");
		gameObjectManager->Add(levelText);
	}
	else {
		LevelInfo* levelText = new LevelInfo({ 650.f,280.f },2.0,"LEVEL "+to_string(Stage1::stage_level));
		gameObjectManager->Add(levelText);
	}

	DebugModePlayerCheat* debugModePlayerCheat = new DebugModePlayerCheat();
	AddGSComponent(debugModePlayerCheat);

	//isGamePause = false;

#ifdef _DEBUG
	ShowCollision* showCollision = new ShowCollision();
	AddGSComponent(showCollision);
	DebugModeTakeAllVision* debugModeTakeAllvision = new DebugModeTakeAllVision();
	AddGSComponent(debugModeTakeAllvision);
	/*DebugModePlayerCheat* debugModePlayerCheat = new DebugModePlayerCheat();
	AddGSComponent(debugModePlayerCheat);*/
#endif // DEBUG



}


void Stage1::Update(double dt)
{

	if (isGamePause == false) {
#ifdef _DEBUG
		GetGSComponent<ShowCollision>()->Update(dt);
		GetGSComponent<DebugModeTakeAllVision>()->Update(dt);
		GetGSComponent<DebugModePlayerCheat>()->Update(dt);
#endif
		Engine::GetWindow().Clear();
		Engine::GetGSComponent<GameObjectManager>()->Update(dt);

		if (esc_key.IsKeyReleased())
		{
			//Engine::GetGameStateManager().Shutdown();
			//Engine::GetGameStateManager().SetNextState("Menu");

			Stage1::player_coin -= Stage1::coinsEarnedInThisStage;
			Stage1::coinsEarnedInThisStage = 0;
			Stage1::IsCoinUpdated = true;

			Engine::GetGameStateManager().SetNextState("ScoreScene");
			Audio* audioPtr = Engine::GetSFXManager().Load("assets/sounds/Esc_key_select.wav");
			audioPtr->Play();
		}
		if (reload_key.IsKeyReleased())
		{
			Engine::GetGameStateManager().ReloadState();
		}

		if (item_eff_key.IsKeyDown())
		{
			inventory_eff_Ptr->SetPosition({ 180.f,70.f });
		}
		if (item_eff_key.IsKeyReleased())
		{
			inventory_eff_Ptr->SetPosition({ -180.f,-70.f });
		}

		//CamShakePower = 0; //test
		//if (reload_key.IsKeyDown())
		//{
		//	CamShakePower = 1; //test
		//}

		GetGSComponent<NeonCreator>()->Update(dt);

		//GetGSComponent<NeonParticles>()->Update(dt);
		//GetGSComponent<Camera>()->MoveUp(playerPtr->GetPosition());

		if (_infoChecker_Ptr != nullptr) {
			_infoChecker_Ptr->SetPosition(playerPtr->GetPosition());
		}

		if (CamShakePower != 0) {

			float lerp = 2.5f;

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> dis(-10.0f * float(CamShakePower), 10.0f * float(CamShakePower));
			float random_off_x = dis(gen);
			float random_off_y = dis(gen);
			//GetGSComponent<Camera>()->MoveUp((playerPtr->GetPosition() + DataType::fvec2(random_off_x, random_off_y)));

			GetGSComponent<Camera>()->position.x += (playerPtr->GetPosition().x - GetGSComponent<Camera>()->position.x) * lerp * float(dt) + random_off_x;
			GetGSComponent<Camera>()->position.y += (playerPtr->GetPosition().y - GetGSComponent<Camera>()->position.y) * lerp * float(dt) + random_off_y;

		}

		else {

			float lerp = 2.5f;
			GetGSComponent<Camera>()->position.x += (playerPtr->GetPosition().x - GetGSComponent<Camera>()->position.x) * lerp * float(dt);
			GetGSComponent<Camera>()->position.y += (playerPtr->GetPosition().y - GetGSComponent<Camera>()->position.y) * lerp * float(dt);

		}


		//camera_view.SetZoom(1.f + sinf(float(totalGameTimer)) + 1.f);

		totalGameTimer += dt;
		//totalGameTimer = round(totalGameTimer * 100) / 100;

	}
	else { //isGamePause == true


		if (isBeforeStage) {
			stageClearTimer += dt;

			float current = float(stageClearTimer / stageClearDelay);
			float max_zoom = 1.0f;
			cam_zoom = max_zoom / (current );
			//cam_zoom -= sinf(float(stageClearTimer) / 3);
			camera_view.SetZoom(cam_zoom);

			if (stageClearTimer > stageClearDelay) {
				isBeforeStage = false;
				isGamePause = false;
				stageClearTimer = 0.f;
				cam_zoom = 1.0;
				camera_view.SetZoom(cam_zoom);
			}
		}
		else {
			stageClearTimer += dt;

			float current = float(stageClearTimer / stageClearDelay);
			float max_zoom = 5.0f;
			cam_zoom = (current * current * current * current * max_zoom) * 10.f + 1.f;
			cam_zoom -= sinf(float(stageClearTimer) / 3);
			camera_view.SetZoom(cam_zoom);


			if (stageClearTimer > stageClearDelay) {
				isBeforeStage = true;
				Engine::GetGameStateManager().ReloadState();
			}


		}



	}

}

void Stage1::Unload()
{
	ClearGSComponent();
	Engine::GetFileInput().ClearWallGrid();

	//if (isStoreStage == false) {
	//	if (stage_level % 3 == 0) { //Move to the store every 3 stages
	//		isStoreStage = true;
	//	}

	//	Stage1::stage_level += 1;		//go to next stage

	//}
	//else {
	//	isStoreStage = false;
	//}
	//Stage1::coinsEarnedInThisStage = 0;//reset



	//if (stage_level > 4)
	//{
	//	Engine::GetGameStateManager().SetNextState("Menu");
	//}

	//if (stage_level > 1)
	//{
	//	Engine::GetGameStateManager().SetNextState("Ending");
	//}

}

void Stage1::Draw()
{
	Camera* cameraPtr = GetGSComponent<Camera>();
	mat3 cameraMatrix = cameraPtr->BuildWorldToCamera_mat3();
	cam_to_ndc = camera_view.BuildCameraToNDC();

	world_to_ndc = cam_to_ndc * cameraMatrix;
	Engine::GetWindow().ClearBackground(0.2f, 0.2f, 0.2f, 255.f);
	game_background.Draw(mat3::build_translation({ 0, 0 }), true, 1.0f);
	
#ifdef _DEBUG
	if (!Engine::GetGSComponent<DebugModeTakeAllVision>()->IsEnabled())
	{
		GetGSComponent<Player_light>()->Draw2(world_to_ndc * playerPtr->GetMatrix_mat3(), playerPtr->Getplayerviewdistance()); //
	}
#else
	GetGSComponent<Player_light>()->Draw2(world_to_ndc * playerPtr->GetMatrix_mat3(), playerPtr->Getplayerviewdistance()); 
#endif // _DEBUG
	


	
	
	//GetGSComponent<GameObjectManager>()->Draw_underParticle(world_to_ndc);
	//GetGSComponent<GameObjectManager>()->Draw_neon(world_to_ndc);
	GetGSComponent<GameObjectManager>()->Draw_neon(world_to_ndc);
	GetGSComponent<GameObjectManager>()->Draw_underParticle(world_to_ndc);
	GetGSComponent<DrawMap>()->Draw(world_to_ndc);
	GetGSComponent<GameObjectManager>()->Draw_all(world_to_ndc);
	GetGSComponent<GameObjectManager>()->Draw_player(world_to_ndc);
	//GetGSComponent<GameObjectManager>()->Draw_UI();
	GetGSComponent<GameObjectManager>()->Draw_particle(world_to_ndc);



	if (isGamePause==true && isBeforeStage == false && this_stage_level != 0) {
		Texture clearFont;
		std::string clearText = "LEVEL " + to_string(Stage1::stage_level - 1);
		Engine::GetFont().SetText(clearText.c_str(),60);
		clearFont = Texture(Engine::GetFont().GetTexture());
		clearFont.Draw(mat3::build_translation({ 0, 0.05f }), "Test", 1.0f);

		Texture clearFont2;
		std::string clearText2 = "CLEAR!";
		Engine::GetFont().SetText(clearText2.c_str(),60);
		clearFont2 = Texture(Engine::GetFont().GetTexture());
		clearFont2.Draw(mat3::build_translation({ 0, -0.1f }), "Test", 1.0f);


	}


}



// Update -> Collide -> Draw