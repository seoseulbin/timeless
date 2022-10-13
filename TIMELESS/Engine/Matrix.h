#pragma once
#include "Vec2.h"
#include "Vec3.h"

class Matrix
{

public:

		float elements[3][3];

			vec3 column0;
			vec3 column1;
			vec3 column2;


public:
	constexpr Matrix() noexcept; // initializes to identity matrix
	constexpr Matrix(vec3 first_column, vec3 second_column, vec3 third_column) noexcept;
	constexpr Matrix(double column0_row0, double column0_row1, double column0_row2, double column1_row0, double column1_row1, double column1_row2, double column2_row0, double column2_row1,
		double column2_row2) noexcept;

public:
	/*const double* operator[](int index) const { return matrix[index]; }
	Matrix operator * (Matrix rhs) const;
	DataType::vec2 operator * (DataType::vec2 rhs) const;
	Matrix& operator *= (Matrix rhs);
	void Reset();*/
public:
	static constexpr Matrix transpose(const Matrix& m) noexcept;
	static constexpr Matrix build_scale(double scale) noexcept;
	static constexpr Matrix build_scale(double scale_x, double scale_y) noexcept;
	static constexpr Matrix build_scale(const DataType::vec2& scale) noexcept;
	static Matrix           build_rotation(double angle_in_radians) noexcept;
	static constexpr Matrix build_translation(double translate_x, double translate_y) noexcept;
	static constexpr Matrix build_translation(const DataType::vec2& translation) noexcept;
protected:
	//double matrix[3][3];
};

//static_assert(sizeof(Matrix) == sizeof(double) * 3 * 3, "mat3 should be 3x3 floats");

constexpr Matrix operator*(const Matrix& m1, const Matrix& m2) noexcept;
constexpr void operator*=(Matrix& m1, const Matrix& m2) noexcept;

constexpr vec3 operator*(const Matrix& m, vec3 v) noexcept;

////////////////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////////////////

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
