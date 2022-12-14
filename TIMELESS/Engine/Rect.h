#pragma once
#pragma once
#include"Vec2.h"
#include"vec2.h"
#include<algorithm>
#include<limits>

namespace DataType
{
	struct [[nodiscard]] rect2
	{
		vec2 point1{ 0.0, 0.0 };
		vec2 point2{ 0.0,0.0 };

		constexpr vec2 Size() const noexcept
		{
			return { Right() - Left(), Top() - Bottom() };
		}

		constexpr double Left() const noexcept
		{
			return std::min(point1.x, point2.x);
		}

		constexpr double Right() const noexcept
		{
			return std::max(point1.x, point2.x);
		}

		constexpr double Top() const noexcept
		{
			return std::max(point1.y, point2.y);
		}

		constexpr double Bottom() const noexcept
		{
			return std::min(point1.y, point2.y);
		}
	};

	struct [[nodiscard]] frect2
	{
		fvec2 point1{ 0.0f, 0.0f };
		fvec2 point2{ 0.0f, 0.0f };

		constexpr fvec2 Size() const noexcept
		{
			return { Left() - Right(), Top() - Bottom() };
		}

		constexpr float Left() const noexcept
		{
			return std::min(point1.x, point2.x);
			//return std::max(point1.x, point2.x);
		}

		constexpr float Right() const noexcept
		{
			return std::max(point1.x, point2.x);
			//return std::min(point1.x, point2.x);
		}

		constexpr float Top() const noexcept
		{
			return std::min(point1.y, point2.y); //여기에 min 드가고
			//return std::max(point1.y, point2.y);
		}

		constexpr float Bottom() const noexcept
		{
			return std::max(point1.y, point2.y);  //여따가 max써야 하지 않냐
			//return std::min(point1.y, point2.y);
		}
	};

	struct [[nodiscard]] irect2
	{
		ivec2 point1{ 0, 0 };
		ivec2 point2{ 0,0 };

		constexpr ivec2 Size() const noexcept
		{
			return { Right() - Left(), Top() - Bottom() };
		}
		constexpr int Left() const noexcept
		{
			return std::min(point1.x, point2.x);
		}
		constexpr int Right() const noexcept
		{
			return std::max(point1.x, point2.x);
		}
		constexpr int Top() const noexcept
		{
			return std::max(point1.y, point2.y);
		}
		constexpr int Bottom() const noexcept
		{
			return std::min(point1.y, point2.y);
		}
	};
}

//struct vect2
//{
//	vec2 point1{ 0,0 };
//	vec2 point2{ 0,0 };
//
//	vect2(DataType::frect2 rect)
//	{
//		point1.x = rect.point1.x;
//		point1.y = rect.point1.y;
//		point2.x = rect.point2.x;
//		point2.y = rect.point2.y;
//	}
//
//	constexpr vec2 Size() const noexcept
//	{
//		return { Right() - Left(), Top() - Bottom() };
//	}
//	constexpr float Left() const noexcept
//	{
//		return std::min(point1.x, point2.x);
//	}
//	constexpr float Right() const noexcept
//	{
//		return std::max(point1.x, point2.x);
//	}
//	constexpr float Top() const noexcept
//	{
//		return std::max(point1.y, point2.y);
//	}
//	constexpr float Bottom() const noexcept
//	{
//		return std::min(point1.y, point2.y);
//	}
//
//};