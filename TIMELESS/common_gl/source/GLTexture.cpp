/*
 * minseok.kim
 * CS200
 * Fall 2022
 */
#include"GLTexture.h"
#include"glCheck.h"
#include<stb_image.h>
#include<string>

GLTexture::~GLTexture() noexcept
{
	delete_texture();
}

void GLTexture::delete_texture() noexcept
{
	glDeleteTextures(1, &texture_handle);
	//glDeleteTextures(1, &texture_handle);
	texture_handle = 0;
	width = 0;
	height = 0;
}

GLTexture::GLTexture(GLTexture&& other) noexcept
{
	texture_handle = other.texture_handle;
	width = other.width;
	height = other.height;
	other.texture_handle = 0;
	other.width = 0;
	other.height = 0;
}

GLTexture& GLTexture::operator=(GLTexture&& other) noexcept
{
	if (this != &other)
	{
		std::swap(texture_handle, other.texture_handle);
		std::swap(width, other.width);
		std::swap(height, other.height);
	}
	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}

bool GLTexture::LoadFromFileImage(const std::filesystem::path& image_filepath, bool flip_vertical) noexcept
{
	int channel;
	bool check = false;
	std::string filename = image_filepath.generic_string();
	stbi_set_flip_vertically_on_load(flip_vertical);
	
	unsigned char* ptr_texels = stbi_load(filename.c_str(), &width, &height, &channel, 0);
	if (LoadFromMemory(width, height, (RGBA*)(ptr_texels)) == flip_vertical)
	{
		check = true;
	}
	stbi_image_free(ptr_texels);
	if (check)
	{
		return true;
	}
	else
		return false;
}


bool GLTexture::LoadFromMemory(int image_width, int image_height, const RGBA* colors) noexcept
{
	delete_texture();
	width = image_width;
	height = image_height;
	//char* ptr_texels = new char[width * height * 4];


	//GLuint texobj_hdl;
	//glCheck(glCreateTextures(GL_TEXTURE_2D, 1, &texture_handle));
	glCreateTextures(GL_TEXTURE_2D, 1 ,&texture_handle);

	constexpr GLsizei ONE_TEXTURE_LEVEL = 1;
	//glCheck(glTextureStorage2D(texture_handle, ONE_TEXTURE_LEVEL, GL_RGBA8, width, height));
	glTextureStorage2D(texture_handle, ONE_TEXTURE_LEVEL, GL_RGBA8, width, height);

	constexpr GLint FIRST_LEVEL = 0;
	constexpr GLsizei OFFSET_X = 0, OFFSET_Y = 0;
	//glCheck(glTextureSubImage2D(texture_handle, FIRST_LEVEL, OFFSET_X, OFFSET_Y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, colors));
	glTextureSubImage2D(texture_handle, FIRST_LEVEL, OFFSET_X, OFFSET_Y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, colors);


	//SetFiltering(Filtering::NearestPixel);
	//SetWrapping(Wrapping::Repeat, Coordinate::Both);

	return true;
}

void GLTexture::SetFiltering(Filtering how_to_filter) noexcept
{
	if (texture_handle == 0)
		return;

	filtering = how_to_filter;

	if (filtering == Filtering::NearestPixel)
	{
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	}
	else if (filtering == Filtering::Linear)
	{
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	}
}


void GLTexture::SetWrapping(Wrapping how_to_wrap, Coordinate coord) noexcept
{
	if (texture_handle == 0)
		return;

	switch (coord)
	{
	case Coordinate::Both:
		glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_S, how_to_wrap));
		glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_S, how_to_wrap));
		break;
	case Coordinate::S:
		glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_S, how_to_wrap));
		break;
	case Coordinate::T:
		glCheck(glTextureParameteri(texture_handle, GL_TEXTURE_WRAP_T, how_to_wrap));
		break;
	}
}

void GLTexture::UseForSlot(unsigned int texture_unit) const noexcept
{
	glCheck(glBindTextureUnit(texture_unit, texture_handle););
}