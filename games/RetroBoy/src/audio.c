#include <gbdk/platform.h>
#include "common.h"
#include "audio.h"

void audio_init(void) {
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;
}

void boop(void) {
    NR10_REG = 0x00;
    NR11_REG = 0x81;
    NR12_REG = 0x43;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}

void bap(void) {
    NR10_REG = 0x7C;
    NR11_REG = 0x41;
    NR12_REG = 0x73;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}

void beedledo(void) {
    NR10_REG = 0x00;
    NR11_REG = 0x81;
    NR12_REG = 0x43;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
    performant_delay(5);

    NR10_REG = 0x7C;
    NR11_REG = 0x41;
    NR12_REG = 0x73;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
    performant_delay(5);

    NR10_REG = 0x7C;
    NR11_REG = 0x41;
    NR12_REG = 0x73;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
    performant_delay(5);
}
