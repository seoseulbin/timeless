#version 450 core

layout(location = 0) in vec3 vColor;

layout(location = 0) out vec4 fFragClr;

void main()
{
    fFragClr = vec4(vColor, 1.0);
}
