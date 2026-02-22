#include <gbdk/platform.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "common.h"
#include "boss.h"
#include "faces.h"
#include "sprites.h"
#include "audio.h"
#include "hud.h"

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

void show_boss_intro(uint8_t level) {
    HIDE_SPRITES;

    switch (level) {
        case 0: load_justin(); break;
        case 1: load_trump(); break;
        case 2: load_cybertruck(); break;
    }

    performant_delay(60);

    clear_screen();
    vsync();

    switch (level) {
        case 0:
            printf("  LEVEL 1: JUSTIN\n\n");
            printf("  Ha! You think you\n");
            printf("  can collect coins\n");
            printf("  faster than my\n");
            printf("  minions?\n\n");
            printf("  You're nothing\n");
            printf("  but a little\n");
            printf("  smiley face!\n\n\n");
            printf("  Collect %d coins\n", 4);
            printf("  to shut me up!\n\n\n");
            printf("  PRESS ANY BUTTON");
            break;
        case 1:
            printf("  LEVEL 2: TRUMP\n\n");
            printf("  Tremendous!\n");
            printf("  Nobody collects\n");
            printf("  coins better\n");
            printf("  than me. NOBODY.\n\n");
            printf("  My guys are the\n");
            printf("  best guys. Believe\n");
            printf("  me.\n\n");
            printf("  Collect %d coins\n", 6);
            printf("  to prove me wrong\n\n\n");
            printf("  PRESS ANY BUTTON");
            break;
        case 2:
            printf("  LEVEL 3: CYBERTRUCK\n\n");
            printf("  BEEP BOOP. I am\n");
            printf("  bulletproof and\n");
            printf("  my windows do\n");
            printf("  NOT break.\n\n");
            printf("  You cannot\n");
            printf("  outrun steel!\n\n");
            printf("  Collect %d coins\n", 10);
            printf("  if you dare!\n\n\n");
            printf("  PRESS ANY BUTTON");
            break;
    }

    wait_for_button();
    clear_screen();
}

void show_boss_defeated(uint8_t level) {
    HIDE_SPRITES;

    switch (level) {
        case 0: load_justin(); break;
        case 1: load_trump(); break;
        case 2: load_cybertruck(); break;
    }

    performant_delay(30);
    clear_screen();
    vsync();

    switch (level) {
        case 0:
            printf("  JUSTIN DEFEATED!\n\n");
            printf("  W-what?! How did\n");
            printf("  you...?!\n\n");
            printf("  This is NOT\n");
            printf("  the current year!\n\n");
            printf("  Fine. But my\n");
            printf("  friend will\n");
            printf("  crush you...\n\n\n\n\n");
            printf("  PRESS ANY BUTTON");
            break;
        case 1:
            printf("  TRUMP DEFEATED!\n\n");
            printf("  FAKE NEWS!\n");
            printf("  That score is\n");
            printf("  RIGGED! I demand\n");
            printf("  a recount!\n\n");
            printf("  You haven't\n");
            printf("  seen anything\n");
            printf("  yet...\n\n\n\n");
            printf("  PRESS ANY BUTTON");
            break;
        case 2:
            printf("  CYBERTRUCK DOWN!\n\n");
            printf("  ERROR 404:\n");
            printf("  DIGNITY NOT FOUND\n\n");
            printf("  *windows crack*\n\n");
            printf("  IMPOSSIBLE.\n");
            printf("  RECALCULATING...\n\n\n");
            printf("  YOU WIN!\n\n\n");
            printf("  PRESS ANY BUTTON");
            break;
    }

    wait_for_button();
    clear_screen();
}
