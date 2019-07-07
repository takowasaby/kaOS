#pragma once

#include "palette.h"

class Screen
{
public:
    using Color = Palette::Color;

    Screen(unsigned char *vram, const int scrnx, const int scrny);
    void boxFill8(const Color color, const int x0, const int y0, const int x1, const int y1);
    void drawBack();

private:
    unsigned char* vram_;
    const int scrnx_;
    const int scrny_;
};