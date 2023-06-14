#include "Camera.h"
#include "Engine.h"
#include <math.h>

Camera::Camera(DataType::fvec2 camera_position) noexcept
{
	position = camera_position;
}

Camera::Camera(DataType::fvec2 camera_position, DataType::fvec2 camera_up) noexcept
{
	position = camera_position;
	up = camera_up;
}

void Camera::SetUp(DataType::fvec2 camera_up) noexcept
{
	up = camera_up;
}

void Camera::MoveUp(float distance) noexcept
{
	position = position + up * distance;
}

void Camera::MoveUp(DataType::fvec2 newPosition) noexcept
{
	position = newPosition;
	/*position.x = (newPosition.x - 1300 / 2.0f) * (1.0f / (1300 / 2.0f));
	position.y = (newPosition.y - 1300 / 2.0f) * (1.0f / (1300 / 2.0f));*/
	// position = newPosition;

	// ¿©±â¼­ ¼Óµµ Áõ°¨
}

DataType::TransformMatrix Camera::BuildCameraToWorld() const noexcept
{
	DataType::TransformMatrix Cam = DataType::TranslateMatrix(position);
	return Cam;
}

DataType::TransformMatrix Camera::BuildWorldToCamera() const noexcept
{
	/*DataType::TransformMatrix Cam
	{
		1, 0, -position.x,
		0, 1, -position.y,
		0, 0, 1
	};*/
	DataType::fvec2 scale{1.0f, 1.0f};
	// float rotation = 45.f;
	DataType::TransformMatrix Cam = DataType::TranslateMatrix(-position) /* * DataType::RotateMatrix(rotation) * */ * DataType::ScaleMatrix(scale);
	return Cam;
}

mat3 Camera::BuildCameraToWorld_mat3() const noexcept
{
	mat3 Cam = mat3::build_translation(position.x, position.y);
	return Cam;
}

mat3 Camera::BuildWorldToCamera_mat3() const noexcept
{
	// mat3 cam
	//{
	//	1,0,0,
	//	0,1,0,
	//	(position.x - 1300 / 2.0f) * (1.0f / (1300 / 2.0f)), (position.y - 1300 / 2.0f) * (1.0f / (1300 / 2.0f)), 1
	// };
	// mat3 cam = mat3::build_translation(-position.x, -position.y);
	mat3 cam{
		1, 0, 0,
		0, 1, 0,
		-position.x, -position.y, 1};
	return cam;
}