/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.h
Creation date: 2022-03-21
Name : minseok.kim
Assignment name : CS170 Math Assignment
Course name : CS170
Term : 2022 Spring
-----------------------------------------------------------------*/
#pragma once
#include <cmath>
#include <limits>

namespace DataType
{
    [[nodiscard]] constexpr double abs(double d) noexcept { return (d < 0.0) ? -d : d; }

    [[nodiscard]] constexpr float abs(float f) noexcept { return (f < 0.0f) ? -f : f; }

    [[nodiscard]] constexpr bool is_equal(double d1, double d2) noexcept
    {
        return abs(d1 - d2) <= std::numeric_limits<double>::epsilon() * abs(d1 + d2);
    }

    [[nodiscard]] constexpr bool is_equal(float f1, float f2) noexcept
    {
        return abs(f1 - f2) <= std::numeric_limits<float>::epsilon() * abs(f1 + f2);
    }

    [[nodiscard]] constexpr bool is_equal(int i1, int i2) noexcept { return i1 == i2; }

    struct vec2
    {
    public:
        double x = 0;
        double y = 0;

        [[nodiscard]] constexpr vec2() noexcept = default;
        [[nodiscard]] explicit constexpr vec2(double value) noexcept : vec2(value, value) {}
        [[nodiscard]] constexpr vec2(double xValue, double yValue) noexcept : x(xValue), y(yValue) {}

        constexpr vec2 &operator+=(vec2 vec) noexcept;

        constexpr friend vec2 operator+(vec2 vec, vec2 vec_2) noexcept;

        constexpr vec2 &operator-=(vec2 vec) noexcept;

        constexpr friend vec2 operator-(vec2 vec, vec2 vec_2) noexcept;

        constexpr friend vec2 operator-(vec2 vec) noexcept;

        constexpr vec2 &operator*=(double v) noexcept;

        constexpr friend vec2 operator*(vec2 vec, vec2 vec_2) noexcept;

        constexpr friend vec2 operator*(vec2 vec, double value) noexcept;

        constexpr friend vec2 operator*(double value, vec2 vec) noexcept;

        constexpr vec2 &operator/=(double value) noexcept;

        constexpr friend vec2 operator/(vec2 vec, double value) noexcept;

        constexpr friend bool operator==(vec2 vec, vec2 vec_2) noexcept;

        constexpr friend bool operator!=(vec2 vec, vec2 vec_2) noexcept;

        [[nodiscard]] constexpr double LengthSquared() const noexcept;
        [[nodiscard]] vec2 Normalize() const noexcept
        {
            double length = std::sqrt(LengthSquared());
            return {x / length, y / length};
        }

        [[nodiscard]] double get_vec2_distance(vec2 vec, vec2 vec_2) noexcept
        {
            double distance = std::sqrt(std::pow(vec.x - vec_2.x, 2) + std::pow(vec.y - vec_2.y, 2));
            return distance;
        }
    };

    // Add float type

    struct fvec2
    {
    public:
        float x = 0.f;
        float y = 0.f;

        [[nodiscard]] constexpr fvec2() noexcept = default;
        [[nodiscard]] explicit constexpr fvec2(float value) noexcept : fvec2(value, value) {}
        [[nodiscard]] constexpr fvec2(float xvalue, float yvalue) noexcept : x(xvalue), y(yvalue) {}

        constexpr fvec2 &operator+=(fvec2 fvec) noexcept;

        constexpr friend fvec2 operator+(fvec2 vec, fvec2 vec_2) noexcept;

        constexpr fvec2 &operator+(float value) noexcept;

        constexpr fvec2 &operator-=(fvec2 vec) noexcept;

        constexpr friend fvec2 operator-(fvec2 vec, fvec2 vec_2) noexcept;

        constexpr friend fvec2 operator-(fvec2 vec) noexcept;

        constexpr fvec2 &operator*=(int v) noexcept;

        constexpr friend fvec2 operator*(fvec2 vec, int value) noexcept;

        constexpr friend fvec2 operator*(int value, fvec2 vec) noexcept;

        constexpr fvec2 &operator/=(int value) noexcept;

        constexpr friend fvec2 operator/(fvec2 vec, int value) noexcept;

        constexpr friend fvec2 operator*(double value, fvec2 vec) noexcept;
        constexpr friend fvec2 operator*(fvec2 vec, double value) noexcept;
        constexpr friend fvec2 operator/(fvec2 vec, double value) noexcept;

        constexpr friend bool operator==(fvec2 vec, fvec2 vec_2) noexcept;

        constexpr friend bool operator!=(fvec2 vec, fvec2 vec_2) noexcept;

        [[nodiscard]] float get_fvec2_distance(fvec2 vec, fvec2 vec_2) noexcept
        {
            float distance = std::sqrtf(std::powf(vec.x - vec_2.x, 2.f) + std::powf(vec.y - vec_2.y, 2.f));
            return distance;
        }
    };

    struct ivec2
    {
    public:
        int x = 0;
        int y = 0;

        [[nodiscard]] constexpr ivec2() noexcept = default;
        [[nodiscard]] explicit constexpr ivec2(int value) noexcept : ivec2(value, value) {}
        [[nodiscard]] constexpr ivec2(int xvalue, int yvalue) noexcept : x(xvalue), y(yvalue) {}

        constexpr ivec2 &operator+=(ivec2 ivec) noexcept;

        constexpr friend ivec2 operator+(ivec2 vec, ivec2 vec_2) noexcept;

        constexpr ivec2 &operator-=(ivec2 vec) noexcept;

        constexpr friend ivec2 operator-(ivec2 vec, ivec2 vec_2) noexcept;

        constexpr friend ivec2 operator-(ivec2 vec) noexcept;

        constexpr ivec2 &operator*=(int v) noexcept;

        constexpr friend ivec2 operator*(ivec2 vec, int value) noexcept;

        constexpr friend ivec2 operator*(int value, ivec2 vec) noexcept;

        constexpr ivec2 &operator/=(int value) noexcept;

        constexpr friend ivec2 operator/(ivec2 vec, int value) noexcept;

        constexpr friend vec2 operator*(double value, ivec2 vec) noexcept;
        constexpr friend vec2 operator*(ivec2 vec, double value) noexcept;
        constexpr friend vec2 operator/(ivec2 vec, double value) noexcept;

        constexpr friend bool operator==(ivec2 vec, ivec2 vec_2) noexcept;

        constexpr friend bool operator!=(ivec2 vec, ivec2 vec_2) noexcept;

        operator vec2()
        {
            return DataType::vec2{static_cast<double>(x), static_cast<double>(y)};
        }
        operator fvec2()
        {
            return DataType::fvec2{static_cast<float>(x), static_cast<float>(y)};
        }
    };

}

#include "Vec2.inl"