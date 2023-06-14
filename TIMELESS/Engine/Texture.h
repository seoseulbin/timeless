#pragma once
#include <GLShader.h>
#include <GLTexture.h>
#include <GLVertexArray.h>

#include "vec2.h"
#include "mat3.h"
#include "Component.h"
#include "Rect.h"

class GameObject;

class Texture : public Component
{
public:
	Texture(){};
	Texture(GLTexture SDLImage);

	Texture(DataType::frect2 displayRect);
	// TextureOpengl(std::string filePath);
	Texture(const std::filesystem::path &filePath);
	Texture(const std::filesystem::path &filePath, bool used_anim_shader);
	Texture(bool show_collide);
	// Texture(const std::filesystem::path& filePath, GameObject* object, DataType::frect2 rectA);
	void Load_red_line();
	void Load(const std::filesystem::path &filePath);
	void Load(const std::filesystem::path &filePath, GameObject *object, DataType::frect2 rectA);

	void Draw_Collision_box(mat3 displayMatrix, DataType::frect2 displayRect); // use
	void Draw(mat3 displayMatrix);											   // use normal grid
	void Draw(mat3 displayMatrix, bool alphaChange, float alpha);
	void Draw(mat3 displayMatrix, const char *text, float alpha);
	// Draw background, Draw button

	void Draw_None_Animation_object(mat3 displayMatrix, float Opacity);
	void Draw_particle_effect(mat3 displayMatrix, float alpha);
	void Draw_Animation_object(mat3 displayMatrix, DataType::vec2 texelPos, vec2 frameSize, float Opacity);

	vec2 GetSize();
	void CreateFullscreenQuad();
	void CreateFontscreenQuad();
	void CreateFullscreenQuad_Red_Line();

	vec2 GetNDCSize();

	// void Draw_player(mat3 displayMatrix);
	// void Draw_alpha_test(mat3 displayMatrix, float Opacity);
private:
	GLTexture image;
	GLShader shader[2];

	GLShader shader_test;
	GLShader text_shader;
	GLVertexArray vao;
	GLVertexArray vao_red;
};