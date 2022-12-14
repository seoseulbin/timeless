#pragma once
#include"Vec2.h"
#include"Matrix.h"
#include"Component.h"
#include"mat3.h"
#include"vec2.h"

class [[nodiscard]] Camera : public Component
{
public:
	DataType::fvec2 position{};

public:
	Camera() noexcept = default;
	Camera(DataType::fvec2 camera_position) noexcept;
	Camera(DataType::fvec2 camera_position, DataType::fvec2 camera_up) noexcept;
	[[nodiscard]] DataType::fvec2 GetUp() const noexcept
	{
		return up;
	}
	[[nodiscard]] DataType::fvec2 GetRight() const noexcept
	{
		return right;
	}
	[[nodiscard]] float GetOrientation() const noexcept
	{
		return orientation;
	}

	void SetUp(DataType::fvec2 camera_up = { 0,1 }) noexcept;
	void SetOrientation(float angle_radians) noexcept;


	void Update(DataType::fvec2 position) noexcept;
	void MoveUp(float distance) noexcept;
	void MoveUp(DataType::fvec2 newPosition) noexcept;
	void MoveRight(float) noexcept;
	void Rotate(float) noexcept;

	DataType::TransformMatrix BuildCameraToWorld() const noexcept;
	
	DataType::TransformMatrix BuildWorldToCamera() const noexcept;
	DataType::TransformMatrix GetMatrix() const noexcept;


	mat3 BuildCameraToWorld_mat3() const noexcept;
	mat3 BuildWorldToCamera_mat3() const noexcept;
private:
	DataType::fvec2 up{ 0,1 };
	DataType::fvec2 right{ 1,0 };
	float orientation{ 0 };
};