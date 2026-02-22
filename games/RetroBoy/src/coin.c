#include <gbdk/platform.h>
#include <types.h>
#include "common.h"
#include "coin.h"
#include "sprites.h"

Coin coin = {
    .pos = {{0}},
    .vel_x = 0,
    .vel_y = 0,
    .sprite_index = 0
};

static uint8_t is_too_close_to_player(fixed pos_x, fixed pos_y) {
    int16_t x_dist = pos_x.b.h - player.pos[0].b.h;
    int16_t y_dist = pos_y.b.h - player.pos[1].b.h;
    if (x_dist < 0) x_dist = -x_dist;
    if (y_dist < 0) y_dist = -y_dist;
    return (x_dist < MIN_SPAWN_DISTANCE && y_dist < MIN_SPAWN_DISTANCE);
}

static uint8_t is_too_close_to_enemies(fixed pos_x, fixed pos_y) {
    for (uint8_t i = 0; i < enemies_spawned; i++) {
        int16_t x_dist = pos_x.b.h - enemies[i].pos[0].b.h;
        int16_t y_dist = pos_y.b.h - enemies[i].pos[1].b.h;
        if (x_dist < 0) x_dist = -x_dist;
        if (y_dist < 0) y_dist = -y_dist;
        if (x_dist < MIN_SPAWN_DISTANCE && y_dist < MIN_SPAWN_DISTANCE)
            return 1;
    }
    return 0;
}

void get_safe_position(fixed *pos_x, fixed *pos_y) {
    do {
        pos_x->w = (uint16_t)random_range(MIN_X, MAX_X) << 8;
        pos_y->w = (uint16_t)random_range(MIN_Y, MAX_Y) << 8;
    } while (is_too_close_to_player(*pos_x, *pos_y) ||
             is_too_close_to_enemies(*pos_x, *pos_y));
}

void move_coin_to_safe_position(void) {
    fixed new_x, new_y;
    get_safe_position(&new_x, &new_y);
    coin.pos[0] = new_x;
    coin.pos[1] = new_y;

    coin.sprite_index = 0;
    set_sprite_prop(1, 0);
    set_sprite_tile(1, 1);

    move_sprite(1, coin.pos[0].b.h, coin.pos[1].b.h);
}

void update_coin_animation(void) {
    coin.sprite_index = (coin.sprite_index + 1) % 6;

    if (coin.sprite_index >= 3) {
        set_sprite_prop(1, S_FLIPX);
        set_sprite_tile(1, 1 + (coin.sprite_index - 3));
    } else {
        set_sprite_prop(1, 0);
        set_sprite_tile(1, 1 + coin.sprite_index);
    }
}
