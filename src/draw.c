/*
** EPITECH PROJECT, 2025
** radar
** File description:
** draw
*/

#include "radar.h"

int check_takeoff(plane_t *data, radar_t *assets)
{
    sfTime time = sfClock_getElapsedTime(assets->gen);
    float seconds = time.microseconds / 1000000.0;

    if (data->start_time <= seconds)
        return 1;
    else
        return 0;
}

void draw_planes(radar_t *assets, node_t *c)
{
    plane_t *d_p;

    d_p = c->data;
    if (check_takeoff(d_p, assets) == 1 && d_p->death == 0) {
        if (assets->hitbox == 1)
            sfRenderWindow_drawRectangleShape(assets->window, d_p->hitbox,
                NULL);
        if (assets->sprite == 1)
            sfRenderWindow_drawSprite(assets->window, d_p->sprite, NULL);
    }
}

void draw_lists(radar_t *assets)
{
    list_t *l_tower = assets->tower;
    tower_t *d_t;
    list_t *l_plane = assets->plane;

    for (node_t *c = l_tower->head; c; c = c->next){
        d_t = c->data;
        if (assets->sprite == 1)
            sfRenderWindow_drawSprite(assets->window, d_t->sprite, NULL);
        if (assets->hitbox == 1)
            sfRenderWindow_drawCircleShape(assets->window, d_t->hitbox, NULL);
        }
        for (node_t *c = l_plane->head; c; c = c->next)
            draw_planes(assets, c);
}
