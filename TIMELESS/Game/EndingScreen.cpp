#include"EndingScreen.h"
#include "Stage1.h"

EndingCredit::EndingCredit() : 
	next_stage_key(InputKey::Keyboard::Enter), esc_key(InputKey::Keyboard::Escape), space_bar_key(InputKey::Keyboard::Space)
{
}




void EndingCredit::Load()
{

	locked_enter_key = true;
	locked_space_key = false;
	start_ = false;
	end_ = false;
	T = chrono::system_clock::now();
	std::string digipen_dragons = "assets/images/DigiPen_Dragon.png";
	digipen_dragons_texture = Texture(digipen_dragons);
	scroll_speed = 0.1f;
	GameObjectManager* gameObjectManager = new GameObjectManager();
	AddGSComponent(gameObjectManager);

	NeonCreator* neoncreatorPtr = new NeonCreator(200, 7);
	AddGSComponent(neoncreatorPtr);

	HealthBar* hp_bar = new HealthBar({ 650.f, 200.f });
	gameObjectManager->Add(hp_bar);

	Coin* coin = new Coin({ 550.f,300.f });
	gameObjectManager->Add(coin);

	Timer* timer_ = new Timer({ 550.f,370.f });
	gameObjectManager->Add(timer_);

	int timerScore;
	if (Stage1::totalGameTimer > 300) {
		timerScore = 1, 000, 000 - (Stage1::totalGameTimer - 300) * 50;
	}
	else {
		timerScore = 1, 000, 000 + (300 - Stage1::totalGameTimer) * 50;
	}


	Engine::GetFont().SetText("Total");
	totalFont = Texture(Engine::GetFont().GetTexture());
	totalScore = Stage1::player_coin * 10 + Stage1::player_life * 100 + timerScore;
	Engine::GetFont().SetText((std::to_string(totalScore)).c_str(),35);
	scoreFont = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("All Stage Clear!");
	levelFont = Texture(Engine::GetFont().GetTexture());

	Engine::GetFont().SetText("Press Enter Key",50);
	Press_Enter_key_font = Texture(Engine::GetFont().GetTexture());



	ending_credit_ypos = 0.0f;
	basic_ypos = -1.2f;
	basic_ypos_height = 0.5f;
	end_ypos_height = 0.5f;
	category_name_height = 0.3f;
	Load_Text();

	Camera* cameraPtr = new Camera(DataType::fvec2(0.0f,0.0f));
	AddGSComponent(cameraPtr);
	camera_view.SetFramebufferSize(vec2(Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y));
	camera_view.SetZoom(1);


	AddGSComponent(new NeonParticles());
	AddGSComponent(new PlayerDieParticles());


}

void EndingCredit::Update(double dt)
{
	Engine::GetWindow().Clear();
	GetGSComponent<Camera>()->MoveUp(DataType::fvec2(0.0f, 0.0f));
	chrono::system_clock::time_point now = chrono::system_clock::now();
	double delta_time = chrono::duration<double>(now - T).count();

	if (delta_time >= 3.0)
	{
		locked_enter_key = false;
	}

	if (start_)
	{
		locked_enter_key = true;
		ending_credit_ypos += scroll_speed * static_cast<float>(dt);
		Engine::GetGSComponent<GameObjectManager>()->Update(dt);

		GetGSComponent<NeonCreator>()->Update_ending(dt);
	}

	if (std::floor((basic_ypos - (end_ypos_height * 19.50f) + ending_credit_ypos) * 10) / 10 == -0.0f)
	{
		//Engine::GetLogger().LogEvent("Image was center!");
		scroll_speed = 0.0f;
		locked_enter_key = false;
		locked_space_key = true;
		end_ = true;
	}
	

	
	
	if (!locked_space_key && space_bar_key.IsKeyDown())
	{
		scroll_speed = 1.8f;
	}
	if (!locked_space_key && space_bar_key.IsKeyReleased())
	{
		scroll_speed = 0.1f;
	}
	if (!locked_enter_key)
	{
		if (!end_ && next_stage_key.IsKeyReleased())
		{
			start_ = true;
		}
		else if (end_ && next_stage_key.IsKeyReleased())
		{
			Engine::GetGameStateManager().SetNextState("Ending Story");
			Stage1::player_life = 3;
			Stage1::stage_level = 1;
			Stage1::isStoreStage = false;
			Stage1::player_inventory[0] = ItemType::Empty;
			Stage1::player_inventory[1] = ItemType::Empty;
			Stage1::player_coin = 0;
			Stage1::coinsEarnedInThisStage = 0;
			Stage1::IsCoinUpdated = true;
			Stage1::totalGameTimer = 0;
		}
	}
	//if (!locked_enter_key && next_stage_key.IsKeyReleased())
	//{
	//	


	
	//}
#ifdef _DEBUG
	if (esc_key.IsKeyReleased())
	{
		//Engine::GetGameStateManager().Shutdown();
		Engine::GetGameStateManager().SetNextState("Menu");
	}
#endif // DEBUG

}

void EndingCredit::Unload()
{
	locked_enter_key = true;
	locked_space_key = false;
	start_ = false;
	end_ = false;
	ClearGSComponent();
	
}

void EndingCredit::Draw()
{
	Camera* cameraPtr = GetGSComponent<Camera>();
	mat3 cameraMatrix = cameraPtr->BuildWorldToCamera_mat3();
	cam_to_ndc = camera_view.BuildCameraToNDC();

	world_to_ndc = cam_to_ndc * cameraMatrix;
	Engine::GetWindow().ClearBackground(0.f, 0.f, 0.f, 1.f);
	
	
	GetGSComponent<GameObjectManager>()->Draw_underParticle(world_to_ndc);
	GetGSComponent<GameObjectManager>()->Draw_particle(world_to_ndc);
	GetGSComponent<GameObjectManager>()->Draw_UI_for_ending(ending_credit_ypos);
	//GetGSComponent<GameObjectManager>()->Draw_UI();
	levelFont.Draw(mat3::build_translation({ 0.0f,-0.1f + ending_credit_ypos }), "", 1.0f);
	totalFont.Draw(mat3::build_translation({ 0.0f, -0.3f + ending_credit_ypos }), "", 1.0f);
	scoreFont.Draw(mat3::build_translation({ 0.0f,-0.4f + ending_credit_ypos }), "", 1.0f);
	if (!locked_enter_key)
	{
		Press_Enter_key_font.Draw(mat3::build_translation({ 0.0f,-0.9f }), "", 1.0f);
	}
	
	Draw_credit();
	
}


	

//	GetGSComponent<GameObjectManager>()->Draw_particle(world_to_ndc);



void EndingCredit::Draw_credit()
{
	endingText.Thank_you_for_playing.Draw(mat3::build_translation({ 0.0f,basic_ypos + ending_credit_ypos }), "", 1.0f);

	endingText.Game_Name.Draw(mat3::build_translation({ 0.0f,basic_ypos - basic_ypos_height + ending_credit_ypos }), "", 1.0f);
	endingText.Team_Name.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 1.3f) + ending_credit_ypos }), "", 1.0f);

	endingText.Producer.Draw(mat3::build_translation({ 0.0f,basic_ypos - (basic_ypos_height * 2.3f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name1.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 2.6f) + ending_credit_ypos }), "", 1.0f);

	endingText.Technical_Lead.Draw(mat3::build_translation({ 0.0f,basic_ypos - (basic_ypos_height * 3.3f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name2.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 3.6f) + ending_credit_ypos }), "", 1.0f);

	endingText.Art_Lead.Draw(mat3::build_translation({ 0.0f,basic_ypos - (basic_ypos_height * 4.3f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name3.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 4.6f) + ending_credit_ypos }), "", 1.0f);

	endingText.Level_Designer.Draw(mat3::build_translation({ 0.0f,basic_ypos - (basic_ypos_height * 5.3f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name4.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 5.6f) + ending_credit_ypos }), "", 1.0f);

	endingText.Programeers.Draw(mat3::build_translation({ 0.0f,basic_ypos - (basic_ypos_height * 6.3f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name1.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 6.6f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name2.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 6.75f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name3.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 6.9f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name4.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 7.05f) + ending_credit_ypos }), "", 1.0f);


	endingText.Art_Animation.Draw(mat3::build_translation({ 0.0f,basic_ypos - (basic_ypos_height * 7.75f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name3.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 8.05f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name2.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 8.2f) + ending_credit_ypos }), "", 1.0f);

	endingText.Sound_Music.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 8.9f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name1.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 9.2f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name4.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 9.35f) + ending_credit_ypos }), "", 1.0f);


	endingText.Testers.Draw(mat3::build_translation({ 0.0f,basic_ypos - (basic_ypos_height * 10.05f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name1.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 10.35f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name2.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 10.5f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name3.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 10.65f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name4.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 10.8f) + ending_credit_ypos }), "", 1.0f);
	endingText.text1.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 10.95f) + ending_credit_ypos }), "", 1.0f);



	endingText.Instructor.Draw(mat3::build_translation({ 0.0f,basic_ypos - (basic_ypos_height * 11.65f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name5.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 11.95f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name7.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 12.1f) + ending_credit_ypos }), "", 1.0f);


	endingText.Teaching_Ass.Draw(mat3::build_translation({ 0.0f,basic_ypos - (basic_ypos_height * 12.8f) + ending_credit_ypos }), "", 1.0f);
	endingText.Name6.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 13.1f) + ending_credit_ypos }), "", 1.0f);


	Tools.Tools_Libraries.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 13.8f) + ending_credit_ypos }), "", 1.0f);
	Tools.powerpoint.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 14.1f) + ending_credit_ypos }), "", 1.0f);
	Tools.visualstudio.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 14.25f) + ending_credit_ypos }), "", 1.0f);
	Tools.aseprite.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 14.4f) + ending_credit_ypos }), "", 1.0f);
	Tools.adobe_fresco.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 14.55f) + ending_credit_ypos }), "", 1.0f);
	Tools.sketchbook.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 14.7f) + ending_credit_ypos }), "", 1.0f);
	Tools.fl_studio.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 14.85f) + ending_credit_ypos }), "", 1.0f);
	Tools.sfxr.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 15.0f) + ending_credit_ypos }), "", 1.0f);
	Tools.sfml.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 15.15f) + ending_credit_ypos }), "", 1.0f);
	Tools.opengl.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 15.3f) + ending_credit_ypos }), "", 1.0f);
	Tools.glew.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 15.45f) + ending_credit_ypos }), "", 1.0f);
	Tools.feetype.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 15.6f) + ending_credit_ypos }), "", 1.0f);
	Tools.stbimage.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 15.75f) + ending_credit_ypos }), "", 1.0f);



	endingText.Special_Thanks.Draw(mat3::build_translation({ 0.0f,basic_ypos - (basic_ypos_height * 16.45f) + ending_credit_ypos }), "", 1.0f);
	endingText.text2.Draw(mat3::build_translation({ 0.0f, basic_ypos - (basic_ypos_height * 16.75f) + ending_credit_ypos }), "", 1.0f);

	digipen_dragons_texture.Draw(mat3::build_translation({ 0.0f, basic_ypos - (end_ypos_height * 19.50f) + ending_credit_ypos }), true, 1.f);

	digipen_copyright.Draw(mat3::build_translation({ 0.0f, basic_ypos - (end_ypos_height * 21.0f) + ending_credit_ypos }), "", 1.0f);
}












void EndingCredit::Load_Text()
{
	endingText.BasicTextSize = 25;
	endingText.CategorySize = 40;
	Tools.basictextsize = 20;
	Engine::GetFont().SetText("Thank you for playing!",55);
	//Engine::GetFont().SetFontSize(50);
	endingText.Thank_you_for_playing = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("NEON",60);
	endingText.Game_Name = Texture(Engine::GetFont().GetTexture());

	Engine::GetFont().SetText("Developed by Team Timeless",30);
	endingText.Team_Name = Texture(Engine::GetFont().GetTexture());

	Engine::GetFont().SetText("MinSeok Kim", endingText.BasicTextSize);
	endingText.Name1 = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("HyoJoon Kim", endingText.BasicTextSize);
	endingText.Name2 = Texture(Engine::GetFont().GetTexture());;
	Engine::GetFont().SetText("SeulBin Seo", endingText.BasicTextSize);
	endingText.Name3 = Texture(Engine::GetFont().GetTexture());;
	Engine::GetFont().SetText("JunSeong Park", endingText.BasicTextSize);
	endingText.Name4 = Texture(Engine::GetFont().GetTexture());;

	Engine::GetFont().SetText("Producer", endingText.CategorySize);
	endingText.Producer = Texture(Engine::GetFont().GetTexture());;
	Engine::GetFont().SetText("Technical Lead", endingText.CategorySize);
	endingText.Technical_Lead = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("Art Lead", endingText.CategorySize);
	endingText.Art_Lead = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("Level Designer", endingText.CategorySize);
	endingText.Level_Designer = Texture(Engine::GetFont().GetTexture());

	Engine::GetFont().SetText("Programmers", endingText.CategorySize);
	endingText.Programeers = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("Art & Animation", endingText.CategorySize);
	endingText.Art_Animation = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("Sound & Music", endingText.CategorySize);
	endingText.Sound_Music = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("Testers", endingText.CategorySize);
	endingText.Testers = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("GAM250 course's all students",endingText.BasicTextSize);
	endingText.text1 = Texture(Engine::GetFont().GetTexture());

	Engine::GetFont().SetText("Academic Advisors", endingText.CategorySize);
	endingText.Instructor = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("Prof. Jonathan Holmes", endingText.BasicTextSize);
	endingText.Name5 = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("Prof. Rudy Castan", endingText.BasicTextSize);
	endingText.Name7 = Texture(Engine::GetFont().GetTexture());

	Engine::GetFont().SetText("Teaching Assistants", endingText.CategorySize);
	endingText.Teaching_Ass = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("Soroor Malekmohammadi", endingText.BasicTextSize);
	endingText.Name6 = Texture(Engine::GetFont().GetTexture());

	Engine::GetFont().SetText("Special Thanks", endingText.CategorySize);
	endingText.Special_Thanks = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("To our friends and families for their unwavering support and encouragement!", endingText.BasicTextSize);
	endingText.text2 = Texture(Engine::GetFont().GetTexture());



	Engine::GetFont().SetText("Tools & Libraries", endingText.CategorySize);
	Tools.Tools_Libraries = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("PowerPoint(Game Design)", Tools.basictextsize);
	Tools.powerpoint = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("Aseprite(Art)", Tools.basictextsize);
	Tools.aseprite = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("Adobe Fresco(Art)", Tools.basictextsize);
	Tools.adobe_fresco = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("FL Studio 20(Audio)", Tools.basictextsize);
	Tools.fl_studio = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("Visual Studio Community 2022(IDE)", Tools.basictextsize);
	Tools.visualstudio = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("sfxr(Audio)", Tools.basictextsize);
	Tools.sfxr = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("SFML(Library)", Tools.basictextsize);
	Tools.sfml = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("OpenGL(Library)", Tools.basictextsize);
	Tools.opengl = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("glew(Library)", Tools.basictextsize);
	Tools.glew = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("SDL_ttf(Library)", Tools.basictextsize);
	Tools.feetype = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("stb image(Library)", Tools.basictextsize);
	Tools.stbimage = Texture(Engine::GetFont().GetTexture());
	Engine::GetFont().SetText("Sketchbook - Ipad(Art)", Tools.basictextsize);
	Tools.sketchbook = Texture(Engine::GetFont().GetTexture());



	Engine::GetFont().SetText("All content (C) 2023 DigiPen(USA) Corporation, all rights reserved.", 15);
	digipen_copyright = Texture(Engine::GetFont().GetTexture());
	
}