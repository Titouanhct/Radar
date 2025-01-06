/*
** EPITECH PROJECT, 2024
** radar
** File description:
** handle_collisions
*/

#include "radar.h"

int in_tower(plane_t *plane, list_t *tower)
{
    tower_t *d_t;
    int radius = 0;
    sfVector2f pos_tower;

    for (node_t *cur = tower->head; cur; cur = cur->next){
        d_t = cur->data;
        radius = d_t->radius;
        pos_tower = d_t->position;
        if (powf(plane->pos.x - pos_tower.x, 2) +
            powf(plane->pos.y - pos_tower.y, 2) <= pow(radius, 2))
                return 1;
    }
    return 0;
}

static void check_in_tower(plane_t *p_c, plane_t *p_n, list_t *l_towers)
{
    if (in_tower(p_c, l_towers) == 0 && in_tower(p_c, l_towers) == 0){
        p_c->death = 1;
        p_n->death = 1;
    }
}

static void intersects(node_t *c, node_t *n, list_t *l_towers)
{
    sfIntRect cur;
    sfIntRect next;
    plane_t *p_c = c->data;
    plane_t *p_n = n->data;

    cur.left = p_c->pos.x;
    cur.top = p_c->pos.y;
    cur.width = 20;
    cur.height = 20;
    next.left = p_n->pos.x;
    next.top = p_n->pos.y;
    next.width = 20;
    next.height = 20;
    if (cur.left + cur.width >= next.left &&
        cur.left <= next.left + next.width &&
        cur.top + cur.height >= next.top &&
        cur.top <= next.top + next.height) {
            check_in_tower(p_c, p_n, l_towers);
        }
}

void check_colision(quadtree_t *qt, list_t *l_towers)
{
    if (qt->divided == 1){
        check_colision(qt->ne, l_towers);
        check_colision(qt->nw, l_towers);
        check_colision(qt->se, l_towers);
        check_colision(qt->sw, l_towers);
    }
    for (node_t *cur = qt->rectangle->head; cur; cur = cur->next) {
        for (node_t *next = cur->next; next; next = next->next)
            intersects(cur, next, l_towers);
    }
}
