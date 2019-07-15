#pragma once

#include "../naskfunc.h"

class KBC
{
public:
    constexpr static unsigned char KBC_MODE = 0x47;

    void setMode(unsigned char mode);
    void enableMouse();
    unsigned char getKeyCode();

private:
    constexpr static unsigned short PORT_KEYDAT = 0x0060;
    constexpr static unsigned short PORT_KEYSTA = 0x0064;
    constexpr static unsigned short PORT_KEYCMD = 0x0064;
    constexpr static unsigned char  KEYSTA_SEND_NOTREADY = 0x02;
    constexpr static unsigned char  KEYCMD_WRITE_MODE = 0x60;
    constexpr static unsigned char  KEYCMD_SENDTO_MOUSE = 0xd4;
    constexpr static unsigned char  MOUSECMD_ENABLE = 0xf4;

    void wait();

};