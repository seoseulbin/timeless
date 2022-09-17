#pragma once
#include"Vec2.h"

class Matrix
{
public:
	Matrix();

	const double* operator[](int index) const { return matrix[index]; }
	Matrix operator * (Matrix rhs) const;
	DataType::vec2 operator * (DataType::vec2 rhs) const;
	Matrix& operator *= (Matrix rhs);
	void Reset();

protected:
	double matrix[3][3];
};

class TranslateMatrix : public Matrix
{
public:
	TranslateMatrix(DataType::ivec2 translate);
	TranslateMatrix(DataType::vec2 translate);
};


class RotateMatrix : public Matrix
{
public:
	RotateMatrix(double radians);
};

class ScaleMatrix : public Matrix
{
public :
	ScaleMatrix(DataType::vec2 scale);
};