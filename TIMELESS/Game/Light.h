#pragma once
#include<GLShader.h>
#include<GLTexture.h>
#include<GLVertexArray.h>
#include"vec2.h"
#include"mat3.h"
#include"../Engine/Component.h"


class Light : public Component
{
public:
	Light();
	void Load();
	void CreateCircle();
	void CreateQuad();
	void Draw(mat3 displayMatrix);
	void Draw2(mat3 displayMatrix, float viewDistance);
	//void DrawOther(mat3 displayMatrix);

private:
	GLShader shader;
	GLShader shader2;
	GLVertexArray vao;
	GLVertexArray vao2;

	float player_viewdistance = 0.0f;
};
