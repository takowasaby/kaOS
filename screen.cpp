#include "screen.h"

Screen::Screen(unsigned char *vram, const int scrnx, const int scrny) :
    vram_(vram),
    scrnx_(scrnx),
    scrny_(scrny)
{}

void Screen::boxFill8(const int x0, const int y0, const int x1, const int y1, const Screen::Color color)
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

void Screen::putfonts8_asc(int x, int y, const Screen::Color c, const char *s)
{
	extern char hankaku[4096];
	for (; *s != 0x00; s++)
	{
		putfont8(x, y, c, hankaku + *s * 16);
		x += 8;
	}
	return;
}

void Screen::drawBack()
{
	boxFill8(0, 0, scrnx_ - 1, scrny_ - 29, Palette::COL8_008484);
	boxFill8(0, scrny_ - 28, scrnx_ - 1, scrny_ - 28, Palette::COL8_C6C6C6);
	boxFill8(0, scrny_ - 27, scrnx_ - 1, scrny_ - 27, Palette::COL8_FFFFFF);
	boxFill8(0, scrny_ - 26, scrnx_ - 1, scrny_ - 1, Palette::COL8_C6C6C6);

	boxFill8(3, scrny_ - 24, 59, scrny_ - 24, Palette::COL8_FFFFFF);
	boxFill8(2, scrny_ - 24, 2, scrny_ - 4, Palette::COL8_FFFFFF);
	boxFill8(3, scrny_ - 4, 59, scrny_ - 4, Palette::COL8_848484);
	boxFill8(59, scrny_ - 23, 59, scrny_ - 5, Palette::COL8_848484);
	boxFill8(2, scrny_ - 3, 59, scrny_ - 3, Palette::COL8_000000);
	boxFill8(60, scrny_ - 24, 60, scrny_ - 3, Palette::COL8_000000);

	boxFill8(scrnx_ - 47, scrny_ - 24, scrnx_ - 4, scrny_ - 24, Palette::COL8_848484);
	boxFill8(scrnx_ - 47, scrny_ - 23, scrnx_ - 47, scrny_ - 4, Palette::COL8_848484);
	boxFill8(scrnx_ - 47, scrny_ - 3, scrnx_ - 4, scrny_ - 3, Palette::COL8_FFFFFF);
	boxFill8(scrnx_ - 3, scrny_ - 24, scrnx_ - 3, scrny_ - 3, Palette::COL8_FFFFFF);
	return;
}

void Screen::putfont8(int x, int y, const Screen::Color c, const char *font)
{
	int i;
	unsigned char *p, d;
	for (i = 0; i < 16; i++)
	{
		p = vram_ + (y + i) * scrnx_ + x;
		d = font[i];
		if ((d & 0x80) != 0) { p[0] = c; }
		if ((d & 0x40) != 0) { p[1] = c; }
		if ((d & 0x20) != 0) { p[2] = c; }
		if ((d & 0x10) != 0) { p[3] = c; }
		if ((d & 0x08) != 0) { p[4] = c; }
		if ((d & 0x04) != 0) { p[5] = c; }
		if ((d & 0x02) != 0) { p[6] = c; }
		if ((d & 0x01) != 0) { p[7] = c; }
	}
	return;
}