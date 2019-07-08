#pragma once

#include "palette.h"

class Screen
{
public:
    using Color = Palette::Color;

    Screen(unsigned char *vram, const int scrnx, const int scrny);
    void boxFill8(const int x0, const int y0, const int x1, const int y1, const Color color);
	void putfonts8_asc(int x, int y, const Color c, const char *s);
    void drawBack();

private:
	void putfont8(int x, int y, const Color c, const char *font);
    
    unsigned char* vram_;
    const int scrnx_;
    const int scrny_;
};