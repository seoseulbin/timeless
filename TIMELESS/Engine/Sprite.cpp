#include"Sprite.h"
#include"Texture.h"
#include"Collision.h"
#include"GameObject.h"



Sprite::Sprite(const std::filesystem::path& spriteFile, GameObject* object)
{
	Load(spriteFile, object);
}

Sprite::~Sprite()
{

}

void Sprite::Load_noObject(const std::filesystem::path& spriteFile)
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
	texturePtr = Engine::GetTextureManager().Load(text);
	frameSize = texturePtr->GetSize();
}

void Sprite::Load(const std::filesystem::path& spriteFile, [[maybe_unused]]GameObject* object)
{
	if (spriteFile.extension() != ".spt")
	{
		throw std::runtime_error("Bad FileType.   " + spriteFile.generic_string() + " not a sprite info file(.spt)");
	}
	std::ifstream inFile(spriteFile);

	if (inFile.is_open() == false)
	{
		throw std::runtime_error("Failed to Read .spt file");
	}
	std::string text;
	inFile >> text;
	texturePtr = Engine::GetTextureManager().Load(text);
	frameSize = texturePtr->GetSize();
	inFile >> text;
	while (!inFile.eof())
	{
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
	}
}

void Sprite::Update([[maybe_unused]] double dt)
{

}

vec2 Sprite::GetFrameSize() const
{
	return frameSize;
}

void Sprite::Draw(mat3 displayMatrix)
{
	texturePtr->Draw(displayMatrix);
}


void Sprite::Draw_player(mat3 displayMatrix, vec2 scale)
{
	displayMatrix.column0.x = 1;
	displayMatrix.column1.y = 1;
	displayMatrix *= mat3::build_scale(scale);
	texturePtr->Draw_player(displayMatrix);
}

void Sprite::Draw(mat3 displayMatrix,float  alpha)
{
	texturePtr->Draw_Neon(displayMatrix,alpha);
}