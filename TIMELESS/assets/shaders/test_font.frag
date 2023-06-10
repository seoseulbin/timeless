#version 450 core

layout (location=1) in vec2 vTextureCoord;
layout (location = 0) out vec4 fFragClr;

uniform sampler2D uTex2d;

uniform float uAlpha;

void main()
{
	vec4 sampled = texture(uTex2d, vTextureCoord);
	fFragClr = vec4(sampled.rgb, sampled.a * uAlpha);
}