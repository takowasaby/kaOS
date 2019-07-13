#pragma once

#include "palette.h"
#include "charImages.h"

class ImageDrawer
{
public:
    using color_type = Palette::color_type;
    using vram_type = unsigned char *;

    ImageDrawer(vram_type const vram, const int scrnx, const color_type transparentColor);
    ImageDrawer(const ImageDrawer&) = delete;
    ImageDrawer& operator=(const ImageDrawer&) = delete;
    
    void mouse(const int x, const int y);

private:
    void drawCharImage(const int x, const int y, const CharImage& image);
    color_type CharImagePixcelColor(const char c);

    vram_type const vram_;
    const int scrnx_;
    const color_type transparentColor_;

};