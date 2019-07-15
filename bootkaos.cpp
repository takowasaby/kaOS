#include "bootkaos.h"

#include "debug.h"

void HariMain(void)
{
	new(Buffer::getInsPtr()) Buffer;

	unsigned int memtotal = Memory::checkAllocableSize(0x00400000, 0xbfffffff);
	new(Memory::getInsPtr()) Memory(0x00400000, memtotal - 0x00400000);

	new(reinterpret_cast<Queue<InteruptInfo> *>(INTERUPT_BUFFER_ADDRESS)) Queue<InteruptInfo>;

	struct KernelMain::BOOTINFO *binfo = reinterpret_cast<KernelMain::BOOTINFO *>(KernelMain::BOOTINFO::LOAD_BOOTINFO_PORT);
	KernelMain kernelMain(*binfo);
	kernelMain.mainLoop();
}

KernelMain::KernelMain(const BOOTINFO& bootinfo) :
	segment_(Segment::SEGMENT_DESCRIPTOR_TABLE_ADDRES),
	interupt_(Interupt::INTERUPT_DESCRIPTOR_TABLE_ADDRES, Interupt::PIC0_FIRST_INTERUPT_NUMBER, Interupt::PIC1_FIRST_INTERUPT_NUMBER),
	palette_(Palette::simplePalette()),
	screen_(bootinfo.vram, bootinfo.scrnx, bootinfo.scrny, 99)
{
	segment_.setKernelSegment(0x0007ffff, 0x00280000);
	palette_.set();
	screen_.drawBack();
    io_sti();
	interupt_.enableMouseInterupt();
	interupt_.enableKeyboardInterupt();
}

void KernelMain::mainLoop()
{
	screen_.text().putfonts8_asc( 8,  8, Palette::COL8_FFFFFF, "ABC 123");
	screen_.text().putfonts8_asc(31, 31, Palette::COL8_000000, "King Warthur was a legendary leader");
	screen_.text().putfonts8_asc(30, 30, Palette::COL8_FFFFFF, "King Warthur was a legendary leader");

	Queue<int> queue;
	queue.enqueue(5);
	queue.enqueue(4);
	queue.enqueue(3);
	queue.enqueue(2);
	queue.enqueue(1);
	queue.enqueue(5);
	queue.enqueue(4);
	queue.enqueue(3);
	queue.enqueue(2);
	queue.enqueue(1);
	char integer[4];
	for (unsigned int i = 0; i < 10; i++)
	{
		sprintf(integer, "%d ", queue.dequeue());
		screen_.text().putfonts8_asc(8 + i * 8, 96, Palette::COL8_FFFFFF, integer);
	}
	sprintf(integer, "%d ", queue.size());
	screen_.text().putfonts8_asc(8 + 80, 96, Palette::COL8_FFFFFF, integer);

	Vec<char> sd(40);
	char *s = new char[40];
	unsigned int freeSize = Memory::getInsPtr()->getFreeSize();

	sprintf(sd.data(), "memory %dMB  free %dKB",
			Memory::checkAllocableSize(0x00400000, 0xbfffffff) / (1024 * 1024), freeSize / 1024);
	memcpy(s, sd.data(), 40);
	screen_.text().putfonts8_asc(8, 64, Palette::COL8_FFFFFF, s);

	int mx = (screen_.getXSize() - 16) / 2;
	int my = (screen_.getYSize() - 28 - 16) / 2;
	screen_.image().mouse(mx, my);

	char dump[256];
	Memory::getInsPtr()->dumpMemoryMap(dump);
	screen_.text().putfonts8_asc(8, 256, Palette::COL8_FFFFFF, dump);

	screen_.text().putfonts8_asc(8, 224, Palette::COL8_FFFFFF, Buffer::getInsPtr()->out());

	unsigned int count = 0;
	Queue<InteruptInfo> *fifo = reinterpret_cast<Queue<InteruptInfo> *>(INTERUPT_BUFFER_ADDRESS);
	char str[4];
	for (;;) {
		if (fifo->size() != 0)
		{
			sprintf(str, "%d ", fifo->dequeue().interuptID_);
			screen_.text().putfonts8_asc(8 + (count++ * 8), 128, Palette::COL8_FFFFFF, str);
		}
		io_hlt();
	}
}
