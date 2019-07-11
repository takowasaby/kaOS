#include "bootkaos.h"

#include "debug.h"

void HariMain(void)
{
	Buffer buffer;
	*(Buffer::getInsPtr()) = buffer;

	struct BOOTINFO *binfo;
	binfo = (struct BOOTINFO *) BOOTINFO::LOAD_BOOTINFO_PORT;

	Palette(Palette::simplePalette()).set();
	Screen screen(binfo->vram, binfo->scrnx, binfo->scrny);

	screen.drawBack();
	screen.putfonts8_asc( 8,  8, Palette::COL8_FFFFFF, "ABC 123");
	screen.putfonts8_asc(31, 31, Palette::COL8_000000, "King Warthur was a legendary leader");
	screen.putfonts8_asc(30, 30, Palette::COL8_FFFFFF, "King Warthur was a legendary leader");

	char s[40];	
	unsigned int freeCache[16];
	unsigned int memtotal = Memory::checkAllocableSize(0x00400000, 0xbfffffff);
	Memory memory(0x00400000, memtotal - 0x00400000);
	unsigned int freeSize = memory.getFreeSize();

	void* allocated1 = memory.allocate(4);
	freeCache[0] = memory.getFreeSize();
	memory.free(allocated1);
	freeCache[1] = memory.getFreeSize();
	void* allocated2 = memory.allocate(4);
	freeCache[2] = memory.getFreeSize();
	void* allocated3 = memory.allocate(4);
	freeCache[3] = memory.getFreeSize();
	void* allocated4 = memory.allocate(4);
	freeCache[4] = memory.getFreeSize();
	memory.free(allocated3);
	freeCache[5] = memory.getFreeSize();
	memory.free(allocated2);
	freeCache[6] = memory.getFreeSize();
	memory.free(allocated4);
	freeCache[7] = memory.getFreeSize();
	void* allocated5 = memory.allocate(4);
	freeCache[8] = memory.getFreeSize();
	void* allocated6 = memory.allocate(4);
	freeCache[9] = memory.getFreeSize();
	memory.free(allocated6);
	freeCache[10] = memory.getFreeSize();
	memory.free(allocated5);
	freeCache[11] = memory.getFreeSize();

	sprintf(s, "memory %dMB  free %dKB",
			memtotal / (1024 * 1024), freeSize / 1024);
	screen.putfonts8_asc(8, 64, Palette::COL8_FFFFFF, s);
	sprintf(s, "0:%dB 1:%dB 2:%dB",
			freeCache[0], freeCache[1], freeCache[2]);
	screen.putfonts8_asc(8, 96, Palette::COL8_FFFFFF, s);
	sprintf(s, "3:%dB 4:%dB 5:%dB",
			freeCache[3], freeCache[4], freeCache[5]);
	screen.putfonts8_asc(8, 128, Palette::COL8_FFFFFF, s);
	sprintf(s, "6:%dB 7:%dB 8:%dB",
			freeCache[6], freeCache[7], freeCache[8]);
	screen.putfonts8_asc(8, 160, Palette::COL8_FFFFFF, s);
	sprintf(s, "9:%dB 10:%dB 11:%dB",
			freeCache[9], freeCache[10], freeCache[11]);
	screen.putfonts8_asc(8, 192, Palette::COL8_FFFFFF, s);

	char dump[256];
	memory.dumpMemoryMap(dump);
	screen.putfonts8_asc(8, 256, Palette::COL8_FFFFFF, dump);

	screen.putfonts8_asc(8, 224, Palette::COL8_FFFFFF, Buffer::getInsPtr()->out());

	for (;;) {
		io_hlt();
	}
}