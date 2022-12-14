#pragma once

struct vec3
{
    double x, y, z;
    double red, green, blue;
    double width, height, depth;

    double elements[3];


    constexpr vec3() noexcept;
    constexpr explicit vec3(double repeated_float) noexcept;
    constexpr vec3(double fx, double fy, double fz) noexcept;
};

