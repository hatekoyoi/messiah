#include "emulator_function.h"

// プログラムカウンタから相対位置にある符号無し8bit値を取得
uint32_t get_code8(Emulator* emu, int index) {
    return emu->memory[emu->eip + index];
}

// プログラムカウンタから相対位置にある符号付き8bit値を取得
int32_t get_sign_code8(Emulator* emu, int index) {
    return (int8_t)emu->memory[emu->eip + index];
}

// プログラムカウンタから相対位置にある符号無し32bit値を取得
uint32_t get_code32(Emulator* emu, int index) {
    int i;
    uint32_t ret = 0;

    // リトルエンディアンでメモリの値を取得する
    for (i = 0; i < 4; i++) {
        ret |= get_code8(emu, index + i) << (i * 8);
    }

    return ret;
}

// プログラムカウンタから相対位置にある符号付き32bit値を取得
int32_t get_sign_code32(Emulator* emu, int index) {
    return (int32_t)get_code32(emu, index);
}

// index番目の32bit汎用レジスタの値を取得する
uint32_t get_register32(Emulator* emu, int index) {
    return emu->registers[index];
}

// index番目の32bit汎用レジスタの値を設定する
void set_register32(Emulator* emu, int index, uint32_t value) {
    emu->registers[index] = value;
}

// メモリのindex番地に8bit値を設定する
void set_memory8(Emulator* emu, uint32_t address, uint32_t value) {
    emu->memory[address] = value & 0xFF;
}

// メモリのindex番地に32bit値を設定する
void set_memory32(Emulator* emu, uint32_t address, uint32_t value) {
    int i;

    // リトルエンディアンでメモリの値を設定する
    for (i = 0; i < 4; i++) {
        set_memory8(emu, address + i, value >> (i * 8));
    }
}

// メモリのindex番地の8bit値を取得する
uint32_t get_memory8(Emulator* emu, uint32_t address) {
    return emu->memory[address];
}

// メモリのindex番地の32bit値を取得する
uint32_t get_memory32(Emulator* emu, uint32_t address) {
    int i;
    uint32_t ret = 0;

    // リトルエンディアンでメモリの値を取得する
    for (i = 0; i < 4; i++) {
        ret |= get_memory8(emu, address + i) << (8 * i);
    }

    return ret;
}
