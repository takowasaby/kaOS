#pragma once

#include "naskfunc.h"
#include "palette.h"
#include "screen.h"

extern "C"
{
    void HariMain(void);
}

struct BOOTINFO {
	char cyls, leds, vmode, reserve;
	short scrnx, scrny;
	unsigned char *vram;
	constexpr static int LOAD_BOOTINFO_PORT = 0x0ff0;
};