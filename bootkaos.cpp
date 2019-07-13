#include "bootkaos.h"

#include "debug.h"

void HariMain(void)
{
	new(Buffer::getInsPtr()) Buffer;
	
	Segment segment(Segment::SEGMENT_DESCRIPTOR_TABLE_ADDRES);
	segment.setKernelSegment(0x0007ffff, 0x00280000);

	unsigned int memtotal = Memory::checkAllocableSize(0x00400000, 0xbfffffff);
	new(Memory::getInsPtr()) Memory(0x00400000, memtotal - 0x00400000);

	struct BOOTINFO *binfo;
	binfo = (struct BOOTINFO *) BOOTINFO::LOAD_BOOTINFO_PORT;

	Palette(Palette::simplePalette()).set();
	Screen screen(binfo->vram, binfo->scrnx, binfo->scrny, 99);

	screen.drawBack();
	screen.text().putfonts8_asc( 8,  8, Palette::COL8_FFFFFF, "ABC 123");
	screen.text().putfonts8_asc(31, 31, Palette::COL8_000000, "King Warthur was a legendary leader");
	screen.text().putfonts8_asc(30, 30, Palette::COL8_FFFFFF, "King Warthur was a legendary leader");

	Vec<int> vec(5);
	vec.shrink_to_fit();
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		char integer[4];
		sprintf(integer, "%d ", vec.capacity());
		screen.text().putfonts8_asc(8 + i * 8, 96, Palette::COL8_FFFFFF, integer);
	}

	Vec<char> sd(40);
	char *s = new char[40];
	unsigned int freeSize = Memory::getInsPtr()->getFreeSize();

	sprintf(sd.data(), "memory %dMB  free %dKB",
			memtotal / (1024 * 1024), freeSize / 1024);
	memcpy(s, sd.data(), 40);
	screen.text().putfonts8_asc(8, 64, Palette::COL8_FFFFFF, s);

	int mx = (binfo->scrnx - 16) / 2;
	int my = (binfo->scrny - 28 - 16) / 2;
	screen.image().mouse(mx, my);

	char dump[256];
	Memory::getInsPtr()->dumpMemoryMap(dump);
	screen.text().putfonts8_asc(8, 256, Palette::COL8_FFFFFF, dump);

	screen.text().putfonts8_asc(8, 224, Palette::COL8_FFFFFF, Buffer::getInsPtr()->out());

	for (;;) {
		io_hlt();
	}
}



void init_gdtidt(void)
{
	struct SEGMENT_DESCRIPTOR *gdt = (struct SEGMENT_DESCRIPTOR *) 0x00270000;
	struct GATE_DESCRIPTOR    *idt = (struct GATE_DESCRIPTOR    *) 0x0026f800;
	int i;

	for (i = 0; i < 8192; i++)
	{
		set_segmdesc(gdt + i, 0, 0, 0);
	}
	set_segmdesc(gdt + 1, 0xffffffff, 0x00000000, 0x4092);
	set_segmdesc(gdt + 2, 0x0007ffff, 0x00280000, 0x409a);
	load_gdtr(0xffff, 0x00270000);

	for (i = 0; i < 256; i++)
	{
		set_gatedesc(idt + i, 0, 0, 0);
	}
	load_idtr(0x7ff, 0x0026f800);

	return;
}

void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar)
{
	if (limit > 0xfffff)
	{
		ar |= 0x8000;
		limit /= 0x1000;
	}
	sd->limit_low    = limit & 0xffff;
	sd->base_low     = base & 0xffff;
	sd->base_mid     = (base >> 16) & 0xff;
	sd->access_right = ar & 0xff;
	sd->limit_high   = ((limit >> 16) & 0x0f) | ((ar >> 8) & 0xf0);
	sd->base_high    = (base >> 24) & 0xff;
	return;
}

void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar)
{
	gd->offset_low   = offset & 0xffff;
	gd->selector     = selector;
	gd->dw_count     = (ar >> 8) & 0xff;
	gd->access_right = ar & 0xff;
	gd->offset_high  = (offset >> 16) & 0xffff;
	return;
}
