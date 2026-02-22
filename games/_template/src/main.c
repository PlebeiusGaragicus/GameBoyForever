#include <gbdk/platform.h>
#include <stdint.h>
#include <stdio.h>

const palette_color_t bkg_palette[] = {
    RGB_WHITE, RGB(0, 20, 0), RGB(0, 10, 0), RGB_BLACK,
};

void main(void) {
    set_bkg_palette(0, 1, bkg_palette);

    printf("Hello GBC!");

    SHOW_BKG;
    DISPLAY_ON;

    while (1) {
        wait_vbl_done();

        uint8_t keys = joypad();
        if (keys & J_START) {
            /* start button pressed */
        }
    }
}
