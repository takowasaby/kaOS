#pragma once

#include "palette.h"
#include "textDrawer.h"
#include "shapeDrawer.h"
#include "imageDrawer.h"

class Screen
{
public:
    using color_type = Palette::color_type;
    using vram_type = unsigned char *;

    Screen(vram_type vram, const int scrnx, const int scrny, const color_type transparentColor);
    void drawBack();

    TextDrawer& text();
    ShapeDrawer& shape();
    ImageDrawer& image();

private:
    TextDrawer textDrawer_;
    ShapeDrawer shapeDrawer_;
    ImageDrawer imageDrawer_;

	vram_type const vram_;
    const int scrnx_;
    const int scrny_;
    const color_type transparentColor_;
};