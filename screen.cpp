#include "screen.h"

Screen::Screen(unsigned char *vram, const int scrnx, const int scrny) :
    vram_(vram),
    scrnx_(scrnx),
    scrny_(scrny)
{}

void Screen::boxFill8(const Screen::Color color, const int x0, const int y0, const int x1, const int y1)
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

void Screen::drawBack()
{
	boxFill8(Palette::COL8_008484, 0, 0, scrnx_ - 1, scrny_ - 29);
	boxFill8(Palette::COL8_C6C6C6, 0, scrny_ - 28, scrnx_ - 1, scrny_ - 28);
	boxFill8(Palette::COL8_FFFFFF, 0, scrny_ - 27, scrnx_ - 1, scrny_ - 27);
	boxFill8(Palette::COL8_C6C6C6, 0, scrny_ - 26, scrnx_ - 1, scrny_ - 1);

	boxFill8(Palette::COL8_FFFFFF, 3, scrny_ - 24, 59, scrny_ - 24);
	boxFill8(Palette::COL8_FFFFFF, 2, scrny_ - 24, 2, scrny_ - 4);
	boxFill8(Palette::COL8_848484, 3, scrny_ - 4, 59, scrny_ - 4);
	boxFill8(Palette::COL8_848484, 59, scrny_ - 23, 59, scrny_ - 5);
	boxFill8(Palette::COL8_000000, 2, scrny_ - 3, 59, scrny_ - 3);
	boxFill8(Palette::COL8_000000, 60, scrny_ - 24, 60, scrny_ - 3);

	boxFill8(Palette::COL8_848484, scrnx_ - 47, scrny_ - 24, scrnx_ - 4, scrny_ - 24);
	boxFill8(Palette::COL8_848484, scrnx_ - 47, scrny_ - 23, scrnx_ - 47, scrny_ - 4);
	boxFill8(Palette::COL8_FFFFFF, scrnx_ - 47, scrny_ - 3, scrnx_ - 4, scrny_ - 3);
	boxFill8(Palette::COL8_FFFFFF, scrnx_ - 3, scrny_ - 24, scrnx_ - 3, scrny_ - 3);
	return;
}