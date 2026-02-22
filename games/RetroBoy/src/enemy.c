#include <gbdk/platform.h>
#include <types.h>
#include "common.h"
#include "enemy.h"
#include "coin.h"
#include "level.h"
#include "audio.h"
#include "sprites.h"

#define abs(x) ((x) > 0 ? (x) : -(x))

Enemy enemies[MAX_ENEMIES];

static void constrain_to_boundaries(Enemy *e) {
    if (e->pos[0].b.h < MIN_X) {
        e->pos[0].w = ((uint16_t)MIN_X << 8);
        e->vel_x = -e->vel_x;
    }
    if (e->pos[0].b.h > MAX_X) {
        e->pos[0].w = ((uint16_t)MAX_X << 8);
        e->vel_x = -e->vel_x;
    }
    if (e->pos[1].b.h < MIN_Y) {
        e->pos[1].w = ((uint16_t)MIN_Y << 8);
        e->vel_y = -e->vel_y;
    }
    if (e->pos[1].b.h > MAX_Y) {
        e->pos[1].w = ((uint16_t)MAX_Y << 8);
        e->vel_y = -e->vel_y;
    }
}

static void update_coin_chaser(Enemy *e) {
    if (coin.pos[0].b.h > e->pos[0].b.h)
        e->vel_x += e->top_speed / 16;
    else
        e->vel_x -= e->top_speed / 16;

    if (coin.pos[1].b.h > e->pos[1].b.h)
        e->vel_y += e->top_speed / 16;
    else
        e->vel_y -= e->top_speed / 16;

    if (e->vel_x > e->top_speed) e->vel_x = e->top_speed;
    if (e->vel_x < -e->top_speed) e->vel_x = -e->top_speed;
    if (e->vel_y > e->top_speed) e->vel_y = e->top_speed;
    if (e->vel_y < -e->top_speed) e->vel_y = -e->top_speed;

    e->pos[0].w += e->vel_x;
    e->pos[1].w += e->vel_y;
    constrain_to_boundaries(e);
}

static void update_player_chaser(Enemy *e) {
    if (player.pos[0].b.h > e->pos[0].b.h) e->pos[0].w += e->top_speed;
    if (player.pos[0].b.h < e->pos[0].b.h) e->pos[0].w -= e->top_speed;
    if (player.pos[1].b.h > e->pos[1].b.h) e->pos[1].w += e->top_speed;
    if (player.pos[1].b.h < e->pos[1].b.h) e->pos[1].w -= e->top_speed;
}

static void update_wanderer(Enemy *e) {
    if (sys_time % 60 == 0) {
        e->vel_x = random_range(-e->top_speed, e->top_speed);
        e->vel_y = random_range(-e->top_speed, e->top_speed);
    }
    e->pos[0].w += e->vel_x;
    e->pos[1].w += e->vel_y;
    constrain_to_boundaries(e);
}

void hide_all_enemies(void) {
    for (uint8_t i = 0; i < MAX_ENEMIES; i++) {
        move_sprite(i + 4, 0, 0);
    }
}

void update_enemies(void) {
    for (uint8_t i = 0; i < enemies_spawned; i++) {
        switch (enemies[i].type) {
            case ENEMY_TYPE_COIN_CHASER:
                update_coin_chaser(&enemies[i]);
                break;
            case ENEMY_TYPE_PLAYER_CHASER:
                update_player_chaser(&enemies[i]);
                break;
            case ENEMY_TYPE_WANDERER:
                update_wanderer(&enemies[i]);
                break;
        }
        move_sprite(enemies[i].sprite_id,
                    enemies[i].pos[0].b.h,
                    enemies[i].pos[1].b.h);
    }
}

void init_enemy(uint8_t index) {
    uint8_t type = get_enemy_type(current_level, enemies_spawned);
    fixed pos_x, pos_y;

    extern void get_safe_position(fixed *, fixed *);
    get_safe_position(&pos_x, &pos_y);

    enemies[index].pos[0] = pos_x;
    enemies[index].pos[1] = pos_y;
    enemies[index].sprite_id = index + 4;
    enemies[index].type = type;
    enemies[index].vel_x = 0;
    enemies[index].vel_y = 0;

    switch (type) {
        case ENEMY_TYPE_COIN_CHASER:
            set_sprite_tile(enemies[index].sprite_id, 4);
            enemies[index].top_speed = COIN_CHASER_SPEED;
            break;
        case ENEMY_TYPE_PLAYER_CHASER:
            set_sprite_tile(enemies[index].sprite_id, 5);
            enemies[index].top_speed = PLAYER_CHASER_SPEED;
            break;
        case ENEMY_TYPE_WANDERER:
            set_sprite_tile(enemies[index].sprite_id, 6);
            enemies[index].top_speed = WANDERER_SPEED;
            break;
    }

    move_sprite(enemies[index].sprite_id,
                enemies[index].pos[0].b.h,
                enemies[index].pos[1].b.h);
}

void handle_enemy_collisions(void) {
    for (uint8_t i = 0; i < enemies_spawned; i++) {
        int16_t ecx = abs(enemies[i].pos[0].b.h - coin.pos[0].b.h);
        int16_t ecy = abs(enemies[i].pos[1].b.h - coin.pos[1].b.h);
        if (ecx < COLLISION_DIST && ecy < COLLISION_DIST) {
            move_coin_to_safe_position();
            enemy_score++;
            display_scores();
            beedledo();
        }

        int16_t epx = abs(player.pos[0].b.h - enemies[i].pos[0].b.h);
        int16_t epy = abs(player.pos[1].b.h - enemies[i].pos[1].b.h);
        if (epx < COLLISION_DIST && epy < COLLISION_DIST) {
            if (enemies[i].type == ENEMY_TYPE_PLAYER_CHASER) {
                game_over = 1;
                hide_all_enemies();
                beedledo();
            } else {
                int16_t opvx = player.vel_x;
                int16_t opvy = player.vel_y;
                int16_t oevx = enemies[i].vel_x;
                int16_t oevy = enemies[i].vel_y;

                if (player.pos[0].b.h < enemies[i].pos[0].b.h) {
                    player.vel_x = -abs(opvx);
                    enemies[i].vel_x = abs(oevx);
                    player.pos[0].w -= 256;
                    enemies[i].pos[0].w += 256;
                } else {
                    player.vel_x = abs(opvx);
                    enemies[i].vel_x = -abs(oevx);
                    player.pos[0].w += 256;
                    enemies[i].pos[0].w -= 256;
                }

                if (player.pos[1].b.h < enemies[i].pos[1].b.h) {
                    player.vel_y = -abs(opvy);
                    enemies[i].vel_y = abs(oevy);
                    player.pos[1].w -= 256;
                    enemies[i].pos[1].w += 256;
                } else {
                    player.vel_y = abs(opvy);
                    enemies[i].vel_y = -abs(oevy);
                    player.pos[1].w += 256;
                    enemies[i].pos[1].w -= 256;
                }
                bap();
            }
        }

        for (uint8_t j = i + 1; j < enemies_spawned; j++) {
            int16_t dx = abs(enemies[i].pos[0].b.h - enemies[j].pos[0].b.h);
            int16_t dy = abs(enemies[i].pos[1].b.h - enemies[j].pos[1].b.h);
            if (dx < 8 && dy < 8) {
                int16_t v1x = enemies[i].vel_x;
                int16_t v1y = enemies[i].vel_y;
                int16_t v2x = enemies[j].vel_x;
                int16_t v2y = enemies[j].vel_y;

                if (enemies[i].pos[0].b.h < enemies[j].pos[0].b.h) {
                    enemies[i].vel_x = -abs(v1x);
                    enemies[j].vel_x = abs(v2x);
                    enemies[i].pos[0].w -= 256;
                    enemies[j].pos[0].w += 256;
                } else {
                    enemies[i].vel_x = abs(v1x);
                    enemies[j].vel_x = -abs(v2x);
                    enemies[i].pos[0].w += 256;
                    enemies[j].pos[0].w -= 256;
                }

                if (enemies[i].pos[1].b.h < enemies[j].pos[1].b.h) {
                    enemies[i].vel_y = -abs(v1y);
                    enemies[j].vel_y = abs(v2y);
                    enemies[i].pos[1].w -= 256;
                    enemies[j].pos[1].w += 256;
                } else {
                    enemies[i].vel_y = abs(v1y);
                    enemies[j].vel_y = -abs(v2y);
                    enemies[i].pos[1].w += 256;
                    enemies[j].pos[1].w -= 256;
                }
            }
        }
    }
}
