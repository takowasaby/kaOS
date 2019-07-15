#pragma once

#include "naskfunc.h"
#include "device/interupt.h"
#include "device/interuptHandler.h"
#include "device/kbc.h"
#include "device/mouse.h"
#include "device/keyboard.h"
#include "graphic/palette.h"
#include "graphic/screen.h"
#include "memory/memory.h"
#include "memory/segment.h"
#include "vec.h"
#include "queue.h"

#include "stdio.h"

extern "C"
{
    void HariMain(void);
}

class KernelMain
{
public:
	struct BOOTINFO {
		char cyls, leds, vmode, reserve;
		short scrnx, scrny;
		unsigned char *vram;
		constexpr static int LOAD_BOOTINFO_PORT = 0x0ff0;
	};

	explicit KernelMain(const BOOTINFO& bootinfo);
	void mainLoop();

	KernelMain(const KernelMain&) = delete;
	KernelMain& operator=(const KernelMain&) = delete;

private:
	Segment segment_;
	Interupt interupt_;
	Palette palette_;
	Screen screen_;
	KBC kbc_;
	Keyboard keyboard_;
	Mouse mouse_;

};