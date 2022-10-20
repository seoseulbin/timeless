/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TransformMatrix.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 04/15/2022
-----------------------------------------------------------------*/
#include "Matrix.h"

DataType::TransformMatrix::TransformMatrix()
{
	Reset();
}

void DataType::TransformMatrix::Reset()
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

DataType::TranslateMatrix::TranslateMatrix(DataType::ivec2 translate)
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = translate.x;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = translate.y;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;

}

DataType::TranslateMatrix::TranslateMatrix(DataType::vec2 translate)
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = translate.x;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = translate.y;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

DataType::RotateMatrix::RotateMatrix(double radians)
{
	matrix[0][0] = cos(radians);
	matrix[0][1] = -sin(radians);
	matrix[0][2] = 0;
	matrix[1][0] = sin(radians);
	matrix[1][1] = cos(radians);
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

DataType::ScaleMatrix::ScaleMatrix(DataType::vec2 scale)
{
	matrix[0][0] = scale.x;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = scale.y;
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

DataType::TransformMatrix DataType::TransformMatrix::operator*(TransformMatrix rhs) const
{
	TransformMatrix result;

	result.matrix[0][0] = matrix[0][0] * rhs[0][0] + matrix[0][1] * rhs[1][0] + matrix[0][2] * rhs[2][0];
	result.matrix[0][1] = matrix[0][0] * rhs[0][1] + matrix[0][1] * rhs[1][1] + matrix[0][2] * rhs[2][1];
	result.matrix[0][2] = matrix[0][0] * rhs[0][2] + matrix[0][1] * rhs[1][2] + matrix[0][2] * rhs[2][2];
	result.matrix[1][0] = matrix[1][0] * rhs[0][0] + matrix[1][1] * rhs[1][0] + matrix[1][2] * rhs[2][0];
	result.matrix[1][1] = matrix[1][0] * rhs[0][1] + matrix[1][1] * rhs[1][1] + matrix[1][2] * rhs[2][1];
	result.matrix[1][2] = matrix[1][0] * rhs[0][2] + matrix[1][1] * rhs[1][2] + matrix[1][2] * rhs[2][2];
	result.matrix[2][0] = matrix[2][0] * rhs[0][0] + matrix[2][1] * rhs[1][0] + matrix[2][2] * rhs[2][0];
	result.matrix[2][1] = matrix[2][0] * rhs[0][1] + matrix[2][1] * rhs[1][1] + matrix[2][2] * rhs[2][1];
	result.matrix[2][2] = matrix[2][0] * rhs[0][2] + matrix[2][1] * rhs[1][2] + matrix[2][2] * rhs[2][2];

	return result;
}

DataType::vec2 DataType::TransformMatrix::operator * (DataType::vec2 rhs) const
{
	DataType::vec2 result;
	result.x = matrix[0][0] * rhs.x + matrix[0][1] * rhs.y + matrix[0][2];
	result.y = matrix[1][0] * rhs.x + matrix[1][1] * rhs.y + matrix[1][2];
	return result;
}

DataType::TransformMatrix& DataType::TransformMatrix::operator*=(DataType::TransformMatrix rhs)
{
	(*this) = (*this) * rhs;
	return (*this);
}




//#include "Matrix.h"
//
//constexpr Matrix::Matrix() noexcept : Matrix(vec3{ 1, 0, 0 }, vec3{ 0, 1, 0 }, vec3{ 0, 0, 1 })
//{
//}
//
//constexpr Matrix::Matrix(vec3 first_column, vec3 second_column, vec3 third_column) noexcept : column0(first_column), column1(second_column), column2(third_column)
//{
//}
//
//constexpr Matrix::Matrix(double column0_row0, double column0_row1, double column0_row2, double column1_row0, double column1_row1, double column1_row2, double column2_row0, double column2_row1,
//	double column2_row2) noexcept
//	: column0{ column0_row0, column0_row1, column0_row2 }, column1{ column1_row0, column1_row1, column1_row2 }, column2{ column2_row0, column2_row1, column2_row2 }
//{
//}
//
//constexpr Matrix operator*(const Matrix& m1, const Matrix& m2) noexcept
//{
//	Matrix results;
//	results.elements[0][0] = m1.elements[0][0] * m2.elements[0][0] + m1.elements[1][0] * m2.elements[0][1] + m1.elements[2][0] * m2.elements[0][2];
//	results.elements[0][1] = m1.elements[0][1] * m2.elements[0][0] + m1.elements[1][1] * m2.elements[0][1] + m1.elements[2][1] * m2.elements[0][2];
//	results.elements[0][2] = m1.elements[0][2] * m2.elements[0][0] + m1.elements[1][2] * m2.elements[0][1] + m1.elements[2][2] * m2.elements[0][2];
//	results.elements[1][0] = m1.elements[0][0] * m2.elements[1][0] + m1.elements[1][0] * m2.elements[1][1] + m1.elements[2][0] * m2.elements[1][2];
//	results.elements[1][1] = m1.elements[0][1] * m2.elements[1][0] + m1.elements[1][1] * m2.elements[1][1] + m1.elements[2][1] * m2.elements[1][2];
//	results.elements[1][2] = m1.elements[0][2] * m2.elements[1][0] + m1.elements[1][2] * m2.elements[1][1] + m1.elements[2][2] * m2.elements[1][2];
//	results.elements[2][0] = m1.elements[0][0] * m2.elements[2][0] + m1.elements[1][0] * m2.elements[2][1] + m1.elements[2][0] * m2.elements[2][2];
//	results.elements[2][1] = m1.elements[0][1] * m2.elements[2][0] + m1.elements[1][1] * m2.elements[2][1] + m1.elements[2][1] * m2.elements[2][2];
//	results.elements[2][2] = m1.elements[0][2] * m2.elements[2][0] + m1.elements[1][2] * m2.elements[2][1] + m1.elements[2][2] * m2.elements[2][2];
//	return results;
//}
//
//constexpr void operator*=(Matrix& m1, const Matrix& m2) noexcept
//{
//	m1 = m1 * m2;
//}
//
//constexpr vec3 operator*(const Matrix& m, vec3 v) noexcept
//{
//	return { m.elements[0][0] * v.x + m.elements[1][0] * v.y + m.elements[2][0] * v.z, m.elements[0][1] * v.x + m.elements[1][1] * v.y + m.elements[2][1] * v.z,
//			m.elements[0][2] * v.x + m.elements[1][2] * v.y + m.elements[2][2] * v.z };
//}
//
//
//constexpr Matrix Matrix::transpose(const Matrix& m) noexcept
//{
//	return { {m.elements[0][0], m.elements[1][0], m.elements[2][0]}, {m.elements[0][1], m.elements[1][1], m.elements[2][1]}, {m.elements[0][2], m.elements[1][2], m.elements[2][2]} };
//}
//
//
//constexpr Matrix Matrix::build_scale(double scale_x, double scale_y) noexcept
//{
//	return { scale_x, 0.0, 0.0, 0.0, scale_y, 0.0, 0.0, 0.0, 1.0 };
//}
//
//constexpr Matrix Matrix::build_scale(double scale) noexcept
//{
//	return build_scale(scale, scale);
//}
//
//constexpr Matrix Matrix::build_scale(const DataType::vec2& scale) noexcept
//{
//	return build_scale(scale.width, scale.height);
//}
//
//constexpr Matrix Matrix::build_translation(double translate_x, double translate_y) noexcept
//{
//	return { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, translate_x, translate_y, 1.0 };
//}
//
//constexpr Matrix Matrix::build_translation(const DataType::vec2& translation) noexcept
//{
//	return build_translation(translation.x, translation.y);
//}

