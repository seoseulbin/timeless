#pragma once
#include"../Engine/GameState.h"
#include"GLShader.h"
#include"GLVertexArray.h"
#include"GLTexture.h"
#include"../Engine/Texture.h"
#include"../Engine/Input.h"
#include"../Engine/GameObjectManager.h"
#include"Player.h"
#include"CameraView.h"


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

	Texture background;

	InputKey next_stage_key;
	InputKey esc_key;

};