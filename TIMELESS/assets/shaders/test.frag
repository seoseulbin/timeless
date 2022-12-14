#version 450 core

//layout (location=0) in vec3 ourColor;
layout (location=1) in vec2 vTextureCoord;
layout (location = 0) out vec4 fFragClr;
//Sout vec4 FragColor;

uniform sampler2D uTex2d;

uniform float uAlpha;

void main()
{
	//vec4 texture_color = texture(uTex2d, TexCoord);
	//vec4 alphaChange = vec4(1.0,1.0,1.0,uAlpha);
	//FragColor = alphaChange * texture_color;

	vec4 texture_color = vec4(1);
	texture_color = texture(uTex2d, vTextureCoord);
	vec4 alphaChange = vec4(1.0,1.0,1.0, uAlpha);
	fFragClr = alphaChange * texture_color;
}