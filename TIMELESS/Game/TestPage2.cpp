#include "TestPage2.h"
#include "Stage1.h"


TestPage2::TestPage2() : next_stage_key(InputKey::Keyboard::Enter), esc_key(InputKey::Keyboard::Escape), reload_key(InputKey::Keyboard::F5)
{

}

void TestPage2::Load()
{
	//std::string filePath = "assets/HOME.png";
	//background = TextureOpengl(filePath);
	GameObjectManager* gameObjectManager = new GameObjectManager();
	AddGSComponent(gameObjectManager);
	playerPtr = new Player();
	gameObjectManager->Add(playerPtr);

	NeonCreator* neoncreatorPtr = new NeonCreator(200);
	AddGSComponent(neoncreatorPtr);
	DrawMap* drawMapPtr = new DrawMap();
	AddGSComponent(drawMapPtr);

	Camera* cameraPtr = new Camera(playerPtr->GetPosition());
	AddGSComponent(cameraPtr);
	camera_view.SetFramebufferSize(vec2(Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y));
	camera_view.SetZoom(1);
	ShowCollision* showCollision = new ShowCollision();
	AddGSComponent(showCollision);
}

void TestPage2::Update(double dt)
{
	Engine::GetWindow().Clear();

	Engine::GetGSComponent<GameObjectManager>()->Update(dt);
	GetGSComponent<ShowCollision>()->Update(dt);
	
	if (esc_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().Shutdown();
	}

	if (reload_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().ReloadState();
	}
	GetGSComponent<Camera>()->MoveUp(playerPtr->GetPosition());
	GetGSComponent<NeonCreator>()->Update(dt);

	if (next_stage_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().SetNextState("Stage 1");
	}
}

void TestPage2::Unload()
{
	ClearGSComponent();
	Engine::GetFileInput().ClearWallGrid();
}

void TestPage2::Draw()
{
	Engine::GetWindow().ClearBackground(0.4f, 0.4f, 0.4f, 255.f);
	Camera* cameraPtr = GetGSComponent<Camera>();
	mat3 cameraMatrix = cameraPtr->BuildWorldToCamera_mat3();
	cam_to_ndc = camera_view.BuildCameraToNDC();
	
	world_to_ndc = cam_to_ndc * cameraMatrix;
	GetGSComponent<GameObjectManager>()->Draw_player(world_to_ndc);
	GetGSComponent<DrawMap>()->Draw(world_to_ndc);
}