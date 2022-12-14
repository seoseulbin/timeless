#include <glCheck.h>

#include"color3.h"
#include "Engine.h"
#include<array>
#include"mat3.h"
#include "Texture.h" //Texture
#include"GameObject.h"
#include"Collision.h"

//for test
#include<iostream>

Texture::Texture(GLTexture SDLImage)
{
    image = std::move(SDLImage);
}
Texture::Texture(const std::filesystem::path& filePath)
{
    shader = GLShader(filePath.filename().string(), {{GLShader::VERTEX, "assets/shaders/test.vert"}, {GLShader::FRAGMENT, "assets/shaders/test.frag"}});
    Load(filePath);
    /*if (const bool loaded = image.LoadFromFileImage(filePath); !loaded)
    {
        throw std::runtime_error("Failed to load");
    }*/
}
Texture::Texture(bool show_collide)
{
    if (show_collide)
    {
        shader = GLShader("RedCollisionRect", { {GLShader::VERTEX, "assets/shaders/model_to_ndc_pos2d_clr.vert"},
        {GLShader::FRAGMENT, "assets/shaders/basic_vtx_clr_attribute.frag"} });
        Load_red_line();
    }
}

//TextureOpengl::TextureOpengl(std::string filePath)
//{
//    shader = GLShader(filePath, { {GLShader::VERTEX, "assets/shaders/test.vert"}, {GLShader::FRAGMENT, "assets/shaders/test.frag"} });
//    Load(filePath);
//}



Texture::Texture(const std::filesystem::path& filePath, GameObject* object, DataType::frect2 rectA)
{
    shader = GLShader("texture shader", { {GLShader::VERTEX, "assets/shaders/test.vert"}, {GLShader::FRAGMENT, "assets/shaders/test.frag"} });
    Load(filePath, object, rectA);
}

void Texture::Load_red_line()
{
    CreateFullscreenQuad_Red_Line();
}


void Texture::Load(const std::filesystem::path& filePath)
{
    
    //shader[1] = GLShader("texel shader", { {GLShader::VERTEX, "assets/shaders/texel_shader.vert"}, {GLShader::FRAGMENT, "assets/shaders/texel_shader.frag"} });
    CreateFullscreenQuad();
    
    if (const bool loaded = image.LoadFromFileImage(filePath); !loaded)
    {
        throw std::runtime_error{ "Failed to load the logo image" };
    }
    glCheck(glEnable(GL_BLEND));
    glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    glCheck(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    
}

void Texture::Load(const std::filesystem::path& filePath, GameObject* object, DataType::frect2 rectA)
{
    
    //shader[1] = GLShader("texel shader", { {GLShader::VERTEX, "assets/shaders/texel_shader.vert"}, {GLShader::FRAGMENT, "assets/shaders/texel_shader.frag"} });
    CreateFullscreenQuad();

    if (const bool loaded = image.LoadFromFileImage(filePath); !loaded)
    {
        throw std::runtime_error{ "Failed to load the logo image" };
    }

    glCheck(glEnable(GL_BLEND));
    glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    glCheck(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

    object->AddGOComponent(new RectCollision(rectA, object));
}

namespace
{
    std::span<const float, 3 * 3> to_span(const mat3& m)
    {
        return std::span<const float, 3 * 3>(&m.elements[0][0], 9);
    }
    //std::span<const float, 3> to_span(const color3& c)
    //{
    //    return std::span<const float, 3>(&c.elements[0], 3);
    //}
}

//use texture shader

void Texture::Draw_Neon(mat3 displayMatrix, float alpha)
{
    displayMatrix.column0.x = 1.f;
    displayMatrix.column1.y = 1.f;
    
    mat3 scale = mat3::build_scale(static_cast<float>(image.GetWidth()), static_cast<float>(image.GetHeight()));
    mat3 extent = mat3::build_scale(1 / Engine::GetWindow().GetSize().x, 1 / Engine::GetWindow().GetSize().y);
    const mat3 model_to_ndc = extent * scale;
    shader.Use();
    image.UseForSlot(0);
    shader.SendUniform("uTex2d", 0);
    auto display = displayMatrix * model_to_ndc;
    shader.SendUniform("uModelToNDC", to_span(display));
    shader.SendUniform("uAlpha", alpha);
    vao.Use();
    GLDrawIndexed(vao);

    vao.Use(false);
    shader.Use(false);
}

void Texture::Draw([[maybe_unused]]mat3 displayMatrix)
{

    displayMatrix.column0.x = 1.f;
    displayMatrix.column1.y = 1.f;
    //displayMatrix.column2.y = -displayMatrix.column2.y;
    mat3 scale = mat3::build_scale(static_cast<float>(image.GetWidth()), static_cast<float>(image.GetHeight()));
    mat3 extent = mat3::build_scale(1 / Engine::GetWindow().GetSize().x, 1 / Engine::GetWindow().GetSize().y);
    const mat3 model_to_ndc = extent * scale;
    shader.Use();
    image.UseForSlot(0);
    shader.SendUniform("uTex2d", 0);
    auto display = displayMatrix * model_to_ndc;
    shader.SendUniform("uModelToNDC", to_span(display));
    shader.SendUniform("uAlpha", 1.f);
    vao.Use();
    GLDrawIndexed(vao);
    
    vao.Use(false);
    shader.Use(false);
}

void Texture::Draw(mat3 displayMatrix, DataType::frect2 displayRect)
{
    
    displayMatrix.column0.x = 1.f;
    displayMatrix.column1.y = 1.f;
    
    mat3 scale = mat3::build_scale(static_cast<float>(displayRect.Size().x), static_cast<float>(displayRect.Size().y));
    mat3 extent = mat3::build_scale(1 / Engine::GetWindow().GetSize().x, 1 / Engine::GetWindow().GetSize().y);
    const mat3 model_to_ndc = extent * scale;
    shader.Use();
    vao_red.Use();
    auto display = displayMatrix * model_to_ndc;
    shader.SendUniform("uModelToNDC", to_span(display));
    glCheck(GLDrawIndexed(vao_red));
    vao_red.Use(false);
    shader.Use(false);
}

void Texture::Draw_player(mat3 displayMatrix)
{
    mat3 scale = mat3::build_scale(static_cast<float>(image.GetWidth()), static_cast<float>(image.GetHeight()));
    mat3 extent = mat3::build_scale(1 / Engine::GetWindow().GetSize().x, 1 / Engine::GetWindow().GetSize().y);
    const mat3 model_to_ndc = extent * scale;
    shader.Use();
    image.UseForSlot(0);
    shader.SendUniform("uTex2d", 0);
    auto display = displayMatrix * model_to_ndc;
    shader.SendUniform("uModelToNDC", to_span(display));
    shader.SendUniform("uAlpha", 1.f);
    vao.Use();
    GLDrawIndexed(vao);
    vao.Use(false);
    shader.Use(false);
}

void Texture::Draw([[maybe_unused]]mat3 displayMatrix,bool alphaChange, float alpha)
{
    displayMatrix.column0.x = 1.f;
    displayMatrix.column1.y = 1.f;
    mat3 scale = mat3::build_scale(static_cast<float>(image.GetWidth()), static_cast<float>(image.GetHeight()));
    mat3 extent = mat3::build_scale(1 / Engine::GetWindow().GetSize().x, 1 / Engine::GetWindow().GetSize().y);
    const mat3 model_to_ndc = extent * scale;
    auto display = displayMatrix * model_to_ndc;
    shader.Use();
    image.UseForSlot(0);
    shader.SendUniform("uTex2d", 0);
    shader.SendUniform("uModelToNDC", to_span(display));
    if (alphaChange)
    {
        shader.SendUniform("uAlpha", alpha);
    }
    else
        shader.SendUniform("uAlpha", 1.0f);
    vao.Use();
    GLDrawIndexed(vao);

    vao.Use(false);
    shader.Use(false);
}

vec2 Texture::GetSize() { return { static_cast<float>(image.GetWidth()), static_cast<float>(image.GetHeight()) }; }

void Texture::CreateFullscreenQuad()
{
    constexpr std::array positions =
    {
        vec2(-1.f,1.f), vec2(-1.f,-1.f), vec2(1.0f,-1.0f), vec2(1.f,1.f)
    };
    //constexpr std::array colors =
    //{
    //    color3(0,1,0), color3(0,0,1), color3(1,0,0), color3(1,1,1)
    //    //color3(1,0,0), color3(0,1,0), color3(0,0,1), color3(1,1,1)
    //};
    /*constexpr std::array textures =
    {
        vec2{1.0f, 0.0f}, vec2{1.0f, 1.0f},
        vec2{0.0f, 1.0f}, vec2{0.0f, 0.0f}
    };*/
    constexpr std::array<unsigned char, 4> indices = { 0,1,3,2 };

    GLAttributeLayout position;
    position.component_type = GLAttributeLayout::Float;
    position.component_dimension = GLAttributeLayout::_2;
    position.normalized = false;
    position.vertex_layout_location = 0;
    position.stride = sizeof(vec2);
    position.offset = 0;
    position.relative_offset = 0;

    //GLAttributeLayout color;
    //color.component_type = GLAttributeLayout::Float;
    //color.component_dimension = GLAttributeLayout::_3;
    //color.normalized = false;
    //color.vertex_layout_location = 1;
    //color.stride = sizeof(color3);
    //color.offset = 0;
    //color.relative_offset = 0;

    //GLAttributeLayout texture;
    //texture.component_type = GLAttributeLayout::Float;
    //texture.component_dimension = GLAttributeLayout::_2;
    //texture.normalized = false;
    //texture.vertex_layout_location = 2;
    //texture.stride = sizeof(vec2);
    //texture.offset = 0;
    //texture.relative_offset = 0;


    vao.AddVertexBuffer(GLVertexBuffer(std::span{ positions }), { position });
    //vao.AddVertexBuffer(GLVertexBuffer(std::span{ colors }), { color });
    //vao.AddVertexBuffer(GLVertexBuffer(std::span{ textures }), { texture });
    vao.SetPrimitivePattern(GLPrimitive::TriangleStrip);
    GLIndexBuffer index_buffer(indices);
    vao.SetIndexBuffer(std::move(index_buffer));
}

void Texture::CreateFullscreenQuad_Red_Line()
{
    constexpr std::array positions =
    {
        vec2(-1.f,1.f), vec2(-1.f,-1.f), vec2(1.0f,-1.0f), vec2(1.f,1.f)
    };
    constexpr std::array colors =
    {
        color3(1,0,0), color3(1,0,1), color3(1,0,0), color3(1,0,1)
    };
    constexpr std::array<unsigned char, 5> indices = { 0,1,2,3,0 };
    GLAttributeLayout position;
    position.component_type = GLAttributeLayout::Float;
    position.component_dimension = GLAttributeLayout::_2;
    position.normalized = false;
    position.vertex_layout_location = 0;
    position.stride = sizeof(vec2);
    position.offset = 0;
    position.relative_offset = 0;

    GLAttributeLayout color;
    color.component_type = GLAttributeLayout::Float;
    color.component_dimension = GLAttributeLayout::_3;
    color.normalized = false;
    color.vertex_layout_location = 1;
    color.stride = sizeof(color3);
    color.offset = 0;
    color.relative_offset = 0;

    vao_red.AddVertexBuffer(GLVertexBuffer(std::span{ positions }), { position });
    vao_red.AddVertexBuffer(GLVertexBuffer(std::span{ colors }), { color });
    vao_red.SetPrimitivePattern(GLPrimitive::LineStrip);
    GLIndexBuffer index_buffer(indices);
    vao_red.SetIndexBuffer(std::move(index_buffer));
}