/*
** EPITECH PROJECT, 2024
** radar
** File description:
** quadtree
*/

#include "radar.h"

static quadtree_t *create_qt(sfIntRect rect)
{
    quadtree_t *qt = malloc(sizeof(quadtree_t));

    qt->area = rect;
    qt->nb_rect = 10;
    qt->rectangle = create_list();
    qt->divided = 0;
    return qt;
}

static void free_qt(quadtree_t *qt)
{
    if (!qt)
        return;
    if (qt->divided){
        free_qt(qt->ne);
        free_qt(qt->nw);
        free_qt(qt->se);
        free_qt(qt->sw);
    }
    free(qt->rectangle);
    free(qt);
}

void corners(quadtree_t *qt)
{
    node_t *next;
    node_t *cur = qt->rectangle->head;

    while (cur){
        next = cur->next;
        insert(cur, qt);
        destroy_node(qt->rectangle, cur);
        cur = next;
    }
}

static void subdivide(quadtree_t *qt)
{
    sfIntRect ar = qt->area;
    sfIntRect a = (sfIntRect) {ar.left + ar.width / 2, ar.top, ar.width / 2,
        ar.height / 2};
    sfIntRect b = (sfIntRect) {ar.left, ar.top, ar.width / 2, ar.height / 2};
    sfIntRect c = (sfIntRect) {ar.left + ar.width / 2, ar.top + ar.height / 2,
        ar.width / 2, ar.height / 2};
    sfIntRect d = (sfIntRect) {ar.left, ar.top + ar.height / 2, ar.width / 2,
        ar.height / 2};

    qt->ne = create_qt(a);
    qt->nw = create_qt(b);
    qt->se = create_qt(c);
    qt->sw = create_qt(d);
    qt->divided = 1;
    corners(qt);
}

static int contains(node_t *cur, quadtree_t *qt)
{
    plane_t *data;
    sfVector2f pos;
    sfIntRect area = qt->area;

    if (cur == NULL)
        return 0;
    data = cur->data;
    pos = data->pos;
    if (pos.x >= area.left && pos.x <= area.left + area.width &&
        pos.y >= area.top && pos.y <= area.top + area.height) {
        return 1;
    } else
        return 0;
}

void insert(node_t *cur, quadtree_t *qt)
{
    if (contains(cur, qt) == 0)
        return;
    if (qt->area.top - qt->area.width < 25){
        add_node_to_list(qt->rectangle, cur);
        return;
    }
    if (qt->divided == 0 && qt->rectangle->size < qt->nb_rect){
        add_node_to_list(qt->rectangle, cur);
    } else if (qt->divided == 0 && qt->rectangle->size >= qt->nb_rect){
            subdivide(qt);
        }
    if (qt->divided == 1) {
            insert(cur, qt->ne);
            insert(cur, qt->nw);
            insert(cur, qt->sw);
            insert(cur, qt->se);
    }
}

void handle_colision(list_t *l_plane, list_t *tower)
{
    quadtree_t *qt;
    sfIntRect rect;

    rect.left = 0;
    rect.top = 0;
    rect.width = 1920;
    rect.height = 1080;
    qt = create_qt(rect);
    for (node_t *cur = l_plane->head; cur; cur = cur->next){
        insert(cur, qt);
    }
    check_colision(qt, tower);
    free_qt(qt);
}
