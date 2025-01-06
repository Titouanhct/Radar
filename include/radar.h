/*
** EPITECH PROJECT, 2024
** Graphic
** File description:
** frame_buffer
*/

#include <stdio.h>
#include <unistd.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"
#include <fcntl.h>
#include <math.h>

#ifndef RADAR_H_
    #define RADAR_H_

typedef struct plane_s {
    sfRectangleShape *hitbox;
    sfSprite *sprite;
    sfTexture *texture;
    int start_time;
    int speed;
    sfVector2f scale;
    sfVector2f start;
    sfVector2f pos;
    sfVector2f end;
    float angle;
    int tower;
    int death;
} plane_t;

typedef struct quadtree_s {
    sfIntRect area;
    int nb_rect;
    list_t *rectangle;
    int divided;
    struct quadtree_s *ne;
    struct quadtree_s *nw;
    struct quadtree_s *se;
    struct quadtree_s *sw;
} quadtree_t;

typedef struct tower_s {
    sfCircleShape *hitbox;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f position;
    int radius;
} tower_t;

typedef struct radar_s {
    list_t *plane;
    list_t *tower;
    sfRenderWindow *window;
    sfClock *move;
    sfClock *gen;
    sfSprite *s_bg;
    sfTexture *t_bg;
    int sprite;
    int hitbox;
} radar_t;

int init_towers(radar_t *assets, char **tab, int i);
int init_planes(radar_t *assets, char **tab, int i);
void clean_node_plane(list_t *l_plane);
void handle_colision(list_t *plane, list_t *tower);
void draw_lists(radar_t *assets);
int check_takeoff(plane_t *data, radar_t *assets);
void insert(node_t *cur, quadtree_t *qt);
void check_colision(quadtree_t *qt, list_t *l_towers);

#endif /* !RADAR_H_ */
