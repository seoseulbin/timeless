#include "Stage1.h"
#include"../Engine/Engine.h"
#include"../Engine/Vec2.h"
#include "Coin.h"
#include "Score.h"
#include"Light.h"

int Stage1::stage_level = 1;
int Stage1::player_life = 3;

Stage1::Stage1() : esc_key(InputKey::Keyboard::Escape), reload_key(InputKey::Keyboard::F5),playerPtr(nullptr)
{	
}

void Stage1::Load()
{
	GameObjectManager* gameObjectManager = new GameObjectManager();
	AddGSComponent(gameObjectManager);
	playerPtr = new Player();
	
	
	Engine::GetLogger().LogDebug("Stage : " + to_string(stage_level));
	
	NeonCreator* neoncreatorPtr = new NeonCreator(200);
	AddGSComponent(neoncreatorPtr);
	gameObjectManager->Add(playerPtr);
	DrawMap* drawMapPtr = new DrawMap();
	AddGSComponent(drawMapPtr);
	
	Camera* cameraPtr = new Camera(playerPtr->GetPosition());
	AddGSComponent(cameraPtr);
	camera_view.SetFramebufferSize(vec2(Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y));
	camera_view.SetZoom(1);
	

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

#ifdef _DEBUG
	ShowCollision* showCollision = new ShowCollision();
	AddGSComponent(showCollision);
#endif // DEBUG

	

}


void Stage1::Update(double dt)
{
#ifdef _DEBUG
	GetGSComponent<ShowCollision>()->Update(dt);
#endif
	Engine::GetWindow().Clear();
	Engine::GetGSComponent<GameObjectManager>()->Update(dt);
	
	if (esc_key.IsKeyReleased())
	{
		//Engine::GetGameStateManager().Shutdown();
		Engine::GetGameStateManager().SetNextState("Menu");
	}
	if (reload_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().ReloadState();
	}

	if(stage_level == 4)
	{
		Engine::GetGameStateManager().SetNextState("Menu");
	}

	
	GetGSComponent<NeonCreator>()->Update(dt);
	//GetGSComponent<NeonParticles>()->Update(dt);
	GetGSComponent<Camera>()->MoveUp(playerPtr->GetPosition());

}

void Stage1::Unload()
{
	ClearGSComponent();
	Engine::GetFileInput().ClearWallGrid();
}

void Stage1::Draw()
{
	Camera* cameraPtr = GetGSComponent<Camera>();
	mat3 cameraMatrix = cameraPtr->BuildWorldToCamera_mat3();
	cam_to_ndc = camera_view.BuildCameraToNDC();

	world_to_ndc = cam_to_ndc * cameraMatrix;
	Engine::GetWindow().ClearBackground(0.2f, 0.2f, 0.2f, 255.f);
	
	GetGSComponent<Player_light>()->Draw2(world_to_ndc * playerPtr->GetMatrix_mat3()); //


	GetGSComponent<GameObjectManager>()->Draw_underParticle(world_to_ndc);
	GetGSComponent<GameObjectManager>()->Draw_all(world_to_ndc);
	
	
	
	GetGSComponent<DrawMap>()->Draw(world_to_ndc);
	
	GetGSComponent<GameObjectManager>()->Draw_player(world_to_ndc);


	GetGSComponent<GameObjectManager>()->Draw_particle(world_to_ndc);


}



// Update -> Collide -> Draw