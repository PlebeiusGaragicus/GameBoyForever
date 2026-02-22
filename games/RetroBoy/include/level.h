#ifndef LEVEL_H
#define LEVEL_H

void init_level(void);
void handle_level_events(void);
uint8_t get_enemy_type(uint8_t level, uint8_t spawn_index);
void display_scores(void);
void reset_score(void);

#endif
