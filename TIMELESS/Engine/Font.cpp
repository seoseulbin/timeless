#include<glCheck.h>
#include"Font.h"
#include"Engine.h"
namespace FontUtil
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
Font::Font()
{
	InitFont();
}

Font::~Font()
{
	TTF_CloseFont(font);
}

void Font::InitFont()
{
	TTF_Init();
}

void Font::LoadFontSetting(const char* Path) // link to filePath
{
	filePath = Path;
	color = { 255,255,255,255 };
	fontSize = 30;
}

void Font::Prepare_font() // open font and link to font ptr
{
	font = TTF_OpenFont(filePath, fontSize);
	if (!font)
	{
		Engine::GetLogger().LogError("Failed to OpenFont");
	}	
}

void Font::Load()
{
	TTF_CloseFont(font);
	font = TTF_OpenFont(filePath, fontSize);
	textTexture = createTextTexture(Text, font, color);
}

void Font::SetText(const char* test)
{
	Text = test;
	fontSize = 30;
	Load();
}

void Font::SetText(const char* text, int size)
{
	Text = text;
	fontSize = size;
	Load();
}

void Font::SetFontSize(int FontSize) // set newfontsize and reload new font ptr
{
	if (font)
	{
		TTF_CloseFont(font);
	}
	fontSize = FontSize;
	Load();
	if (!font)
	{
		Engine::GetLogger().LogError("Failed to load font with new size");
	}
}

void Font::Setting(const char* text, int size, int r, int g, int b, int alpha)
{
    color.r = static_cast<Uint8>(r);
    color.g = static_cast<Uint8>(g);
    color.b = static_cast<Uint8>(b);
    color.a = static_cast<Uint8>(alpha);
    Text = text;
	fontSize = size;
}

//void Font::Draw([[maybe_unused]] mat3 displayMatrix, float alpha)
//{
//	displayMatrix.column0.x = 1.f;
//	displayMatrix.column1.y = 1.f;
//	mat3 scale = mat3::build_scale(static_cast<float>(textTexture.GetWidth()), static_cast<float>(textTexture.GetHeight()));
//	mat3 extent = mat3::build_scale(1 / Engine::GetWindow().GetSize().x, 1 / Engine::GetWindow().GetSize().y);
//	const mat3 model_to_ndc = extent * scale;
//	auto display = displayMatrix * model_to_ndc;
//	shader.Use();
//	textTexture.UseForSlot(0);
//	shader.SendUniform("uTex2d", 0);
//	shader.SendUniform("uModelToNDC", FontUtil::to_span(display));
//	shader.SendUniform("uAlpha", alpha);
//	vao.Use();
//	GLDrawIndexed(vao);
//	vao.Use(false);
//	shader.Use(false);
//}

SDL_Color Font::GetColor()
{
    return color;
}


GLTexture Font::createTextTexture(const char* text, TTF_Font* font_, SDL_Color color_)
{
    SDL_Surface* textSurface = TTF_RenderText_Blended(font_, text, color_);
    if (!textSurface)
    {
        Engine::GetLogger().LogError("Failed to render text surface");
    }

    // Convert the SDL_Surface to the desired pixel format (RGBA32)
    SDL_PixelFormat* desiredFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    SDL_Surface* convertedSurface = SDL_ConvertSurface(textSurface, desiredFormat, 0);
    if (!convertedSurface)
    {
        Engine::GetLogger().LogError("Failed to convert text surface to the desired pixel format");
        SDL_FreeSurface(textSurface);
        //throw std::runtime_error{ "Failed to convert the text surface to the desired pixel format" };
    }

    GLTexture texture;
    if (const bool loaded = texture.LoadFromMemory(convertedSurface->w, convertedSurface->h, reinterpret_cast<GLTexture::RGBA*>(convertedSurface->pixels)); !loaded)
    {
        throw std::runtime_error{ "Failed to load the texture font image" };
    }

    // Free the surfaces
    SDL_FreeSurface(convertedSurface);
    SDL_FreeSurface(textSurface);

    return texture;
}


GLTexture Font::GetTexture()
{
	GLTexture texture;
	texture = std::move(textTexture);
	return texture;
}



//void Font::CreateFontscreenQuad()
//{
//	constexpr std::array positions =
//	{
//		vec2(-1.f,1.f), vec2(-1.f,-1.f), vec2(1.0f,-1.0f), vec2(1.f,1.f)
//	};
//	constexpr std::array textures =
//	{
//		vec2{0.0f, 0.0f}, vec2{0.0f, 1.0f},
//		vec2{1.0f, 1.0f}, vec2{1.0f, 0.0f}
//	};
//	constexpr std::array<unsigned char, 4> indices = { 0,1,3,2 };
//
//	GLAttributeLayout position;
//	position.component_type = GLAttributeLayout::Float;
//	position.component_dimension = GLAttributeLayout::_2;
//	position.normalized = false;
//	position.vertex_layout_location = 0;
//	position.stride = sizeof(vec2);
//	position.offset = 0;
//	position.relative_offset = 0;
//
//	GLAttributeLayout texCoordLayout;
//	texCoordLayout.component_type = GLAttributeLayout::Float;
//	texCoordLayout.component_dimension = GLAttributeLayout::_2;
//	texCoordLayout.normalized = false;
//	texCoordLayout.vertex_layout_location = 1;
//	texCoordLayout.stride = sizeof(vec2);
//	texCoordLayout.offset = 0;
//	texCoordLayout.relative_offset = 0;
//
//	vao.AddVertexBuffer(GLVertexBuffer(std::span{ positions }), { position });
//	vao.AddVertexBuffer(GLVertexBuffer(std::span{ textures }), { texCoordLayout });
//	vao.SetPrimitivePattern(GLPrimitive::TriangleStrip);
//	GLIndexBuffer index_buffer(indices);
//	vao.SetIndexBuffer(std::move(index_buffer));
//}
