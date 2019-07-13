#include "palette.h"

Palette::PaletteData::PaletteData(const unsigned int* data, unsigned int size) :
    data_(data),
    size_(size)
{}

Palette::PaletteData::PaletteData(const PaletteData& other) :
    data_(other.data_),
    size_(other.size_)
{}

Palette::PaletteData& Palette::PaletteData::operator=(const PaletteData& other)
{
    if (this == &other) return *this;
    data_ = other.data_;
    size_ = other.size_;
    return *this;
}

Palette::Palette(const PaletteData& palleteData) :
    paletteData_(palleteData)
{}

void Palette::set() const
{
    int eflags = io_load_eflags();
    io_cli();
    io_out8(PALETTE_WRITE_START_PORT, 0);
    const unsigned int* rgb = paletteData_.data_;
    for (unsigned int i = 0; i < paletteData_.size_; i++)
    {
        io_out8(PALETTE_WRITE_GBA_PORT, rgb[0] / 4);
        io_out8(PALETTE_WRITE_GBA_PORT, rgb[1] / 4);
        io_out8(PALETTE_WRITE_GBA_PORT, rgb[2] / 4);
        rgb += 3;
    }
    io_store_eflags(eflags);
    return;
}

Palette::PaletteData Palette::simplePalette()
{
    return PaletteData(SIMPLE_RGB_TABLE, 16);
}