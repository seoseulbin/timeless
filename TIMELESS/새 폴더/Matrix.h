/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TransformMatrix.h
Project: CS230
Author: Seulbin Seo
Creation date: 04/15/2022
-----------------------------------------------------------------*/
#pragma once
#include "Vec2.h"

namespace DataType
{
	class TransformMatrix
	{
	public:
		TransformMatrix();
		DataType::vec2 operator * (DataType::vec2 rhs) const;
		const double* operator[](int index) const { return matrix[index]; }
		TransformMatrix operator * (TransformMatrix rhs) const;
		TransformMatrix& operator *= (TransformMatrix rhs);
		void Reset();

	protected:
		double matrix[3][3];
	};

	class TranslateMatrix : public TransformMatrix
	{
	public:
		TranslateMatrix(DataType::ivec2 translate);
		TranslateMatrix(DataType::vec2 translate);
	};

	class RotateMatrix : public TransformMatrix
	{
	public:
		RotateMatrix(double radians);
	};

	class ScaleMatrix : public TransformMatrix
	{
	public:
		ScaleMatrix(DataType::vec2 scale);
	};
}



//#pragma once
//#include "Vec2.h"
//#include "Vec3.h"
//
//class Matrix
//{
//
//public:
//
//	float elements[3][3];
//
//	vec3 column0;
//	vec3 column1;
//	vec3 column2;
//
//
//public:
//	constexpr Matrix() noexcept; // initializes to identity matrix
//	constexpr Matrix(vec3 first_column, vec3 second_column, vec3 third_column) noexcept;
//	constexpr Matrix(double column0_row0, double column0_row1, double column0_row2, double column1_row0, double column1_row1, double column1_row2, double column2_row0, double column2_row1,
//		double column2_row2) noexcept;
//
//public:
//	/*const double* operator[](int index) const { return matrix[index]; }
//	Matrix operator * (Matrix rhs) const;
//	DataType::vec2 operator * (DataType::vec2 rhs) const;
//	Matrix& operator *= (Matrix rhs);
//	void Reset();*/
//public:
//	static constexpr Matrix transpose(const Matrix& m) noexcept;
//	static constexpr Matrix build_scale(double scale) noexcept;
//	static constexpr Matrix build_scale(double scale_x, double scale_y) noexcept;
//	static constexpr Matrix build_scale(const DataType::vec2& scale) noexcept;
//	static Matrix           build_rotation(double angle_in_radians) noexcept;
//	static constexpr Matrix build_translation(double translate_x, double translate_y) noexcept;
//	static constexpr Matrix build_translation(const DataType::vec2& translation) noexcept;
//protected:
//	//double matrix[3][3];
//};
//
////static_assert(sizeof(Matrix) == sizeof(double) * 3 * 3, "mat3 should be 3x3 floats");
//
//constexpr Matrix operator*(const Matrix& m1, const Matrix& m2) noexcept;
//constexpr void operator*=(Matrix& m1, const Matrix& m2) noexcept;
//
//constexpr vec3 operator*(const Matrix& m, vec3 v) noexcept;
//
//
