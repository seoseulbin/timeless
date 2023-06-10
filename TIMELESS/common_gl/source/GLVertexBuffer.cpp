#include "GLVertexBuffer.h"
#include"glCheck.h"

GLVertexBuffer::GLVertexBuffer(GLsizei size_in_bytes)
{
	glCheck(glCreateBuffers(1, &buffer_handle));
	size = size_in_bytes;
	glCheck(glNamedBufferStorage(buffer_handle, size, nullptr, GL_DYNAMIC_STORAGE_BIT));
}


GLVertexBuffer::~GLVertexBuffer()
{
	//glDeleteBuffers(size, &buffer_handle);
	glCheck(glDeleteBuffers(1, &buffer_handle));
}

GLVertexBuffer::GLVertexBuffer(GLVertexBuffer&& temp) noexcept
{
	buffer_handle = temp.buffer_handle;
	size = temp.size;
	temp.buffer_handle = 0;
	temp.size = 0;
}

GLVertexBuffer& GLVertexBuffer::operator=(GLVertexBuffer&& temp) noexcept
{
	// // O: 여기에 return 문을 삽입합니다.
	if (this != &temp)
	{
		std::swap(buffer_handle, temp.buffer_handle);
		std::swap(size, temp.size);
	}
	return *this;
}


void GLVertexBuffer::Use(bool bind) const
{
	if (bind == true)
	{
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, buffer_handle));
	}
	else if (bind == false)
	{
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}


void GLVertexBuffer::send_buffer_data_to_gpu(const void* data, GLsizei size_bytes, GLsizei starting_offset) const
{
	glCheck(glNamedBufferSubData(buffer_handle, starting_offset, size_bytes, data));
}


