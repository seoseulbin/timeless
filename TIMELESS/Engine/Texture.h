#pragma once
#include <GLShader.h>
#include <GLTexture.h>
#include <GLVertexArray.h>

#include "vec2.h"
#include "mat3.h"
#include"Component.h"
#include"Rect.h"

class GameObject;

class Texture : public Component
{
public:
    Texture() {};
    Texture(GLTexture SDLImage);
    
    Texture(DataType::frect2 displayRect);
    //TextureOpengl(std::string filePath);
    Texture(const std::filesystem::path& filePath);
    Texture(bool show_collide);
    Texture(const std::filesystem::path& filePath, GameObject* object, DataType::frect2 rectA);
    void Load_red_line();
    void Load(const std::filesystem::path& filePath);
    void Load(const std::filesystem::path& filePath, GameObject* object, DataType::frect2 rectA);

    void Draw(mat3 displayMatrix, DataType::frect2 displayRect);
    void Draw(mat3 displayMatrix);
    void Draw_player(mat3 displayMatrix);
    void Draw_Neon(mat3 displayMatrix, float alpha);
    void Draw(mat3 displayMatrix,bool alphaChange, float alpha);
    //void Draw(mat3 displayMatrix, vec2 texelPos, vec2 frameSize);
    vec2 GetSize();
    void CreateFullscreenQuad();
    void CreateFullscreenQuad_Red_Line();

private:
    GLTexture image;
    GLShader shader;
    GLVertexArray vao;
    GLVertexArray vao_red;
};