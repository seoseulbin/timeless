#pragma once
#include "../Engine/GameState.h"
#include "GLShader.h"
#include "GLVertexArray.h"
#include "GLTexture.h"
#include "../Engine/Texture.h"
#include "../Engine/Input.h"
#include "../Engine/GameObjectManager.h"
#include "Player.h"
#include "CameraView.h"

class Player;

class LoadingScreen : public GameState
{
public:
	LoadingScreen();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "LoadingScreen";
	}

private:
	Texture background_up;
	Texture background_down;

	bool Blinking = true;
	std::chrono::system_clock::time_point T;
	float alphaVal;

	InputKey next_stage_key;
	InputKey esc_key;
};