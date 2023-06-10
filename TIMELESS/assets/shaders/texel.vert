#version 450 core

layout (location=0) in vec2 aPos;
layout (location=1) in vec3 aColor;
//layout (location=2) in vec2 aTexCoord;


//layout (location=0) out vec3 ourColor;
layout (location = 1) out vec2 vTextureCoord;

uniform mat3 uModelToNDC;

void main()
{
	//vec3 ndc = uModelToNDC * vec3(aPos, 1.0);
	//gl_Position = vec4(ndc.xy, 0.0, 1.0);
	//ourColor = aColor;
	//TexCoord = vec2(aTexCoord.x, aTexCoord.y);

	vTextureCoord = ((aPos + 1) / 2);
	gl_Position = vec4(vec2(uModelToNDC * vec3(aPos, 1.f)),0.0,1.0);
}