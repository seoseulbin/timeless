#version 450 core

layout(location = 1) in vec2 vTextureCoordinates;

layout(location = 0) out vec4 fFragClr;

uniform sampler2D uTex2d;

uniform float uTexelPos;
uniform float uFrameSizeX;
uniform float uFrameSizeY;
uniform float uImageSizeX;
uniform float uImageSizeY;

uniform float uAlpha;

void main()
{
    vec2 startPixel = vec2(uTexelPos, 0.0);
    vec2 FrameSize = vec2(uFrameSizeX, uFrameSizeY); 
    vec2 endPixel = startPixel + FrameSize;
    vec2 ImageSize = vec2(uImageSizeX, uImageSizeY);

    vec2 texCoord = startPixel / ImageSize;
    vec2 texSize = FrameSize / ImageSize;
    vec4 texture_color = texture(uTex2d, vTextureCoordinates * texSize + texCoord); 

    vec4 alphaChange = vec4(1.0,1.0,1.0, uAlpha);
    fFragClr = texture_color * alphaChange;
}