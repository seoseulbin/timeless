#include "Sprite.h"
#include "Texture.h"
#include "Collision.h"
#include "GameObject.h"
#include "../Game/GameObjectTypes.h"

Sprite::Sprite(const std::filesystem::path &spriteFile, GameObject *object)
{
	Load(spriteFile, object);
}

Sprite::~Sprite()
{
	for (Animation *anim : animations)
	{
		delete anim;
	}
	animations.clear();
}

void Sprite::Load_noObject(const std::filesystem::path &spriteFile)
{
	if (spriteFile.extension() != ".spt")
	{
		throw std::runtime_error("Bad FileType.   " + spriteFile.generic_string() + " not a sprite info file(.spt)");
	}
	std::ifstream inFile(spriteFile);
	if (!inFile.is_open())
	{
		throw std::runtime_error("Failed to Read .spt file");
	}
	std::string text;
	inFile >> text;
	texturePtr = Engine::GetTextureManager().Load(text, false);
	frameSize = texturePtr->GetSize();
}

void Sprite::Load(const std::filesystem::path &spriteFile, [[maybe_unused]] GameObject *object)
{
	frameTexel.clear();
	if (spriteFile.extension() != ".spt")
	{
		throw std::runtime_error("Bad FileType.   " + spriteFile.generic_string() + " not a sprite info file(.spt)");
	}
	std::ifstream inFile(spriteFile);

	if (inFile.is_open() == false)
	{
		throw std::runtime_error("Failed to Read .spt file");
	}
	std::string text, savetexturePtr;
	bool need_anim = false;
	inFile >> text;
	savetexturePtr = text;
	if (object->GetObjectType() == GameObjectType::Neon || object->GetObjectType() == GameObjectType::PlayerLight)
	{
		texturePtr = Engine::GetTextureManager().Load(text, false);
	}
	else
	{
		texturePtr = Engine::GetTextureManager().Load(text, true);
	}

	frameSize = texturePtr->GetSize();
	inFile >> text;
	while (!inFile.eof())
	{
		if (text == "FrameSize")
		{
			inFile >> frameSize.x;
			inFile >> frameSize.y;
		}
		if (text == "NumFrames")
		{
			int numFrames;
			inFile >> numFrames;
			for (int i = 0; i < numFrames; i++)
			{
				frameTexel.push_back({static_cast<int>(frameSize.x) * i, 0});
			}
		}
		if (text == "Frame")
		{
			int frameLocationX, frameLocationY;
			inFile >> frameLocationX;
			inFile >> frameLocationY;
			frameTexel.push_back({frameLocationX, frameLocationY});
		}
		if (text == "Anim")
		{
			inFile >> text;
			animations.push_back(new Animation(text));
			need_anim = true;
		}
		if (text == "CollisionRect")
		{
			DataType::frect2 rect;
			inFile >> rect.point1.x >> rect.point1.y >> rect.point2.x >> rect.point2.y;
			if (object == nullptr)
			{
				Engine::GetLogger().LogError("Trying to add collision to a nullobject");
			}
			else
			{
				object->AddGOComponent(new RectCollision(rect, object));
			}
		}
		inFile >> text;
	}
	if (frameTexel.empty() == true)
	{
		frameTexel.push_back({0, 0});
	}

	if (animations.empty())
	{
		animations.push_back(new Animation{});
		PlayAnimation(0);
	}
}

void Sprite::Update([[maybe_unused]] double dt)
{
	if (animations.size() != 0)
		animations[currAnim]->Update(dt);
}

void Sprite::PlayAnimation(int anim)
{
	if (anim < 0 || anim > animations.size() - 1)
	{
		Engine::GetLogger().LogError("Animation" + std::to_string(anim));
		currAnim = 0;
	}
	else
	{
		currAnim = anim;
		animations[currAnim]->ResetAnimation();
	}
}

int Sprite::GetCurrentAnim()
{
	return currAnim;
}

bool Sprite::IsAnimationDone()
{
	return animations[currAnim]->IsAnimationDone();
}

vec2 Sprite::GetFrameSize() const
{
	return frameSize;
}

DataType::ivec2 Sprite::GetFrameTexel(int frameNum) const
{
	if (frameNum < 0 || frameNum >= frameTexel.size())
	{
		Engine::GetLogger().LogError("Bad frame request" + std::to_string(frameNum));
		return DataType::ivec2{0, 0};
	}
	return frameTexel[frameNum];
}

////////////////Draw Function///////////////

void Sprite::Draw(mat3 displayMatrix)
{
	texturePtr->Draw(displayMatrix);
}

void Sprite::Draw_None_Animation_object(mat3 displayMatrix, [[maybe_unused]] float Opacity)
{
	// test1-----------------------------------------------------------------------------------------------
	texturePtr->Draw_None_Animation_object(displayMatrix, Opacity);

	/// test2----------------------------------------------------------------------------------------------
	// displayMatrix.column0.x = 1;
	// displayMatrix.column1.y = 1;
	// texturePtr->Draw_Animation_object(displayMatrix, GetFrameTexel(animations[currAnim]->GetDisplayFrame()), GetFrameSize());
}

void Sprite::Draw_Animation_object(mat3 displayMatrix, vec2 scale, float rotate, float Opacity)
{
	displayMatrix.column0.x = 1;
	displayMatrix.column1.y = 1;
	displayMatrix *= mat3::build_scale(scale);
	displayMatrix *= mat3::build_rotation(rotate);

	texturePtr->Draw_Animation_object(displayMatrix, GetFrameTexel(animations[currAnim]->GetDisplayFrame()), GetFrameSize(), Opacity);
}

void Sprite::Draw_particle_effect(mat3 displayMatrix, float alpha)
{
	texturePtr->Draw_particle_effect(displayMatrix, alpha);
}