#ifndef COMMON_H
#define COMMON_H

#include <gbdk/platform.h>
#include <stdint.h>
#include <types.h>

#define MIN_X 12
#define MAX_X 156
#define MIN_Y 20
#define MAX_Y 148

#define TOP_SPEED 600
#define SPEED_CHANGE 8
#define PLAYER_FRICTION 2

#define MAX_ENEMIES 7
#define MAX_LEVEL 3

#define ENEMY_TYPE_WANDERER      0
#define ENEMY_TYPE_COIN_CHASER   1
#define ENEMY_TYPE_PLAYER_CHASER 2

#define COIN_CHASER_SPEED   90
#define PLAYER_CHASER_SPEED 100
#define WANDERER_SPEED      150

#define MIN_SPAWN_DISTANCE 32
#define MIN_COIN_DISTANCE  24
#define COLLISION_DIST     6

typedef enum {
    STATE_TITLE,
    STATE_LEVEL_INTRO,
    STATE_PLAYING,
    STATE_LEVEL_COMPLETE,
    STATE_GAME_OVER
} GameState;

typedef struct {
    fixed pos[2];
    int16_t vel_x;
    int16_t vel_y;
    uint8_t top_speed;
} Player;

typedef struct {
    fixed pos[2];
    int16_t vel_x;
    int16_t vel_y;
    uint8_t sprite_index;
} Coin;

typedef struct {
    fixed pos[2];
    uint8_t sprite_id;
    uint8_t type;
    int16_t vel_x;
    int16_t vel_y;
    uint8_t top_speed;
    uint8_t active;
} Enemy;

typedef struct {
    uint8_t max_enemies;
    uint16_t spawn_interval;
    uint8_t score_to_win;
} LevelConfig;

extern Player player;
extern Coin coin;
extern Enemy enemies[MAX_ENEMIES];
extern GameState game_state;
extern uint8_t current_level;
extern uint8_t player_score;
extern uint8_t enemy_score;
extern uint8_t enemies_spawned;
extern uint16_t level_timer;
extern uint8_t spawn_timer;
extern uint8_t game_over;

void get_safe_position(fixed *pos_x, fixed *pos_y);
int16_t random_range(int16_t min, int16_t max);
void performant_delay(uint8_t frames);
int16_t reduce_velocity(int16_t vel);

#endif
