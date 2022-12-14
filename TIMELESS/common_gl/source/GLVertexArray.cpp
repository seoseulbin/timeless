#include "GLVertexArray.h"
#include"glCheck.h"

GLVertexArray::GLVertexArray(GLPrimitive::Type the_primitive_pattern) : primitive_pattern(the_primitive_pattern)
{
	glCheck(glCreateVertexArrays(1, &vertex_array_handle));
}

GLVertexArray::~GLVertexArray()
{
	glCheck(glDeleteVertexArrays(1, &vertex_array_handle));
}

GLVertexArray::GLVertexArray(GLVertexArray&& temp) noexcept
{
	vertex_array_handle = temp.vertex_array_handle;
	std::swap(vertex_buffers, temp.vertex_buffers);
	index_buffer = std::move(temp.index_buffer);
	num_indices = temp.num_indices;
	indices_type = temp.indices_type;
	primitive_pattern = temp.primitive_pattern;
	num_vertices = temp.num_vertices;
	temp.vertex_array_handle = 0;
	temp.vertex_buffers.clear();
	temp.num_indices = 0;
	temp.indices_type = GLIndexElement::None;
	temp.primitive_pattern = GLPrimitive::Triangles;
	temp.num_vertices = 0;
}

GLVertexArray& GLVertexArray::operator=(GLVertexArray&& temp) noexcept
{
	// TODO: 여기에 return 문을 삽입합니다.
	if (this != &temp)
	{
		std::swap(vertex_array_handle, temp.vertex_array_handle);
		std::swap(vertex_buffers, temp.vertex_buffers);
		std::swap(num_indices, temp.num_indices);
		std::swap(index_buffer, temp.index_buffer);
		std::swap(indices_type, temp.indices_type);
		std::swap(primitive_pattern, temp.primitive_pattern);
		std::swap(num_vertices, temp.num_vertices);
	}
	return *this;
}


void GLVertexArray::Use(bool bind) const
{
	if (bind == true)
	{
		glCheck(glBindVertexArray(vertex_array_handle));
	}
	else if (bind == false)
	{
		glCheck(glBindVertexArray(0));
	}
}

void GLVertexArray::AddVertexBuffer(GLVertexBuffer&& vertex_buffer, std::initializer_list<GLAttributeLayout> buffer_layout)
{
	GLHandle handle = vertex_buffer.GetHandle();
	for (const GLAttributeLayout& layout : buffer_layout)
	{
		glCheck(glEnableVertexArrayAttrib(vertex_array_handle, layout.vertex_layout_location));
		glCheck(glVertexArrayVertexBuffer(vertex_array_handle, layout.vertex_layout_location, handle, layout.offset, layout.stride));
		glCheck(glVertexArrayAttribFormat(vertex_array_handle, layout.vertex_layout_location, layout.component_dimension, layout.component_type, layout.normalized, layout.relative_offset));
		glCheck(glVertexArrayAttribBinding(vertex_array_handle, layout.vertex_layout_location, layout.vertex_layout_location));
	}
	vertex_buffers.push_back(std::move(vertex_buffer));
}

void GLVertexArray::SetIndexBuffer(GLIndexBuffer&& the_indices)
{
	num_indices = the_indices.GetCount();
	indices_type = the_indices.GetElementType();
	index_buffer = std::move(the_indices);
	glCheck(glVertexArrayElementBuffer(vertex_array_handle, index_buffer.GetHandle()));
}

void GLDrawIndexed(const GLVertexArray& vertex_array) noexcept
{
	glCheck(glDrawElements(vertex_array.GetPrimitivePattern(), vertex_array.GetIndicesCount(), vertex_array.GetIndicesType(), 0));
}

void GLDrawVertices(const GLVertexArray& vertex_array) noexcept
{
	glCheck(glDrawArrays(vertex_array.GetPrimitivePattern(), 0, vertex_array.GetVertexCount()));
}
