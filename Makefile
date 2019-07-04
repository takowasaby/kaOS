TOOLPATH = ../z_tools/
INCPATH  = ../z_tools/haribote/

WINE     = wine

MAKE	 = make
NASK	 = ${WINE} ${TOOLPATH}nask.exe
CC1      = ${WINE} ${TOOLPATH}cc1.exe -I${INCPATH} -Os -Wall -quiet
GAS2NASK = ${WINE} ${TOOLPATH}gas2nask.exe -a
OBJ2BIM  = ${WINE} ${TOOLPATH}obj2bim.exe
MAKEFONT = ${WINE} ${TOOLPATH}makefont.exe
BIN2OBJ  = ${WINE} ${TOOLPATH}bin2obj.exe
BIM2HRB  = ${WINE} ${TOOLPATH}bim2hrb.exe
RULEFILE = ${TOOLPATH}haribote/haribote.rul
EDIMG    = ${WINE} ${TOOLPATH}edimg.exe
IMGTOL   = ${WINE} ${TOOLPATH}imgtol.com
COPY     = cp
DEL      = rm

default :
	${MAKE} img

ipl.bin : ipl.nas Makefile
	${NASK} ipl.nas ipl.bin ipl.lst

kaOS.img : ipl.bin Makefile
	${EDIMG} imgin:${TOOLPATH}fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0   imgout:kaOS.img

asm :
	${MAKE} -r ipl.bin

img :
	${MAKE} -r kaOS.img

run : 
	${MAKE} img
	qemu-system-i386 -m 32 -localtime -fda kaOS.img

install :
	${MAKE} img
	${IMGTOL} w a: kaOS.img

clean :
	${DEL} ipl.bin
	${DEL} ipl.lst

src_only :
	${MAKE} clean
	${DEL} kaOS.img