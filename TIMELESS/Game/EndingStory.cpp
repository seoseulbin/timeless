#include "EndingStory.h"

EndingStory::EndingStory()
	: next_stage_key(InputKey::Keyboard::Enter), esc_key(InputKey::Keyboard::Escape), Story(nullptr), alpha(0.f)
{
}

void EndingStory::Load()
{
	GameObjectManager* gameObjectManager = new GameObjectManager();
	AddGSComponent(gameObjectManager);
	Story = new EStory();

	gameObjectManager->Add(Story);

	Engine::GetFont().SetText("Succeed!", 120);
	Success = Texture(Engine::GetFont().GetTexture());

	Engine::GetFont().SetText("Press Enter Key to go to Menu", 20);
	go_Menu = Texture(Engine::GetFont().GetTexture());

	T = chrono::system_clock::now();


#ifdef _DEBUG
	ShowCollision* showCollision = new ShowCollision();
	AddGSComponent(showCollision);
	DebugModeTakeAllVision* debugModeTakeAllvision = new DebugModeTakeAllVision();
	AddGSComponent(debugModeTakeAllvision);
	DebugModePlayerCheat* debugModePlayerCheat = new DebugModePlayerCheat();
	AddGSComponent(debugModePlayerCheat);
#endif // DEBUG
}

void EndingStory::Update(double dt)
{
	Engine::GetWindow().Clear();
	Engine::GetGSComponent<GameObjectManager>()->Update(dt);
	chrono::system_clock::time_point now = chrono::system_clock::now();
	dt = chrono::duration<double>(now - T).count();

	if (next_stage_key.IsKeyReleased())
		Engine::GetGameStateManager().SetNextState("Menu");

	if (dt > 4.0f)
	{
		alpha += 0.2f;
	}
	 

#ifdef _DEBUG
	if (esc_key.IsKeyReleased())
	{
		Engine::GetGameStateManager().SetNextState("Menu");
	}
#endif // DEBUG
}

void EndingStory::Unload()
{
	ClearGSComponent();
}

void EndingStory::Draw()
{
	Engine::GetWindow().ClearBackground(0.f, 0.f, 0.f, 1.f);
	GetGSComponent<GameObjectManager>()->Draw_UI();
	Success.Draw(mat3::build_translation({ 0.05f, 0.5f }), "", alpha);
	go_Menu.Draw(mat3::build_translation({ 0.0f,-0.95f }), "", alpha);
}



//------------------------------------------------------------------------------------------------------------------------


EStory::EStory()
{
	AddGOComponent(new Sprite("assets/data/EndingStory.spt", this));
	SetPosition({650,400});
	this->GetGOComponent<Sprite>()->PlayAnimation(0);
}
