#pragma once

#include "naskfunc.h"

class Palette
{
    constexpr static int PALETTE_WRITE_START_PORT = 0x03c8;
    constexpr static int PALETTE_WRITE_GBA_PORT = 0x03c9;

public:
    using Color = unsigned char;

    constexpr static Color COL8_000000 = 0;
    constexpr static Color COL8_FF0000 = 1;
    constexpr static Color COL8_00FF00 = 2;
    constexpr static Color COL8_FFFF00 = 3;
    constexpr static Color COL8_0000FF = 4;
    constexpr static Color COL8_FF00FF = 5;
    constexpr static Color COL8_00FFFF = 6;
    constexpr static Color COL8_FFFFFF = 7;
    constexpr static Color COL8_C6C6C6 = 8;
    constexpr static Color COL8_840000 = 9;
    constexpr static Color COL8_008400 = 10;
    constexpr static Color COL8_848400 = 11;
    constexpr static Color COL8_000084 = 12;
    constexpr static Color COL8_840084 = 13;
    constexpr static Color COL8_008484 = 14;
    constexpr static Color COL8_848484 = 15;

    struct PaletteData
    {
        const unsigned int* data_;
        unsigned int size_;
        PaletteData(const unsigned int* data, unsigned int size);
        PaletteData(const PaletteData& other);
        PaletteData& operator=(const PaletteData& other);
    };

    Palette(const PaletteData& palleteData);
    void set() const;
    static PaletteData simplePalette();

private:
    PaletteData paletteData_;

    constexpr static unsigned int SIMPLE_RGB_TABLE[16 * 3] = {
		0x00, 0x00, 0x00,	/*  0:黒 */
		0xff, 0x00, 0x00,	/*  1:明るい赤 */
		0x00, 0xff, 0x00,	/*  2:明るい緑 */
		0xff, 0xff, 0x00,	/*  3:明るい黄色 */
		0x00, 0x00, 0xff,	/*  4:明るい青 */
		0xff, 0x00, 0xff,	/*  5:明るい紫 */
		0x00, 0xff, 0xff,	/*  6:明るい水色 */
		0xff, 0xff, 0xff,	/*  7:白 */
		0xc6, 0xc6, 0xc6,	/*  8:明るい灰色 */
		0x84, 0x00, 0x00,	/*  9:暗い赤 */
		0x00, 0x84, 0x00,	/* 10:暗い緑 */
		0x84, 0x84, 0x00,	/* 11:暗い黄色 */
		0x00, 0x00, 0x84,	/* 12:暗い青 */
		0x84, 0x00, 0x84,	/* 13:暗い紫 */
		0x00, 0x84, 0x84,	/* 14:暗い水色 */
		0x84, 0x84, 0x84	/* 15:暗い灰色 */
    };
};