#pragma once
#include<string>
#include<filesystem>
#include"vec2.h"
#include"Vec2.h"
#include"mat3.h"
#include"Engine.h"
#include<vector>
#include"Component.h"
#include"Animation.h"

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
	void Update(double dt) override;

	vec2 GetFrameSize() const;


	void PlayAnimation(int anim);
	int GetCurrentAnim();
	bool IsAnimationDone();

	void Draw(mat3  displayMatrix);
	void Draw_None_Animation_object(mat3 displayMatrix, float Opacity);
	void Draw_Animation_object(mat3 displayMatrix, vec2 scale,float rotate, float Opacity);
	void Draw_particle_effect(mat3 displayMatrix, float alpha);
private:
	DataType::ivec2 GetFrameTexel(int frameNum) const;
	int currAnim;
	vec2 frameSize;
	std::vector<DataType::ivec2> frameTexel;
	Texture* texturePtr;
	std::vector<Animation*> animations;
};