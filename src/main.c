/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** ..
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "radar.h"

static void analyse_events(sfRenderWindow *window, sfEvent event,
    radar_t *assets)
{
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyS)
            assets->sprite *= -1;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyL)
            assets->hitbox *= -1;
    }
}

static void clean_lplane(list_t *l_plane)
{
    plane_t *data;

    for (node_t *cur = l_plane->head; cur; cur = cur->next){
        data = cur->data;
        if (data->death == 1){
            destroy_node(l_plane, cur);
        }
    }
}

static void clean_up(radar_t *assets)
{
    node_t *next;

    sfRenderWindow_destroy(assets->window);
    sfSprite_destroy(assets->s_bg);
    sfTexture_destroy(assets->t_bg);
    sfClock_destroy(assets->move);
    sfClock_destroy(assets->gen);
    for (node_t *cur = assets->plane->head; cur; cur = next) {
        next = cur->next;
        destroy_node(assets->plane, cur);
    }
    for (node_t *cur = assets->tower->head; cur; cur = next) {
        next = cur->next;
        destroy_node(assets->plane, cur);
    }
    free(assets->plane);
    free(assets->tower);
    free(assets);
}

static void check_landing(node_t *cur)
{
    plane_t *data = cur->data;

    if (data->end.x > data->start.x && data->end.y > data->start.y)
        if (data->pos.x >= data->end.x && data->pos.y >= data->end.y)
            data->death = 1;
    if (data->end.x > data->start.x && data->end.y < data->start.y)
        if (data->pos.x >= data->end.x && data->pos.y <= data->end.y)
            data->death = 1;
    if (data->end.x < data->start.x && data->end.y > data->start.y)
        if (data->pos.x <= data->end.x && data->pos.y >= data->end.y)
            data->death = 1;
    if (data->end.x < data->start.x && data->end.y < data->start.y)
        if (data->pos.x <= data->end.x && data->pos.y <= data->end.y)
            data->death = 1;
}

void move_planes(radar_t *assets)
{
    list_t *l_plane = assets->plane;
    plane_t *d_p;
    sfTime time;
    float seconds;

    time = sfClock_getElapsedTime(assets->move);
    seconds = time.microseconds / 1000000.0;
    if (seconds > 0.05){
        for (node_t *cur = l_plane->head; cur &&
            check_takeoff(cur->data, assets) == 1; cur = cur->next) {
            d_p = (plane_t *)cur->data;
            d_p->pos.x += cos(d_p->angle) * (float) d_p->speed / 20.f;
            d_p->pos.y += sin(d_p->angle) * (float) d_p->speed / 20.f;
            sfSprite_setPosition(d_p->sprite, d_p->pos);
            sfRectangleShape_setPosition(d_p->hitbox, d_p->pos);
            check_landing(cur);
        }
        sfClock_restart(assets->move);
    }
}

int display_window(radar_t *assets)
{
    sfEvent event;

    while (sfRenderWindow_isOpen(assets->window)) {
        clean_lplane(assets->plane);
        analyse_events(assets->window, event, assets);
        sfRenderWindow_clear(assets->window, sfBlack);
        move_planes(assets);
        sfRenderWindow_drawSprite(assets->window, assets->s_bg, NULL);
        handle_colision(assets->plane, assets->tower);
        draw_lists(assets);
        sfRenderWindow_display(assets->window);
        if (assets->plane->head == NULL && assets->plane->tail == NULL)
            sfRenderWindow_close(assets->window);
    }
    clean_up(assets);
    return EXIT_SUCCESS;
}

int prepare_window(radar_t *assets)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfVector2f scale = {1.86, 1.7};

    assets->move = sfClock_create();
    assets->gen = sfClock_create();
    assets->window = sfRenderWindow_create(mode, "My Radar", sfResize |
        sfClose, NULL);
    if (!assets->window)
        return EXIT_FAILURE;
    assets->s_bg = sfSprite_create();
    assets->t_bg = sfTexture_createFromFile("assets/bg.png", NULL);
    sfSprite_setTexture(assets->s_bg, assets->t_bg, sfNone);
    sfSprite_setScale(assets->s_bg, scale);
    sfRenderWindow_drawSprite(assets->window, assets->s_bg, NULL);
    sfRenderWindow_setFramerateLimit(assets->window, 60);
    assets->hitbox = 1;
    assets->sprite = 1;
    return 0;
}

int init_tower_and_planes(radar_t *assets, char *filename)
{
    char *str = my_catchar(filename);
    char *tmp;
    char **tab;

    if (str == NULL){
        write(2, "files doesn't exist", 20);
        return 84;
    }
    tmp = my_strcatdup(str, "\n");
    tab = my_str_to_word_array(tmp);
    for (int i = 0; tab[i] != NULL; i++){
        if (my_strcmp(tab[i], "T") == 0) {
            init_towers(assets, tab, i + 1);
        }
        if (my_strcmp(tab[i], "A") == 0) {
            init_planes(assets, tab, i + 1);
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    radar_t *assets = malloc(sizeof(radar_t));

    assets->tower = create_list();
    assets->plane = create_list();
    if (assets == NULL) {
        write(2, "erreur de malloc", 17);
        return 84;
    }
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0)
        my_cat("src/usage.txt");
    if (argc == 2 && my_strcmp(argv[1], "-h") != 0){
        if (init_tower_and_planes(assets, argv[1]) != 84){
            prepare_window(assets);
            display_window(assets);
        }
    }
    if (argc != 2) {
        return 0;
    }
}
