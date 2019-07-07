#include "bootkaos.h"

void HariMain(void)
{
	unsigned char *vram;
	int xsize, ysize;
	struct BOOTINFO *binfo;

	Palette(Palette::simplePalette()).set();
	binfo = (struct BOOTINFO *) 0x0ff0;
	xsize = binfo->scrnx;
	ysize = binfo->scrny;
	vram = binfo->vram;

	Screen(vram, xsize, ysize).drawBack();

	for (;;) {
		io_hlt();
	}
}