#include "bootkaos.h"

void HariMain(void)
{
	struct BOOTINFO *binfo;
	binfo = (struct BOOTINFO *) BOOTINFO::LOAD_BOOTINFO_PORT;

	Palette(Palette::simplePalette()).set();
	Screen screen(binfo->vram, binfo->scrnx, binfo->scrny);

	screen.drawBack();
	screen.putfonts8_asc( 8,  8, Palette::COL8_FFFFFF, "ABC 123");
	screen.putfonts8_asc(31, 31, Palette::COL8_000000, "King Warthur was a legendary leader");
	screen.putfonts8_asc(30, 30, Palette::COL8_FFFFFF, "King Warthur was a legendary leader");

	for (;;) {
		io_hlt();
	}
}