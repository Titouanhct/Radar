/*
** EPITECH PROJECT, 2024
** radar
** File description:
** add_node_to_list
*/

#include "list.h"

void add_node_to_list(list_t *list, node_t *node)
{
    if (!node || !list)
        return;
    if (list->tail)
        list->tail->next = node;
    list->tail = node;
    if (!list->head)
        list->head = node;
    list->size++;
}
