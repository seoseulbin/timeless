#include "Matrix.h"

Matrix::Matrix()
{
	Reset();
}

Matrix Matrix::operator*(Matrix rhs) const
{
	Matrix result;

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

DataType::vec2 Matrix::operator*(DataType::vec2 rhs) const
{
	DataType::vec2 result;
	result.x = matrix[0][0] * rhs.x + matrix[0][1] * rhs.y + matrix[0][2];
	result.y = matrix[1][0] * rhs.x + matrix[1][1] * rhs.y + matrix[1][2];
	return result;
}

Matrix& Matrix::operator*=(Matrix rhs)
{
	(*this) = (*this) * rhs;
	return (*this);
}

void Matrix::Reset()
{
	matrix[0][0] = 1; 	matrix[0][1] = 0; 	matrix[0][2] = 0;
	matrix[1][0] = 0; 	matrix[1][1] = 1; 	matrix[1][2] = 0;
	matrix[2][0] = 0; 	matrix[2][1] = 0; 	matrix[2][2] = 1;
}

TranslateMatrix::TranslateMatrix(DataType::ivec2 translate)
{
	matrix[0][0] = 1; 	matrix[0][1] = 0; 	matrix[0][2] = translate.x;
	matrix[1][0] = 0; 	matrix[1][1] = 1; 	matrix[1][2] = translate.y;
	matrix[2][0] = 0; 	matrix[2][1] = 0; 	matrix[2][2] = 1;
}

TranslateMatrix::TranslateMatrix(DataType::vec2 translate)
{
	matrix[0][0] = 1.0; 	matrix[0][1] = 0.0; 	matrix[0][2] = translate.x;
	matrix[1][0] = 0.0; 	matrix[1][1] = 1.0; 	matrix[1][2] = translate.y;
	matrix[2][0] = 0.0; 	matrix[2][1] = 0.0; 	matrix[2][2] = 1.0;
}

RotateMatrix::RotateMatrix(double radians)
{
	matrix[0][0] = cos(radians); 	matrix[0][1] = -sin(radians);		matrix[0][2] = 0.0;
	matrix[1][0] = sin(radians); 	matrix[1][1] = cos(radians); 		matrix[1][2] = 0.0;
	matrix[2][0] = 0.0; 			matrix[2][1] = 0.0; 				matrix[2][2] = 1.0;
}

ScaleMatrix::ScaleMatrix(DataType::vec2 scale)
{
	matrix[0][0] = scale.x; 	matrix[0][1] = 0.0; 		matrix[0][2] = 0.0;
	matrix[1][0] = 0.0; 		matrix[1][1] = scale.y; 	matrix[1][2] = 0.0;
	matrix[2][0] = 0.0; 		matrix[2][1] = 0.0; 		matrix[2][2] = 1.0;
}