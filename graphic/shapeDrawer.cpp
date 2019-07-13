#include "shapeDrawer.h"

ShapeDrawer::ShapeDrawer(vram_type const vram, const int scrnx) :
    vram_(vram),
    scrnx_(scrnx)
{
}

void ShapeDrawer::box(const int x0, const int y0, const int x1, const int y1, const color_type color)
{
    int x, y;
    for (y = y0; y <= y1; y++)
    {
        for (x = x0; x <= x1; x++)
        {
            vram_[y * scrnx_ + x] = color;
        }
    }
    return;
}
