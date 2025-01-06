/*
** EPITECH PROJECT, 2024
** my_swap.c
** File description:
** ..
*/

#include "radar.h"

void my_swap(int *a, int *b)
{
    int temp = *b;

    *b = *a;
    *a = temp;
}
