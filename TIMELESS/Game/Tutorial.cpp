#include "Tutorial.h"
#include "../Engine/Engine.h"

Tutorial::Tutorial() : exit(InputKey::Keyboard::Escape), enter(InputKey::Keyboard::Enter), moveLeftKey(InputKey::Keyboard::Left), moveRightKey(InputKey::Keyboard::Right),
					   moveUpKey(InputKey::Keyboard::Up), moveDownKey(InputKey::Keyboard::Down), evadeKey(InputKey::Keyboard::Space)
{
}

void Tutorial::Load()
{
	std::string filePath1 = "assets/images/story1.png";
	std::string filePath2 = "assets/images/story2.png";
	std::string filePath3 = "assets/images/story3.png";
	std::string filePath4 = "assets/images/story4.png";
	std::string filePath5 = "assets/images/story6.png";

	// std::string playerFIle = "assets/images/new_player.png";

	story1 = Texture(filePath1);
	story2 = Texture(filePath2);
	story3 = Texture(filePath3);
	story4 = Texture(filePath4);
	story5 = Texture(filePath5);

	GameObjectManager *gameObjectManager = new GameObjectManager();
	AddGSComponent(gameObjectManager);
	playerPtr = new Player();
	gameObjectManager->Add(playerPtr);
	Camera *cameraPtr = new Camera(playerPtr->GetPosition());
	AddGSComponent(cameraPtr);
	camera_view.SetFramebufferSize(vec2(Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y));
	camera_view.SetZoom(1);

#ifdef _DEBUG
	ShowCollision *showCollision = new ShowCollision();
	AddGSComponent(showCollision);
	DebugModeTakeAllVision *debugModeTakeAllvision = new DebugModeTakeAllVision();
	AddGSComponent(debugModeTakeAllvision);
	DebugModePlayerCheat *debugModePlayerCheat = new DebugModePlayerCheat();
	AddGSComponent(debugModePlayerCheat);
#endif // _DEBUG
}

void Tutorial::Update(double dt)
{
	Engine::GetWindow().Clear();

	if (CurrentStory < 4)
	{
		if (enter.IsKeyReleased())
		{
			CurrentStory++;
		}
	}

	if (exit.IsKeyReleased())
	{
		Engine::GetGameStateManager().SetNextState("Menu");
		Audio *audioPtr = Engine::GetSFXManager().Load("assets/sounds/Esc_key_select.wav");
		audioPtr->Play();
	}

	if (CurrentStory == 4)
	{

#ifdef _DEBUG
		GetGSComponent<ShowCollision>()->Update(dt);
		GetGSComponent<DebugModeTakeAllVision>()->Update(dt);
		GetGSComponent<DebugModePlayerCheat>()->Update(dt);
#endif // _DEBUG

		Engine::GetGSComponent<GameObjectManager>()->Update(dt);
		GetGSComponent<Camera>()->MoveUp(playerPtr->GetPosition());
	}
}

void Tutorial::Unload()
{
	ClearGSComponent();
	CurrentStory = 0;
}

void Tutorial::Draw()
{
	Engine::GetWindow().ClearBackground(0.f, 0.f, 0.f, 255.f);

	switch (CurrentStory)
	{
	case 0:
		story1.Draw(mat3::build_translation({0, 0}), true, 1.f);
		break;
	case 1:
		story2.Draw(mat3::build_translation({0, 0}), true, 1.f);
		break;
	case 2:
		story3.Draw(mat3::build_translation({0, 0}), true, 1.f);
		break;
	case 3:
		story5.Draw(mat3::build_translation({0, 0}), true, 1.f);
		break;
	case 4:
		Camera *cameraPtr = GetGSComponent<Camera>();
		mat3 cameraMatrix = cameraPtr->BuildWorldToCamera_mat3();
		auto cam_to_ndc = camera_view.BuildCameraToNDC();
		auto world_to_ndc = cam_to_ndc * cameraMatrix;
		story4.Draw(world_to_ndc * mat3::build_translation(Engine::GetWindow().GetSize().x / 2, Engine::GetWindow().GetSize().y / 2), true, 1.f);
		GetGSComponent<GameObjectManager>()->Draw_player(world_to_ndc);
		break;
	}
}