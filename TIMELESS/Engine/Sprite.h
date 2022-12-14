#pragma once
#include<string>
#include<filesystem>
#include"vec2.h"
#include"Vec2.h"
#include"mat3.h"
#include"Engine.h"
#include<vector>
#include"Component.h"

class Texture;
class GameObject;

class Sprite : public Component
{
public:
	Sprite() : texturePtr(nullptr) {}
	Sprite(const std::filesystem::path& spriteFile, GameObject* object);
	~Sprite();
	void Load_noObject(const std::filesystem::path& spriteFile);
	void Load(const std::filesystem::path& spriteFile, GameObject* object);
	void Draw(mat3 displayMatrix);
	void Draw_player(mat3 displayMatrix, vec2 scale);
	void Draw(mat3 displayMatrix, float alpha);
	vec2 GetFrameSize() const;
	void Update(double dt) override;



	//void PlayAnimation(int anim); 추후 필요시 사용예정
	//bool IsAnimationDone();
	//int GetCurrAnim();
	
private:
	DataType::ivec2 GetFrameTexel(int frameNum) const;
	//int currAnim;
	vec2 frameSize;
	std::vector<DataType::ivec2> frameTexel;
	Texture* texturePtr;
	
};