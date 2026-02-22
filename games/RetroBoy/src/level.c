#include <gbdk/platform.h>
#include <types.h>
#include "common.h"
#include "level.h"
#include "enemy.h"
#include "coin.h"
#include "audio.h"
#include "hud.h"
#include "sprites.h"

uint8_t game_over = 0;
uint8_t player_score = 0;
uint8_t enemy_score = 0;
uint8_t current_level = 0;
uint16_t level_timer = 0;
uint8_t enemies_spawned = 0;
uint8_t spawn_timer = 0;

static const LevelConfig LEVEL_CONFIGS[MAX_LEVEL] = {
    { .max_enemies = 3, .spawn_interval = 180, .score_to_win = 4 },
    { .max_enemies = 5, .spawn_interval = 120, .score_to_win = 6 },
    { .max_enemies = 7, .spawn_interval = 60,  .score_to_win = 10 }
};

uint8_t get_enemy_type(uint8_t lvl, uint8_t spawn_index) {
    switch (lvl) {
        case 0:
            return ENEMY_TYPE_WANDERER;
        case 1:
            return (spawn_index % 2 == 0) ?
                   ENEMY_TYPE_WANDERER :
                   ENEMY_TYPE_COIN_CHASER;
        case 2:
            if (spawn_index < 2) return ENEMY_TYPE_WANDERER;
            if (spawn_index < 4) return ENEMY_TYPE_COIN_CHASER;
            if (spawn_index < 6) return ENEMY_TYPE_PLAYER_CHASER;
            return ENEMY_TYPE_WANDERER;
        default:
            return ENEMY_TYPE_WANDERER;
    }
}

void init_level(void) {
    level_timer = 0;
    enemies_spawned = 0;
    hide_all_enemies();
    game_over = 0;
}

void handle_level_events(void) {
    const LevelConfig *config = &LEVEL_CONFIGS[current_level];

    level_timer++;

    if (player_score >= config->score_to_win) {
        if (current_level < MAX_LEVEL - 1) {
            beedledo();
            player_score = 0;
            current_level++;
            game_state = STATE_LEVEL_COMPLETE;
        } else {
            game_state = STATE_LEVEL_COMPLETE;
        }
        game_over = 1;
        return;
    }

    if (level_timer % config->spawn_interval == 0 &&
        enemies_spawned < config->max_enemies) {
        init_enemy(enemies_spawned);
        enemies_spawned++;
    }
}

void display_scores(void) {
    uint8_t p_tens = ((player_score / 10) % 10) + 128;
    uint8_t p_ones = (player_score % 10) + 128;
    set_bkg_tiles(17, 1, 1, 1, &p_tens);
    set_bkg_tiles(18, 1, 1, 1, &p_ones);

    uint8_t e_tens = ((enemy_score / 10) % 10) + 128;
    uint8_t e_ones = (enemy_score % 10) + 128;
    set_bkg_tiles(1, 16, 1, 1, &e_tens);
    set_bkg_tiles(2, 16, 1, 1, &e_ones);
}

void reset_score(void) {
    player_score = 0;
    enemy_score = 0;
    display_scores();
}
