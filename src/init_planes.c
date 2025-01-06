/*
** EPITECH PROJECT, 2024
** radar
** File description:
** init_planes
*/

#include "radar.h"

sfRectangleShape *create_rectangle(sfVector2f position)
{
    sfRectangleShape *rectangle = sfRectangleShape_create();
    sfVector2f size = {20, 20};

    sfRectangleShape_setFillColor(rectangle, sfTransparent);
    sfRectangleShape_setOutlineColor(rectangle, sfGreen);
    sfRectangleShape_setOutlineThickness(rectangle, 1);
    sfRectangleShape_setOrigin(rectangle, (sfVector2f){10, 10});
    sfRectangleShape_setPosition(rectangle, position);
    sfRectangleShape_setSize(rectangle, size);
    return rectangle;
}

static void create_sprite(plane_t *data)
{
    sfVector2f scale = {0.075, 0.075};
    float degres = data->angle * (180.f / 3.1415);

    data->death = 0;
    data->hitbox = create_rectangle(data->start);
    data->sprite = sfSprite_create();
    data->texture = sfTexture_createFromFile("assets/plane.png", NULL);
    sfSprite_setTexture(data->sprite, data->texture, sfNone);
    sfSprite_setScale(data->sprite, scale);
    sfSprite_setOrigin(data->sprite, (sfVector2f) {147.5, 134});
    sfSprite_setRotation(data->sprite, degres);
    sfSprite_setPosition(data->sprite, data->start);
}

static float set_angle(plane_t *data)
{
    float adj = data->end.x - data->start.x;
    float opp = data->end.y - data->start.y;
    float angle = atan2f(opp, adj);

    data->pos = data->start;
    data->tower = 1;
    return angle;
}

plane_t *fill_data_plane(char **tab, int i)
{
    plane_t *data = malloc(sizeof(plane_t));

    if (data == NULL){
        write(2, "erreur de malloc", 17);
        return data;
    }
    data->start.x = my_getnbr(tab[i]);
    i++;
    data->start.y = my_getnbr(tab[i]);
    i++;
    data->end.x = my_getnbr(tab[i]);
    i++;
    data->end.y = my_getnbr(tab[i]);
    i++;
    data->speed = my_getnbr(tab[i]);
    i++;
    data->start_time = my_getnbr(tab[i]);
    data->angle = set_angle(data);
    create_sprite(data);
    return data;
}

int init_planes(radar_t *assets, char **tab, int i)
{
    list_t *l_plane = assets->plane;

    pushback(l_plane, fill_data_plane(tab, i));
    return 0;
}

void clean_node_plane(list_t *l_plane)
{
    plane_t *data;
    node_t *next;

    for (node_t *node = l_plane->head; node; node = next) {
        data = node->data;
        next = node->next;
        if (data->death == 1) {
            sfRectangleShape_destroy(data->hitbox);
            sfSprite_destroy(data->sprite);
            sfTexture_destroy(data->texture);
            destroy_node(l_plane, node);
        }
    }
}
