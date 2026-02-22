#include <gbdk/platform.h>
#include <gb/cgb.h>
#include <stdio.h>
#include <rand.h>
#include <types.h>

#include "common.h"
#include "audio.h"
#include "player.h"
#include "coin.h"
#include "enemy.h"
#include "level.h"
#include "hud.h"
#include "boss.h"
#include "sprites.h"

Player player;
GameState game_state;

static const uint16_t bg_palette[] = {
    RGB_WHITE, RGB(20, 25, 20), RGB(10, 15, 10), RGB_BLACK
};

static const uint16_t sprite_palettes[] = {
    RGB_WHITE, RGB(0, 28, 0), RGB(0, 16, 0), RGB_BLACK,
    RGB_WHITE, RGB(31, 31, 0), RGB(20, 16, 0), RGB_BLACK,
    RGB_WHITE, RGB(28, 0, 0), RGB(16, 0, 0), RGB_BLACK,
    RGB_WHITE, RGB(0, 0, 28), RGB(0, 0, 16), RGB_BLACK
};

static void init_gbc_palettes(void) {
    set_bkg_palette(0, 1, bg_palette);
    set_sprite_palette(0, 4, sprite_palettes);
}

static void seed_prng(void) {
    printf("--------------------");
    printf("|                  |");
    printf("|    RETRO  BOY    |");
    printf("|                  |");
    printf("--------------------");
    printf("\n\n\n");
    printf("    PRESS START!\n\n\n\n\n");
    printf("  Collect coins.\n");
    printf("  Defeat bosses.\n");
    printf("  Avoid chasers!");

    waitpad(J_START);
    boop();

    uint16_t seed = LY_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);

    performant_delay(10);
    clear_screen();
}

static void ready_start(void) {
    uint8_t x, y;
    uint8_t counter = 60;

    x = random_range(MIN_X, MAX_X) & 0xFF;
    y = random_range(MIN_Y, MAX_Y) & 0xFF;

    while (counter--) {
        if (sys_time % 20 == 0) {
            x = random_range(MIN_X, MAX_X) & 0xFF;
            y = random_range(MIN_Y, MAX_Y) & 0xFF;
            move_sprite(0, x, y);
            bap();
        }
        vsync();
    }

    performant_delay(20);
    boop();

    player.pos[0].w = (uint16_t)x << 8;
    player.pos[1].w = (uint16_t)y << 8;
    player.vel_x = 0;
    player.vel_y = 0;
    player.top_speed = TOP_SPEED;

    move_coin_to_safe_position();

    enemies_spawned = 0;
    spawn_timer = 60;

    reset_score();
    display_scores();

    game_over = 0;
    level_timer = 0;
}

static void pause_screen(void) {
    HIDE_SPRITES;
    boop();

    clear_screen();
    vsync();
    printf("\n\n\n\n\n\n\n");
    printf("      PAUSED\n\n");
    printf("   PRESS START");

    while (joypad() & J_START) vsync();
    while (!(joypad() & J_START)) vsync();
    while (joypad() & J_START) vsync();

    boop();
    show_screen_border();
    load_number_tiles();
    display_scores();
    SHOW_SPRITES;
}

void main(void) {
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    audio_init();
    init_gbc_palettes();

    seed_prng();

    game_state = STATE_TITLE;
    current_level = 0;

    uint8_t key;

    while (1) {
        switch (game_state) {
            case STATE_TITLE:
                game_state = STATE_LEVEL_INTRO;
                break;

            case STATE_LEVEL_INTRO:
                show_boss_intro(current_level);
                hide_all_enemies();
                init_level();
                load_sprites();
                SHOW_SPRITES;
                ready_start();
                game_state = STATE_PLAYING;
                break;

            case STATE_PLAYING:
                key = joypad();

                if (key & J_START) {
                    pause_screen();
                    break;
                }

                update_player_physics(key);
                handle_player_coin_collision();

                if (sys_time % 8 == 0) {
                    update_coin_animation();
                }

                handle_level_events();
                update_enemies();
                handle_enemy_collisions();

                if (game_over) {
                    if (game_state == STATE_LEVEL_COMPLETE) {
                        /* level.c already set this */
                    } else {
                        game_state = STATE_GAME_OVER;
                    }
                }

                vsync();
                break;

            case STATE_LEVEL_COMPLETE:
                show_boss_defeated(current_level - 1);
                if (current_level >= MAX_LEVEL) {
                    current_level = 0;
                }
                game_state = STATE_LEVEL_INTRO;
                break;

            case STATE_GAME_OVER:
                HIDE_SPRITES;
                clear_screen();
                vsync();
                printf("\n\n\n\n\n");
                printf("    GAME  OVER\n\n");
                printf("   A chaser got\n");
                printf("   you!\n\n");
                printf("   Score: %d\n\n\n", player_score);
                printf("   PRESS START\n");
                printf("   to try again");

                while (joypad()) vsync();
                waitpad(J_START);
                boop();

                current_level = 0;
                game_state = STATE_LEVEL_INTRO;
                clear_screen();
                break;
        }
    }
}
