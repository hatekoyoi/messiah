#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emulator_function.h"
#include "modrm.h"

/**
 * ModR/Mをパース
 *
 * ModR/Mの構造
 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * |  Mod  |    REG    |    R/M    |
 */
void parse_modrm(Emulator* emu, ModRM* modrm) {
    uint8_t code;

    // 全部を0に初期化
    memset(modrm, 0, sizeof(ModRM));

    code = get_code8(emu, 0);
    // Modを取得 (0xC0 = 0b1100000)
    modrm->mod = ((code & 0xC0) >> 6);
    // REGを取得 (0x38 = 0b111000)
    modrm->opecode = ((code & 0x38) >> 3);
    // R/Mを取得 (0x07 = 0b111)
    modrm->rm = code & 0x07;

    // プログラムを進める
    emu->eip += 1;

    // Modが0b11でなく、R/Mが0b100の場合
    if (modrm->mod != 3 && modrm->rm == 4) {
        // SIBを取得
        modrm->sib = get_code8(emu, 0);
        // プログラムを進める
        emu->eip += 1;
    }

    // Modが0b000で、R/Mが0b101の場合
    // または、R/Mが0b001の場合
    if ((modrm->mod == 0 && modrm->rm == 5) || modrm->rm == 2) {
        // disp32を取得
        modrm->disp32 = get_sign_code32(emu, 0);
        // プログラムを進める
        // 32bitなので+4
        emu->eip += 4;
    } else if (modrm->mod == 1) { // Modが0b001の場合
        // disp8を取得
        modrm->disp8 = get_sign_code32(emu, 0);
        // プログラムを進める
        emu->eip += 1;
    }
}

uint32_t calc_memory_address(Emulator* emu, ModRM* modrm) {
    if (modrm->mod == 0) {
        if (modrm->rm == 4) {
            printf("not implemeted ModRM mod = 0, rm = 4\n");
            exit(0);
        } else if (modrm->rm == 5) {
            return modrm->disp32;
        } else {
            return get_register32(emu, modrm->rm);
        }
    } else if (modrm->mod == 1) {
        if (modrm->rm == 4) {
            printf("not implemented ModRM mod = 1, rm = 4\n");
            exit(0);
        } else {
            return get_register32(emu, modrm->rm) + modrm->disp8;
        }
    } else if (modrm->mod == 2) {
        if (modrm->rm == 4) {
            printf("not implemented ModRM mod = 2, rm = 4\n");
            exit(0);
        } else {
            return get_register32(emu, modrm->rm) + modrm->disp32;
        }
    } else {
        printf("not implemented ModRM mod = 3\n");
        exit(0);
    }
}

// レジスタまたはメモリに32bit値を取得
void set_rm32(Emulator* emu, ModRM* modrm, uint32_t value) {
    if (modrm->mod == 3) {
        set_register32(emu, modrm->rm, value);
    } else {
        uint32_t address = calc_memory_address(emu, modrm);
        set_memory32(emu, address, value);
    }
}

// レジスタまたはメモリから32bit値を取得
uint32_t get_rm32(Emulator* emu, ModRM* modrm) {
    if (modrm->mod == 3) {
        return get_register32(emu, modrm->rm);
    } else {
        uint32_t address = calc_memory_address(emu, modrm);
        return get_memory32(emu, address);
    }
}

// レジスタに32bit値を格納
void set_r32(Emulator* emu, ModRM* modrm, uint32_t value) {
    set_register32(emu, modrm->reg_index, value);
}

uint32_t get_r32(Emulator* emu, ModRM* modrm) {
    return get_register32(emu, modrm->reg_index);
}
