#include "screen.h"

Screen::Screen(vram_type vram, const int scrnx, const int scrny, const color_type transparentColor) : 
	textDrawer_(vram, scrnx),
	shapeDrawer_(vram, scrnx),
	imageDrawer_(vram, scrnx, transparentColor),
    vram_(vram),
    scrnx_(scrnx),
    scrny_(scrny),
	transparentColor_(transparentColor)
{}

void Screen::drawBack()
{
	shape().box(0, 0, scrnx_ - 1, scrny_ - 29, Palette::COL8_008484);
	shape().box(0, scrny_ - 28, scrnx_ - 1, scrny_ - 28, Palette::COL8_C6C6C6);
	shape().box(0, scrny_ - 27, scrnx_ - 1, scrny_ - 27, Palette::COL8_FFFFFF);
	shape().box(0, scrny_ - 26, scrnx_ - 1, scrny_ - 1, Palette::COL8_C6C6C6);

	shape().box(3, scrny_ - 24, 59, scrny_ - 24, Palette::COL8_FFFFFF);
	shape().box(2, scrny_ - 24, 2, scrny_ - 4, Palette::COL8_FFFFFF);
	shape().box(3, scrny_ - 4, 59, scrny_ - 4, Palette::COL8_848484);
	shape().box(59, scrny_ - 23, 59, scrny_ - 5, Palette::COL8_848484);
	shape().box(2, scrny_ - 3, 59, scrny_ - 3, Palette::COL8_000000);
	shape().box(60, scrny_ - 24, 60, scrny_ - 3, Palette::COL8_000000);

	shape().box(scrnx_ - 47, scrny_ - 24, scrnx_ - 4, scrny_ - 24, Palette::COL8_848484);
	shape().box(scrnx_ - 47, scrny_ - 23, scrnx_ - 47, scrny_ - 4, Palette::COL8_848484);
	shape().box(scrnx_ - 47, scrny_ - 3, scrnx_ - 4, scrny_ - 3, Palette::COL8_FFFFFF);
	shape().box(scrnx_ - 3, scrny_ - 24, scrnx_ - 3, scrny_ - 3, Palette::COL8_FFFFFF);
	return;
}

TextDrawer& Screen::text()
{
	return textDrawer_;
}

ShapeDrawer& Screen::shape()
{
	return shapeDrawer_;
}

ImageDrawer& Screen::image()
{
	return imageDrawer_;
}