#pragma once

#include "naskfunc.h"
#include "graphic/palette.h"
#include "graphic/screen.h"
#include "memory.h"
#include "vec.h"

#include "stdio.h"

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

struct SEGMENT_DESCRIPTOR 
{
	short limit_low, base_low;
	char base_mid, access_right;
	char limit_high, base_high;
};

struct GATE_DESCRIPTOR
{
	short offset_low, selector;
	char dw_count, access_right;
	short offset_high;
};

void init_mouse_cursor8(char *vram, char bc);
void putblock8_8(char *vram, int vxsize, int pxsize, int pysize, int px0, int py0, char *buf, int bxsize);
void init_gdtidt(void);
void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar);
void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar);
