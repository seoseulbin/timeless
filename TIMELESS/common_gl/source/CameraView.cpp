/*
 * minseok.kim
 * CS200
 * Fall 2022
 */
#include"CameraView.h"

void CameraView::SetFramebufferSize(vec2 the_framebuffer_size) noexcept
{
    framebuffer_size = the_framebuffer_size;
}

void CameraView::SetFramebufferSize(int new_pixel_width, int new_pixel_height) noexcept
{
    SetFramebufferSize(vec2{ float(new_pixel_width), float(new_pixel_height) });
}

vec2 CameraView::GetViewSize() const
{
    return framebuffer_size;
}

void CameraView::SetZoom(float new_zoom) noexcept
{
    if (new_zoom != 0)
    {
        zoom = new_zoom;
    }
}

mat3 CameraView::BuildCameraToNDC() const noexcept
{
    vec2 Extand_Zoom{ framebuffer_size / zoom };

    mat3 ExtandMatrix
    {
      (2/Extand_Zoom.x) ,   0                 ,   0,
        0                 ,  -(2/Extand_Zoom.y)  ,   0,
        0                 ,   0                 ,   1
    };
    /*mat3 ExtandMatrix
    {
      1 ,   0                 ,   0,
        0                 ,  1  ,   0,
       2 / Extand_Zoom.x                 ,   2 / Extand_Zoom.y                 ,   1
    };*/
    return ExtandMatrix;
}

mat3 CameraView::BuildWindowDeviceToCamera() const noexcept
{
    vec2 Extand_Zoom{ framebuffer_size / zoom };

    /*mat3 ExtandMatrix
    {
      1 ,   0                 ,   0,
        0                 ,  1  ,   0,
       -Extand_Zoom.x /2                 ,   Extand_Zoom.y /2                 ,   1
    };*/

    mat3 ExtandMatrix
    {
        Extand_Zoom.x / framebuffer_size.x    ,  0                                      ,  0,
        0                                     ,  -(Extand_Zoom.y / framebuffer_size.y)  ,  0,
        -Extand_Zoom.x / 2                  ,  Extand_Zoom.y / 2                      ,  1
    };

    return ExtandMatrix;
}