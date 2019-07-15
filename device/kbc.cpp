#include "kbc.h"

void KBC::setMode(unsigned char mode)
{
	wait();
	io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);
	wait();
	io_out8(PORT_KEYDAT, mode);
}

void KBC::enableMouse()
{
	wait();
	io_out8(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
	wait();
	io_out8(PORT_KEYDAT, MOUSECMD_ENABLE);
}

unsigned char KBC::getKeyCode()
{
    return io_in8(PORT_KEYDAT);
}

void KBC::wait()
{
	for (;;)
	{
		if ((io_in8(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0)
		{
			break;
		}
	}
}