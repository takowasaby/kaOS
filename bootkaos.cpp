#include "bootkaos.h"

#include "debug.h"

void HariMain(void)
{
	Buffer buffer;
	*(Buffer::getInsPtr()) = buffer;

	unsigned int memtotal = Memory::checkAllocableSize(0x00400000, 0xbfffffff);
	Memory memory(0x00400000, memtotal - 0x00400000);
	*(Memory::getInsPtr()) = memory;

	struct BOOTINFO *binfo;
	binfo = (struct BOOTINFO *) BOOTINFO::LOAD_BOOTINFO_PORT;

	Palette(Palette::simplePalette()).set();
	Screen screen(binfo->vram, binfo->scrnx, binfo->scrny);

	screen.drawBack();
	screen.putfonts8_asc( 8,  8, Palette::COL8_FFFFFF, "ABC 123");
	screen.putfonts8_asc(31, 31, Palette::COL8_000000, "King Warthur was a legendary leader");
	screen.putfonts8_asc(30, 30, Palette::COL8_FFFFFF, "King Warthur was a legendary leader");

	char *s = new char[20];	
	unsigned int freeSize = memory.getFreeSize();

	sprintf(s, "memory %dMB  free %dKB",
			memtotal / (1024 * 1024), freeSize / 1024);
	screen.putfonts8_asc(8, 64, Palette::COL8_FFFFFF, s);

	char dump[256];
	memory.dumpMemoryMap(dump);
	screen.putfonts8_asc(8, 256, Palette::COL8_FFFFFF, dump);

	screen.putfonts8_asc(8, 224, Palette::COL8_FFFFFF, Buffer::getInsPtr()->out());

	for (;;) {
		io_hlt();
	}
}