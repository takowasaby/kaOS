#include "imageDrawer.h"

ImageDrawer::ImageDrawer(vram_type const vram, const int scrnx, const color_type transparentColor) :
    vram_(vram),
    scrnx_(scrnx),
    transparentColor_(transparentColor)
{
}

void ImageDrawer::mouse(const int x, const int y)
{
    drawCharImage(x, y, CharImages::MOUSE_CURSOR);
    return;
}

void ImageDrawer::drawCharImage(const int x, const int y, const CharImage& image)
{
    int xc, yc;
    for (yc = y; yc <= y + image.y; yc++)
    {
        for (xc = x; xc <= x + image.x; xc++)
        {
            color_type color = CharImagePixcelColor(image.image[yc - y][xc - x]);
            if (color != transparentColor_)
            {
                vram_[yc * scrnx_ + xc] = color;
            }
        }
    }
    return;
}

ImageDrawer::color_type ImageDrawer::CharImagePixcelColor(const char c)
{
    switch (c)
    {
    case '*':
        return Palette::COL8_000000;
    case 'O':
        return Palette::COL8_FFFFFF;
    case '.':
        return transparentColor_;
    default:
        break;
    }
    return transparentColor_;
}