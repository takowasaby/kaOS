#include "textDrawer.h"

TextDrawer::TextDrawer(vram_type const vram, const int scrnx) :
    vram_(vram),
    scrnx_(scrnx)
{
}

void TextDrawer::putfonts8_asc(int x, int y, const color_type c, const char *s)
{
	extern char hankaku[4096];
	for (; *s != 0x00; s++)
	{
		putfont8(x, y, c, hankaku + *s * 16);
		x += 8;
	}
	return;
}

void TextDrawer::putfont8(int x, int y, const color_type c, const char *font)
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