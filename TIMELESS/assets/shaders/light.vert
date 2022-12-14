#version 450 core

layout (location=0) in vec2 aPos;
layout (location=1) in vec3 aColor;

uniform mat3 uModelToNDC;

void main()
{
	gl_Position = vec4(vec2(uModelToNDC * vec3(aPos, 1.f)),0.0,1.0);
}