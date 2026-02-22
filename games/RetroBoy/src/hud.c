#include <gbdk/platform.h>
#include <gb/cgb.h>
#include "common.h"
#include "hud.h"
#include "sprites.h"
#include "coin.h"

void clear_screen(void) {
    vsync();
    HIDE_BKG;
    set_bkg_data(0, 1, BLANK);
    init_bkg(0);
    SHOW_BKG;
}

void show_win_text_fullscreen(void) {
    set_bkg_data(0, 1, BLANK);
    init_win(0);
    move_win(7, 0);
    SHOW_WIN;
}

void hide_win_text(void) {
    HIDE_WIN;
}

void show_screen_border(void) {
    HIDE_BKG;
    set_bkg_data(0, 9, ScreenBorderTiles);
    set_bkg_tiles(0, 0, 20, 18, ScreenBorderMap);
    SHOW_BKG;
}

void load_number_tiles(void) {
    set_bkg_data(128, 10, NumberTiles);
}

void load_sprites(void) {
    show_screen_border();
    load_number_tiles();

    set_sprite_data(0, 1, Smiles);
    set_sprite_tile(0, 0);

    set_sprite_data(1, 3, CoinFlip);
    set_sprite_tile(1, 1);
    set_sprite_prop(1, 0);

    set_sprite_data(4, 1, Spoky);
    set_sprite_tile(2, 4);

    set_sprite_data(5, 1, Frowns);
    set_sprite_tile(3, 5);

    set_sprite_data(6, 1, Gooby);
    set_sprite_tile(4, 6);

    move_sprite(1, coin.pos[0].b.h, coin.pos[1].b.h);
}
