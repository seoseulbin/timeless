#include "Light.h"
#include "../Engine/angles.h"
#include <glCheck.h>
#include "color3.h"
#include "../Engine/Engine.h"
namespace
{
	std::span<const float, 3 * 3> to_span(const mat3 &m)
	{
		return std::span<const float, 3 * 3>(&m.elements[0][0], 9);
	}
	// std::span<const float, 3> to_span(const color3& c)
	//{
	//     return std::span<const float, 3>(&c.elements[0], 3);
	// }
}

Light::Light()
{
	Load();
}

void Light::Load()
{
	shader = GLShader("Light Shader", {{GLShader::VERTEX, "assets/shaders/light.vert"}, {GLShader::FRAGMENT, "assets/shaders/light.frag"}});
	shader2 = GLShader("Light Shader2", {{GLShader::VERTEX, "assets/shaders/light2.vert"},
										 {GLShader::FRAGMENT, "assets/shaders/light2.frag"}});

	CreateCircle();
	CreateQuad();

	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Light::Draw(mat3 displayMatrix)
{
	displayMatrix.column0.x = 1.f;
	displayMatrix.column1.y = 1.f;

	mat3 scale = mat3::build_scale(static_cast<float>(1300), static_cast<float>(800));
	mat3 extent = mat3::build_scale(1 / Engine::GetWindow().GetSize().x, 1 / Engine::GetWindow().GetSize().y);
	const mat3 model_to_ndc = extent * scale;
	shader2.Use();
	vao2.Use();
	auto display = displayMatrix * model_to_ndc;
	shader2.SendUniform("uModelToNDC", to_span(display));
	GLDrawIndexed(vao2);
	vao2.Use(false);
	shader2.Use(false);
}

void Light::Draw2(mat3 displayMatrix, float viewDistance)
{
	glClearColor(0, 0, 0, 1);
	displayMatrix.column0.x = 1.f;
	displayMatrix.column1.y = 1.f;
	mat3 scale2 = mat3::build_scale(viewDistance * 2, viewDistance * 2);
	mat3 extent2 = mat3::build_scale(1 / Engine::GetWindow().GetSize().x, 1 / Engine::GetWindow().GetSize().y);
	const mat3 model_to_ndc2 = extent2 * scale2;
	shader.Use();
	vao.Use();
	auto display2 = displayMatrix * model_to_ndc2;
	shader.SendUniform("uModelToNDC", to_span(display2));
	glCheck(GLDrawVertices(vao));

	vao.Use(false);
	shader.Use(false);
}

void Light::CreateCircle()
{
	constexpr int slices = 90;
	constexpr int count{slices + 2};
	float degree = 360.0f / slices;
	std::vector<vec2> pos_vtx(count);
	unsigned pos_index{0};
	pos_vtx[pos_index++] = vec2{0, 0};

	for (int i = 0; i <= slices; i++)
	{
		pos_vtx[pos_index++] = vec2{cos(util::to_radians(degree) * i), sin(util::to_radians(degree) * i)};
	}

	vao.SetVertexCount(static_cast<int>(pos_vtx.size()));

	GLAttributeLayout position;
	position.component_dimension = GLAttributeLayout::_2;
	position.component_type = GLAttributeLayout::Float;
	position.normalized = false;
	position.offset = 0;
	position.relative_offset = 0;
	position.stride = sizeof(vec2);
	position.vertex_layout_location = 0;

	vao.AddVertexBuffer(GLVertexBuffer(std::span{pos_vtx}), {position});
	vao.SetPrimitivePattern(GLPrimitive::TriangleFan);
}

void Light::CreateQuad()
{
	constexpr std::array positions =
		{
			vec2(-1.f, 1.f), vec2(-1.f, -1.f), vec2(1.0f, -1.0f), vec2(1.f, 1.f)};
	constexpr std::array<unsigned char, 4> indices = {0, 1, 3, 2};
	GLAttributeLayout position;
	position.component_type = GLAttributeLayout::Float;
	position.component_dimension = GLAttributeLayout::_2;
	position.normalized = false;
	position.vertex_layout_location = 0;
	position.stride = sizeof(vec2);
	position.offset = 0;
	position.relative_offset = 0;

	vao2.AddVertexBuffer(GLVertexBuffer(std::span{positions}), {position});
	vao2.SetPrimitivePattern(GLPrimitive::TriangleStrip);
	GLIndexBuffer index_buffer(indices);
	vao2.SetIndexBuffer(std::move(index_buffer));
}