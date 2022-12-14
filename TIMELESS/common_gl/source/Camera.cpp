/*
 * minseok.kim
 * CS200
 * Fall 2022
 */
#include"Camera.h"
#include<math.h>

Camera::Camera(vec2 camera_position, vec2 camera_up) noexcept
{
	Position = camera_position;
	IsFirstPerson = false;
	up = camera_up;
	right = perpendicular_to(up);
	orientation = (float)atan2(right.x, right.y);
}

void Camera::SetUp(vec2 camera_up) noexcept
{
	up = camera_up;
	right = perpendicular_to(up);
	orientation = (float)atan2(right.x, right.y);
}

void Camera::SetOrientation(float angle_radians) noexcept
{
	orientation = angle_radians;
	up = { (float)cos(orientation),(float)sin(orientation) };
	right = perpendicular_to(up);
}

void Camera::MoveUp(float distance) noexcept
{
	Position = Position + up * distance;
}

void Camera::MoveRight(float distance) noexcept
{
	Position = Position + right * distance;
}

void Camera::Rotate(float angle_radians) noexcept
{
	SetOrientation(orientation + angle_radians);
}

mat3 Camera::BuildCameraToWorld() const noexcept
{
	if (IsFirstPerson)
	{
		mat3 firstPerson
		{
			right.x		, right.y	 ,	0,
			up.x		, up.y		 ,	0,
			Position.x	, Position.y ,  1
		};

		return firstPerson;
	}
	else
	{
		
		mat3 freePerson;
		return freePerson.build_translation(Position);
	}
}

mat3 Camera::BuildWorldToCamera() const noexcept
{
	if (IsFirstPerson)
	{
		vec2 minus_right(-right.x, -right.y);
		vec2 minus_up(-up.x, -up.y);
		mat3 firstPerson
		{
			right.x					 ,	up.x				  ,	0,
			right.y					 ,	up.y				  ,	0,
			dot(minus_right,Position),	dot(minus_up,Position), 1
		};

		return firstPerson;
	}
	else
	{
		mat3 freePerson
		{
			1		   ,	0		   ,	0,
			0		   ,	1		   ,	0,
			-Position.x,	-Position.y,	1
		};

		return freePerson;
	}
}