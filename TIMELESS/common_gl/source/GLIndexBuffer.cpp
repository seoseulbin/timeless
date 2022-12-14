#include "GLIndexBuffer.h"
#include"glCheck.h"


GLIndexBuffer::GLIndexBuffer(std::span<const unsigned int> indices)
{
	glCheck(glCreateBuffers(1, &indices_handle));
	element_type = GLIndexElement::UInt;
	count = static_cast<GLsizei>(indices.size());
	glCheck(glNamedBufferStorage(indices_handle, indices.size_bytes(), indices.data(), GL_DYNAMIC_STORAGE_BIT));
	
}

GLIndexBuffer::GLIndexBuffer(std::span<const unsigned short> indices)
{
	glCheck(glCreateBuffers(1, &indices_handle));
	element_type = GLIndexElement::UShort;
	count = static_cast<GLsizei>(indices.size());
	glCheck(glNamedBufferStorage(indices_handle, indices.size_bytes(), indices.data(), GL_DYNAMIC_STORAGE_BIT));
}

GLIndexBuffer::GLIndexBuffer(std::span<const unsigned char> indices)
{
	glCheck(glCreateBuffers(1, &indices_handle));
	element_type = GLIndexElement::UByte;
	count = static_cast<GLsizei>(indices.size());
	glCheck(glNamedBufferStorage(indices_handle, indices.size_bytes(), indices.data(), GL_DYNAMIC_STORAGE_BIT));
}


GLIndexBuffer::~GLIndexBuffer()
{
	glCheck(glDeleteBuffers(count, &indices_handle));
}

GLIndexBuffer::GLIndexBuffer(GLIndexBuffer&& temp) noexcept
{
	indices_handle = temp.indices_handle;
	count = temp.count;
	temp.count = 0;
	temp.indices_handle = 0;
}


GLIndexBuffer& GLIndexBuffer::operator=(GLIndexBuffer&& temp) noexcept
{
	if (this != &temp)
	{
		std::swap(indices_handle, temp.indices_handle);
		std::swap(count, temp.count);
	}
	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}


void GLIndexBuffer::Use(bool bind) const
{
	if (bind == true)
	{
		glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_handle));
	}
	else if (bind == false)
	{
		glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}