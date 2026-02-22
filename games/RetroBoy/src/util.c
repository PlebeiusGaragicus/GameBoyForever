#include <gbdk/platform.h>
#include <rand.h>
#include "common.h"

int16_t random_range(int16_t min, int16_t max) {
    return (rand() % (max - min + 1)) + min;
}

void performant_delay(uint8_t frames) {
    for (uint8_t i = 0; i < frames; i++) {
        wait_vbl_done();
    }
}

int16_t reduce_velocity(int16_t vel) {
    return vel >> 2;
}
