#pragma once

#include "palette.h"

class ShapeDrawer
{
public:
    using color_type = Palette::color_type;
    using vram_type = unsigned char *;

    ShapeDrawer(vram_type const vram, const int scrnx);
    ShapeDrawer(const ShapeDrawer&) = delete;
    ShapeDrawer& operator=(const ShapeDrawer&) = delete;

    void box(const int x0, const int y0, const int x1, const int y1, const color_type color);

private:
    vram_type const vram_;
    const int scrnx_;

};