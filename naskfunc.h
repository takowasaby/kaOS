#pragma once

extern "C"
{
    void io_hlt(void);
    void io_cli(void);
    void io_sti(void);
    void io_stihlt(void);
    int io_in8(int port);
    int io_in16(int port);
    int io_in32(int port);
    void io_out8(int port, int data);
    void io_out16(int port, int data);
    void io_out32(int port, int data);
    int  io_load_eflags(void);
    void io_store_eflags(int eflags);
    void load_gdtr(int limit, int addr);
    void load_idtr(int limit, int addr);
    int load_cr0(void);
    void store_cr0(int cr0);
    void load_tr(int tr);
    unsigned int memtest_sub(unsigned int start, unsigned int end);
};