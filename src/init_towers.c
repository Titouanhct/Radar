/*
** EPITECH PROJECT, 2024
** radar
** File description:
** init_towers
*/

#include "radar.h"

sfCircleShape *create_circle(sfVector2f position, int radius)
{
    sfCircleShape *circle = sfCircleShape_create();

    sfCircleShape_setFillColor(circle, sfTransparent);
    sfCircleShape_setOutlineColor(circle, sfBlack);
    sfCircleShape_setOutlineThickness(circle, 1);
    sfCircleShape_setOrigin(circle, ((sfVector2f){radius, radius}));
    sfCircleShape_setPosition(circle, position);
    sfCircleShape_setRadius(circle, radius);
    return circle;
}

tower_t *fill_data_tower(char **tab, int i)
{
    tower_t *data = malloc(sizeof(tower_t));
    sfVector2f scale = {0.05, 0.05};

    if (data == NULL){
        write(2, "erreur de malloc", 17);
        return data;
    }
    data->position.x = my_getnbr(tab[i]);
    i++;
    data->position.y = my_getnbr(tab[i]);
    i++;
    data->radius = (my_getnbr(tab[i]));
    data->hitbox = create_circle(data->position, data->radius);
    data->sprite = sfSprite_create();
    data->texture = sfTexture_createFromFile("assets/tower.png", NULL);
    sfSprite_setTexture(data->sprite, data->texture, sfNone);
    sfSprite_setScale(data->sprite, scale);
    sfSprite_setOrigin(data->sprite, (sfVector2f){256, 256});
    sfSprite_setPosition(data->sprite, data->position);
    return data;
}

int init_towers(radar_t *assets, char **tab, int i)
{
    list_t *l_tower = assets->tower;

    pushback(l_tower, fill_data_tower(tab, i));
    return 0;
}
