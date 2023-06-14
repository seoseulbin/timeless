#include "Matrix.h"

DataType::TransformMatrix::TransformMatrix() noexcept
{
	Reset();
}

DataType::TransformMatrix::TransformMatrix(
	float x, float y, float z,
	float x1, float y1, float z1,
	float x2, float y2, float z2) noexcept
{
	matrix[0][0] = x;
	matrix[0][1] = y;
	matrix[0][2] = z;
	matrix[1][0] = x1;
	matrix[1][1] = y1;
	matrix[1][2] = z1;
	matrix[2][0] = x2;
	matrix[2][1] = y2;
	matrix[2][2] = z2;
}

void DataType::TransformMatrix::Reset()
{
	matrix[0][0] = 1.f;
	matrix[0][1] = 0.f;
	matrix[0][2] = 0.f;
	matrix[1][0] = 0.f;
	matrix[1][1] = 1.f;
	matrix[1][2] = 0.f;
	matrix[2][0] = 0.f;
	matrix[2][1] = 0.f;
	matrix[2][2] = 1.f;
}

DataType::TranslateMatrix::TranslateMatrix(DataType::ivec2 translate)
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = (float)translate.x;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = (float)translate.y;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

DataType::TranslateMatrix::TranslateMatrix(DataType::vec2 translate)
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = static_cast<float>(translate.x);
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = static_cast<float>(translate.y);
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

DataType::TranslateMatrix::TranslateMatrix(DataType::fvec2 translate)
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

// DataType::RotateMatrix::RotateMatrix(double radians)
//{
//	matrix[0][0] = cos(radians);	matrix[0][1] = -sin(radians);	matrix[0][2] = 0;
//	matrix[1][0] = sin(radians);	matrix[1][1] = cos(radians);	matrix[1][2] = 0;
//	matrix[2][0] = 0;				matrix[2][1] = 0;				matrix[2][2] = 1;
// }

DataType::RotateMatrix::RotateMatrix(float radians)
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

// DataType::ScaleMatrix::ScaleMatrix(DataType::vec2 scale)
//{
//	matrix[0][0] = scale.x;	matrix[0][1] = 0;		matrix[0][2] = 0;
//	matrix[1][0] = 0;		matrix[1][1] = scale.y;	matrix[1][2] = 0;
//	matrix[2][0] = 0;		matrix[2][1] = 0;		matrix[2][2] = 1;
// }

DataType::ScaleMatrix::ScaleMatrix(DataType::fvec2 scale)
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

DataType::fvec2 DataType::TransformMatrix::operator*(DataType::fvec2 rhs) const
{
	DataType::fvec2 result;
	result.x = matrix[0][0] * rhs.x + matrix[0][1] * rhs.y + matrix[0][2];
	result.y = matrix[1][0] * rhs.x + matrix[1][1] * rhs.y + matrix[1][2];
	return result;
}

DataType::TransformMatrix &DataType::TransformMatrix::operator*=(DataType::TransformMatrix rhs)
{
	(*this) = (*this) * rhs;
	return (*this);
}
