#pragma once
#include<doodle/image.hpp>

#include"Vec2.h"
#include"Matrix.h"

using namespace std;
using namespace DataType;
using namespace doodle;


namespace Timeless
{
	class Texture
	{
	public:
		Texture();
		void Load(const filesystem::path& filePath);
		void Load(const filesystem::path& filePath, vec2 location);
		void Draw(vec2 location);
		void Draw(Matrix displayMatrix);
		//void Update(Camera camera);
		ivec2 GetSize();

	private:
		Image image;
		vec2 position;
	};
}