#ifndef MODRM_H_
#define MODRM_H_

#include <stdint.h>

#include "emulator.h"

// ModR/Mを表す構造体
typedef struct {
    uint8_t mod;
    union {
        uint8_t opecode;
        uint8_t reg_index;
    };
    uint8_t rm;

    uint8_t sib;
    union {
        int8_t disp8; // disp8は符号付き整数
        uint32_t disp32;
    };
} ModRM;

void parse_modrm(Emulator* emu, ModRM* modrm);

uint32_t calc_memory_address(Emulator* emu, ModRM* modrm);

void set_rm32(Emulator* emu, ModRM* modrm, uint32_t value);

uint32_t get_rm32(Emulator* emu, ModRM* modrm);

void set_r32(Emulator* emu, ModRM* modrm, uint32_t value);

uint32_t get_r32(Emulator* emu, ModRM* modrm);

uint8_t get_rm8(Emulator* emu, ModRM* modrm);
void set_rm8(Emulator* emu, ModRM* modrm, uint8_t value);
uint8_t get_r8(Emulator* emu, ModRM* modrm);
void set_r8(Emulator* emu, ModRM* modrm, uint8_t value);

#endif
