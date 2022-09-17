#pragma once
#include<string>
#include"Vec2.h"

using namespace std;


namespace Timeless
{
	class Window
	{
	public:
		void Init(string windowTitle);
		void Update();
		void Resize(int newWidth, int newHeight);
		void Clear(unsigned int color);
		DataType::ivec2 GetSize();
	private:
		DataType::ivec2 windowSize = { 1300, 800 };
	};
}

