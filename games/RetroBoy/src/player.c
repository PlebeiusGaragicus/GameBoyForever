#include <gbdk/platform.h>
#include <types.h>
#include "common.h"
#include "player.h"
#include "coin.h"
#include "level.h"
#include "audio.h"
#include "sprites.h"

void update_player_physics(uint8_t key) {
    if (key & J_LEFT) {
        if (player.vel_x > -TOP_SPEED)
            player.vel_x -= SPEED_CHANGE;
    } else if (key & J_RIGHT) {
        if (player.vel_x < TOP_SPEED)
            player.vel_x += SPEED_CHANGE;
    } else {
        if (player.vel_x > 0)
            player.vel_x -= PLAYER_FRICTION;
        else if (player.vel_x < 0)
            player.vel_x += PLAYER_FRICTION;
    }

    if (key & J_UP) {
        if (player.vel_y > -TOP_SPEED)
            player.vel_y -= SPEED_CHANGE;
    } else if (key & J_DOWN) {
        if (player.vel_y < TOP_SPEED)
            player.vel_y += SPEED_CHANGE;
    } else {
        if (player.vel_y > 0)
            player.vel_y -= PLAYER_FRICTION;
        else if (player.vel_y < 0)
            player.vel_y += PLAYER_FRICTION;
    }

    if (key & J_A) {
        player.pos[0].w += player.vel_x >> 1;
        player.pos[1].w += player.vel_y >> 1;
    } else {
        player.pos[0].w += player.vel_x;
        player.pos[1].w += player.vel_y;
    }

    if (player.pos[0].b.h < MIN_X) {
        player.pos[0].w = ((uint16_t)MIN_X << 8);
        player.vel_x = -reduce_velocity(player.vel_x);
    }
    if (player.pos[0].b.h > MAX_X) {
        player.pos[0].w = ((uint16_t)MAX_X << 8);
        player.vel_x = -reduce_velocity(player.vel_x);
    }
    if (player.pos[1].b.h < MIN_Y) {
        player.pos[1].w = ((uint16_t)MIN_Y << 8);
        player.vel_y = -reduce_velocity(player.vel_y);
    }
    if (player.pos[1].b.h > MAX_Y) {
        player.pos[1].w = ((uint16_t)MAX_Y << 8);
        player.vel_y = -reduce_velocity(player.vel_y);
    }

    move_sprite(0, player.pos[0].b.h, player.pos[1].b.h);
}

void handle_player_coin_collision(void) {
    int16_t x_dist = player.pos[0].b.h - coin.pos[0].b.h;
    int16_t y_dist = player.pos[1].b.h - coin.pos[1].b.h;
    if (x_dist < 0) x_dist = -x_dist;
    if (y_dist < 0) y_dist = -y_dist;
    if (x_dist < COLLISION_DIST && y_dist < COLLISION_DIST) {
        move_coin_to_safe_position();
        player_score++;
        display_scores();
        boop();
    }
}
