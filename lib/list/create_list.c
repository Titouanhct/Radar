/*
** EPITECH PROJECT, 2024
** create_list
** File description:
** Function that creates the empty linked l_circle
*/

#include "list.h"
#include <stdlib.h>

list_t *create_list(void)
{
    list_t *l_circle = malloc(sizeof(list_t));

    l_circle->head = NULL;
    l_circle->tail = NULL;
    l_circle->size = 0;
    return l_circle;
}
