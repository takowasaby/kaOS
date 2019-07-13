#pragma once

#include "palette.h"

class TextDrawer
{
public:
    using color_type = Palette::color_type;
    using vram_type = unsigned char *;

    TextDrawer(vram_type const vram, const int scrnx);
    TextDrawer(const TextDrawer&) = delete;
    TextDrawer& operator=(const TextDrawer&) = delete;
    
    void putfonts8_asc(const int x, const int y, const color_type c, const char *s);

private:
	void putfont8(const int x, const int y, const color_type c, const char *font);

    vram_type const vram_;
    const int scrnx_;

};