#pragma once
#include"..\Engine\GameState.h"
#include"../Engine/GameObjectManager.h"
#include"..\Engine\Input.h"
#include"..\Engine\Font.h"
#include"..\Engine\Engine.h"
#include "Coin.h"
#include "HP_UI.h"
#include "Neon.h"
#include "Particle.h"
#include "../Engine/Camera.h"
#include"../Engine/GameObject.h"
#include"CameraView.h"
#include<chrono>

class EndingCredit : public GameState
{
public:
	EndingCredit();
	void Load_Text();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;


	void Draw_credit();

	string GetName() override
	{
		return "Ending";
	}

private:
	Texture background;
	InputKey next_stage_key;
	InputKey esc_key;
	InputKey space_bar_key;

	struct 
	{
		Texture Thank_you_for_playing;
		Texture Game_Name;
		Texture Team_Name;
		Texture Producer;
		Texture Technical_Lead;
		Texture Art_Lead;
		Texture Level_Designer;
		Texture Name1;
		Texture Name2;
		Texture Name3;
		Texture Name4;
		Texture Name5;
		Texture Name6;
		Texture Name7;
		Texture Programeers;
		Texture Art_Animation;
		Texture Sound_Music;
		Texture Testers;
		Texture text1;
		Texture Instructor;
		Texture Teaching_Ass;
		Texture Special_Thanks;
		Texture text2;

		int BasicTextSize;
		int CategorySize;
		
	}endingText;

	struct
	{
		Texture Tools_Libraries;
		Texture powerpoint;
		Texture aseprite;
		Texture adobe_fresco;
		Texture fl_studio;
		Texture sketchbook;
		Texture visualstudio;
		Texture sfxr;
		Texture sfml;
		Texture opengl;
		Texture glew;
		Texture feetype;
		Texture stbimage;
		int basictextsize;
	}Tools;

	
	Texture digipen_dragons_texture;
	Texture digipen_copyright;

	Texture scoreFont;
	Texture totalFont;
	Texture levelFont;
	Texture Press_Enter_key_font;
	int totalScore;
	float ending_credit_ypos;
	float scroll_speed;
	float basic_ypos_height;
	float end_ypos_height;
	float category_name_height;
	float basic_ypos;
	CameraView camera_view;
	mat3 world_to_ndc;
	mat3 world_to_cam;
	mat3 cam_to_ndc;


	bool locked_enter_key;
	bool start_;
	bool locked_space_key;
	bool end_;

	float alpha = 0;
	std::chrono::system_clock::time_point T;

};