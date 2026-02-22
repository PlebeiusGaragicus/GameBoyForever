#include <gbdk/platform.h>
#include <gb/cgb.h>
#include "common.h"
#include "boss.h"
#include "faces.h"
#include "sprites.h"
#include "audio.h"
#include "hud.h"
#include "vwf.h"
#include "vwf_font.h"

#define TEXT_BASE_TILE 192

static void load_justin(void) {
    HIDE_BKG;
    set_bkg_data(0, Justin_tileset_size, Justin_tileset);
    set_bkg_tiles(0, 0, 20, 18, Justin_tilemap);
    SHOW_BKG;
}

static void load_trump(void) {
    HIDE_BKG;
    set_bkg_data(0, TrumpFace_tileset_size, TrumpFace_tileset);
    set_bkg_tiles(0, 0, 20, 18, TrumpFace_tilemap);
    SHOW_BKG;
}

static void load_cybertruck(void) {
    HIDE_BKG;
    set_bkg_data(0, CyberTruck_tileset_size, CyberTruck_tileset);
    set_bkg_tiles(0, 0, 20, 18, CyberTruck_tilemap);
    SHOW_BKG;
}

static void wait_for_button(void) {
    while (joypad()) vsync();
    while (!joypad()) vsync();
    boop();
}

static void vwf_to_win(const unsigned char *text) {
    show_win_text_fullscreen();
    vwf_set_destination(VWF_RENDER_WIN);
    vwf_activate_font(0);
    vwf_set_colors(3, 0);
    vwf_draw_text(1, 1, TEXT_BASE_TILE, text);
}

void show_boss_intro(uint8_t level) {
    HIDE_SPRITES;
    HIDE_WIN;

    switch (level) {
        case 0: load_justin(); break;
        case 1: load_trump(); break;
        case 2: load_cybertruck(); break;
    }

    performant_delay(60);

    switch (level) {
        case 0:
            vwf_to_win(
                "LEVEL 1: JUSTIN\n\n"
                "Ha! You think you\n"
                "can collect coins\n"
                "faster than my\n"
                "minions?\n\n"
                "You're nothing but\n"
                "a little smiley!\n\n"
                "Collect 4 coins\n"
                "to shut me up!\n\n\n"
                "PRESS ANY BUTTON"
            );
            break;
        case 1:
            vwf_to_win(
                "LEVEL 2: TRUMP\n\n"
                "Tremendous! Nobody\n"
                "collects coins\n"
                "better than me.\n"
                "NOBODY.\n\n"
                "My guys are the\n"
                "best. Believe me.\n\n"
                "Collect 6 coins\n"
                "to prove me wrong\n\n\n"
                "PRESS ANY BUTTON"
            );
            break;
        case 2:
            vwf_to_win(
                "LEVEL 3: CYBERTRUCK\n\n"
                "BEEP BOOP. I am\n"
                "bulletproof and\n"
                "my windows do\n"
                "NOT break.\n\n"
                "You cannot outrun\n"
                "steel!\n\n"
                "Collect 10 coins\n"
                "if you dare!\n\n\n"
                "PRESS ANY BUTTON"
            );
            break;
    }

    wait_for_button();
    hide_win_text();
    clear_screen();
}

void show_boss_defeated(uint8_t level) {
    HIDE_SPRITES;
    HIDE_WIN;

    switch (level) {
        case 0: load_justin(); break;
        case 1: load_trump(); break;
        case 2: load_cybertruck(); break;
    }

    performant_delay(30);

    switch (level) {
        case 0:
            vwf_to_win(
                "JUSTIN DEFEATED!\n\n"
                "W-what?! How did\n"
                "you...?!\n\n"
                "This is NOT the\n"
                "current year!\n\n"
                "Fine. But my\n"
                "friend will\n"
                "crush you...\n\n\n"
                "PRESS ANY BUTTON"
            );
            break;
        case 1:
            vwf_to_win(
                "TRUMP DEFEATED!\n\n"
                "FAKE NEWS!\n"
                "That score is\n"
                "RIGGED! I demand\n"
                "a recount!\n\n"
                "You haven't seen\n"
                "anything yet...\n\n\n\n"
                "PRESS ANY BUTTON"
            );
            break;
        case 2:
            vwf_to_win(
                "CYBERTRUCK DOWN!\n\n"
                "ERROR 404:\n"
                "DIGNITY NOT FOUND\n\n"
                "*windows crack*\n\n"
                "IMPOSSIBLE.\n"
                "RECALCULATING...\n\n\n"
                "YOU WIN!\n\n"
                "PRESS ANY BUTTON"
            );
            break;
    }

    wait_for_button();
    hide_win_text();
    clear_screen();
}
