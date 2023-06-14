#pragma once
#include "mat3.h"
#include "vec2.h"
#include "GLTexture.h"
#include <GLShader.h>
#include <GLVertexArray.h>
#include "Vec2.h"
#include "color3.h"
#include "SDL2/SDL_ttf.h"
#include "Component.h"

class Font
{
public:
	Font();
	~Font();
	void InitFont();
	void LoadFontSetting(const char *filePath);
	void Prepare_font();
	void Load();
	void SetText(const char *text);
	void SetText(const char *text, int size);
	void Setting(const char *text, int size = 30, int r = 255, int g = 255, int b = 255, int alpha = 255);
	// void Draw(mat3 displayMatrix, float alpha);
	void SetFontSize(int FontSize);
	SDL_Color GetColor();
	GLTexture createTextTexture(const char *text, TTF_Font *font, SDL_Color color);
	GLTexture GetTexture();

	void CreateFontscreenQuad();

private:
	GLTexture textTexture;

	SDL_Color color;

	TTF_Font *font;
	const char *Text;
	const char *filePath;
	int fontSize;
};

class FontTexture
{
public:
	FontTexture();

private:
	GLVertexArray vao;
};