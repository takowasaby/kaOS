OBJS_BOOTPACK = bootkaos.obj naskfunc.obj palette.obj screen.obj

TOOLPATH = ../z_tools2/
INCPATH  = ../z_tools2/haribote/

MAKE	 = ${TOOLPATH}make.exe
NASK	 = ${TOOLPATH}nask.exe
CC1      = ${TOOLPATH}cc1.exe -I${INCPATH} -Os -Wall -quiet
CPP      = ${TOOLPATH}c++ -std=c++17 -I../z_tools2/haribote/ -Os -Wall -nostdlib -fno-builtin -fno-exceptions -fno-rtti -B../z_tools2/ -c
GAS2NASK = ${TOOLPATH}gas2nask.exe -a
OBJ2BIM  = ${TOOLPATH}obj2bim.exe
MAKEFONT = ${TOOLPATH}makefont.exe
BIN2OBJ  = ${TOOLPATH}bin2obj.exe
BIM2HRB  = ${TOOLPATH}bim2hrb.exe
RULEFILE = ${TOOLPATH}haribote/haribote.rul
EDIMG    = ${TOOLPATH}edimg.exe
IMGTOL   = ${TOOLPATH}imgtol.com
COPY     = copy
DEL      = del

default :
	${MAKE} img

ipl.bin : ipl.nas Makefile
	${NASK} ipl.nas ipl.bin ipl.lst

asmhead.bin : asmhead.nas Makefile
	${NASK} asmhead.nas asmhead.bin asmhead.lst 

bootpack.bim : ${OBJS_BOOTPACK} Makefile
	$(OBJ2BIM) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map \
		${OBJS_BOOTPACK}

bootpack.hrb : bootpack.bim Makefile
	$(BIM2HRB) bootpack.bim bootpack.hrb 0

kaos.sys : asmhead.bin bootpack.hrb Makefile
	copy /B asmhead.bin+bootpack.hrb kaos.sys 

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
	${MAKE} clean
	$(COPY) kaos.img ..\z_tools2\qemu\fdimage0.bin
	$(MAKE) -C ..\z_tools2\qemu

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
	-${DEL} kaos.img