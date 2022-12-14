
namespace DataType
{
	constexpr vec2& DataType::vec2::operator+=(vec2 vec) noexcept
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}
	constexpr vec2 DataType::operator+ (vec2 vec, vec2 vec_2) noexcept
	{
		return vec2(vec.x + vec_2.x, vec.y + vec_2.y);
	}
	constexpr vec2& DataType::vec2::operator-=(vec2 vec) noexcept
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	constexpr vec2 DataType::operator- (vec2 vec, vec2 vec_2) noexcept
	{
		return vec2(vec.x - vec_2.x, vec.y - vec_2.y);
	}
	constexpr vec2 DataType::operator - (vec2 vec) noexcept
	{
		return vec2(-vec.x, -vec.y);
	}
	constexpr vec2& DataType::vec2::operator*=(double value) noexcept
	{
		x *= value;
		y *= value;
		return *this;
	}
	constexpr vec2 DataType::operator*(vec2 vec, double value) noexcept
	{
		return vec2(vec.x * value, vec.y * value);
	}
	constexpr vec2 DataType::operator*(double value, vec2 vec) noexcept
	{
		return vec2(value * vec.x, value * vec.y);
	}
	constexpr vec2 DataType::operator*(vec2 vec, vec2 vec_2) noexcept
	{
		return vec2(vec.x * vec_2.x, vec.y * vec_2.y);
	}

	constexpr vec2& DataType::vec2::operator/=(double value) noexcept
	{
		x /= value;
		y /= value;
		return *this;
	}
	constexpr vec2 DataType::operator/(vec2 vec, double value) noexcept
	{
		return vec2(vec.x / value, vec.y / value);
	}
	constexpr bool DataType::operator==(vec2 vec, vec2 vec_2) noexcept
	{
		return is_equal(vec.x, vec_2.x) == is_equal(vec.y, vec_2.y);
	}
	constexpr bool DataType::operator!=(vec2 vec, vec2 vec_2) noexcept
	{
		return (!is_equal(vec.x, vec_2.x) || !is_equal(vec.y, vec_2.y));
	}

	constexpr double vec2::LengthSquared() const noexcept
	{
		return x * x + y * y;
	}
	//inline constexpr vec2 DataType::vec2::Normalize() const noexcept
	//{
	//	double length = std::sqrt(vec2::LengthSquared());
	//	return { x / length, y / length };
	//}


	constexpr ivec2& DataType::ivec2::operator+=(ivec2 ivec) noexcept
	{
		x += ivec.x;
		y += ivec.y;
		return *this;
	}
	constexpr ivec2 DataType::operator+(ivec2 vec, ivec2 vec_2) noexcept
	{
		return ivec2(vec.x + vec_2.x, vec.y + vec_2.y);
	}
	constexpr ivec2& DataType::ivec2::operator-=(ivec2 vec) noexcept
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	constexpr ivec2 DataType::operator-(ivec2 vec, ivec2 vec_2) noexcept
	{
		return ivec2(vec.x - vec_2.x, vec.y - vec_2.y);
	}
	constexpr ivec2 DataType::operator-(ivec2 vec) noexcept
	{
		return ivec2(-vec.x, -vec.y);
	}
	constexpr ivec2& DataType::ivec2::operator*=(int v) noexcept
	{
		x *= v;
		y *= v;
		return *this;
	}
	constexpr ivec2 DataType::operator*(ivec2 vec, int value) noexcept
	{
		return ivec2(vec.x * value, vec.y * value);
	}
	constexpr ivec2 DataType::operator*(int value, ivec2 vec) noexcept
	{
		return ivec2(value * vec.x, value * vec.y);
	}
	constexpr ivec2& DataType::ivec2::operator/=(int value) noexcept
	{
		x /= value;
		y /= value;
		return *this;
	}
	constexpr ivec2 DataType::operator/(ivec2 vec, int value) noexcept
	{
		return ivec2(vec.x / value, vec.y / value);
	}
	constexpr bool DataType::operator==(ivec2 vec, ivec2 vec_2) noexcept
	{
		return is_equal(vec.x, vec_2.x) == is_equal(vec.y, vec_2.y);
	}
	constexpr bool DataType::operator!=(ivec2 vec, ivec2 vec_2) noexcept
	{
		return (!is_equal(vec.x, vec_2.x) || !is_equal(vec.y, vec_2.y));
	}


	constexpr vec2 DataType::operator*(double value, ivec2 vec) noexcept
	{
		return vec2(value * vec.x, value * vec.y);
	}
	constexpr vec2 DataType::operator*(ivec2 vec, double value) noexcept
	{
		return vec2(vec.x * value, vec.y * value);
	}
	constexpr vec2 DataType::operator/(ivec2 vec, double value) noexcept
	{
		return vec2(vec.x / value, vec.y / value);
	}




	// float type

	constexpr fvec2& DataType::fvec2::operator+=(fvec2 fvec) noexcept
	{
		x += fvec.x;
		y += fvec.y;
		return *this;
		// TODO: 여기에 return 문을 삽입합니다.
	}
	constexpr fvec2 DataType::operator+(fvec2 vec, fvec2 vec_2) noexcept
	{
		return fvec2(vec.x + vec_2.x , vec.y + vec_2.y);
	}

	constexpr fvec2& DataType::fvec2::operator+(float value) noexcept
	{
		x += value;
		y += value;

		return *this;
	}

	constexpr fvec2& DataType::fvec2::operator-=(fvec2 vec) noexcept
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
		// TODO: 여기에 return 문을 삽입합니다.
	}
	constexpr fvec2 DataType::operator-(fvec2 vec, fvec2 vec_2) noexcept
	{
		return fvec2(vec.x - vec_2.x, vec.y - vec_2.y);
	}
	constexpr fvec2 DataType::operator-(fvec2 vec) noexcept
	{
		return fvec2(-vec.x, -vec.y);
	}
	constexpr fvec2& DataType::fvec2::operator*=(int v) noexcept
	{
		x *= v;
		y *= v;
		return *this;
		// TODO: 여기에 return 문을 삽입합니다.
	}
	constexpr fvec2 DataType::operator*(fvec2 vec, int value) noexcept
	{
		return fvec2(vec.x * value, vec.y * value);
	}
	constexpr fvec2 DataType::operator*(int value, fvec2 vec) noexcept
	{
		return fvec2(value * vec.x, value * vec.y);
	}
	constexpr fvec2& DataType::fvec2::operator/=(int value) noexcept
	{
		x /= value;
		y /= value;
		return *this;
		// TODO: 여기에 return 문을 삽입합니다.
	}
	constexpr fvec2 DataType::operator/(fvec2 vec, int value) noexcept
	{
		return fvec2(vec.x / value, vec.y / value);
	}

	constexpr fvec2 DataType::operator*(double value, fvec2 vec) noexcept
	{
		return fvec2(static_cast<float>(value) * vec.x, static_cast<float>(value) * vec.y);
	}
	constexpr fvec2 DataType::operator*(fvec2 vec, double value) noexcept
	{
		return fvec2(vec.x * static_cast<float>(value), vec.y * static_cast<float>(value));
	}
	constexpr fvec2 DataType::operator/(fvec2 vec, double value) noexcept
	{
		return fvec2(vec.x / static_cast<float>(value), vec.y / static_cast<float>(value));
	}
	constexpr bool DataType::operator==(fvec2 vec, fvec2 vec_2) noexcept
	{
		return is_equal(vec.x, vec_2.x) == is_equal(vec.y, vec_2.y);
	}
	constexpr bool DataType::operator!=(fvec2 vec, fvec2 vec_2) noexcept
	{
		return (!is_equal(vec.x, vec_2.x) || !is_equal(vec.y, vec_2.y));
	}
}
