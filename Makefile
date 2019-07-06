OBJS_BOOTPACK = bootkaos.obj naskfunc.obj

TOOLPATH = ../z_tools/
INCPATH  = ../z_tools/haribote/

WINE     = wine

MAKE	 = make
NASK	 = ${WINE} ${TOOLPATH}nask.exe
CC1      = ${WINE} ${TOOLPATH}cc1.exe -I${INCPATH} -Os -Wall -quiet
CPP      = g++ -I${INCPATH} -m32 -Os -Wall -nostdlib -fno-builtin -fno-exceptions -fno-rtti -B${TOOLPATH} -c
LD		 = g++ -m32 -nostdlib -Wl,--oformat=binary
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

asmhead.bin : asmhead.nas Makefile
	${NASK} asmhead.nas asmhead.bin asmhead.lst 

bootpack.hrb : ${OBJS_BOOTPACK} Makefile
	${LD} -o bootpack.hrb ${OBJS_BOOTPACK}

kaos.sys : asmhead.bin bootpack.hrb Makefile
	cat asmhead.bin bootpack.hrb > kaos.sys 

kaos.img : ipl.bin kaos.sys Makefile
	${EDIMG} imgin:${TOOLPATH}fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0 \
		copy from:kaos.sys to:@: \
		imgout:kaos.img

# C/C++

%.gas : %.c Makefile
	${CC1} -o $*.gas $*.c

%.nas : %.gas Makefile
	${GAS2NASK} $*.gas $*.nas

%.obj : %.nas Makefile
	${NASK} $*.nas $*.obj $*.lst

%.obj : %.cpp Makefile
	${CPP} -o $*.obj $*.cpp


img :
	${MAKE} -r kaos.img

run : 
	${MAKE} img
	qemu-system-i386 -m 32 -localtime -fda kaos.img

install :
	${MAKE} img
	${IMGTOL} w a: kaos.img

clean :
	-$(DEL) *.bin
	-$(DEL) *.lst
	-$(DEL) *.obj
	-$(DEL) *.map
	-$(DEL) *.bim
	-$(DEL) *.hrb
	-$(DEL) *.sys

src_only :
	${MAKE} clean
	${DEL} kaos.img