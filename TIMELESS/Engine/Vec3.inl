#include "Vec3.h"

constexpr vec3::vec3() noexcept : vec3(0.0)
{
}

constexpr vec3::vec3(double repeated_float) noexcept : vec3(repeated_float, repeated_float, repeated_float)
{
}

constexpr vec3::vec3(double fx, double fy, double fz) noexcept : x(fx), y(fy), z(fz)
{
}
