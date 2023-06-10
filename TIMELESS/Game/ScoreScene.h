#pragma once
#include"../Engine/GameState.h"
#include"GLShader.h"
#include"GLVertexArray.h"
#include"GLTexture.h"
#include"..\Engine\Texture.h"
#include"../Engine/Input.h"
#include"../Engine/GameObjectManager.h"
#include"Player.h"
#include"CameraView.h"
#include"../Engine/Font.h"
#include "Coin.h"
#include "HP_UI.h"
#include"..\Engine\Font.h"

class ScoreScene : public GameState
{
public:
	ScoreScene();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	string GetName() override
	{
		return "ScoreScene";
	}


private:
	Texture background;
	InputKey next_stage_key;

	Texture scoreFont;
	Texture levelFont;

	int totalScore;
};
