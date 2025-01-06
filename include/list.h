/*
** EPITECH PROJECT, 2024
** list.h
** File description:
** .h for my linked list library
*/

#ifndef LIST_H_
    #define LIST_H_

typedef struct node_s {
    void *data;
    struct node_s *prev;
    struct node_s *next;
} node_t;

typedef struct list_s {
    node_t *head;
    node_t *tail;
    int size;
} list_t;

list_t *create_list(void);
void pushback(list_t *list, void *data);
void pushfront(list_t *list, void *data);
void popfront(list_t *list);
void popback(list_t *list);
void destroy_node(list_t *list, node_t *node);
int my_apply_on_nodes(list_t *list, void *(*f)(void *));
int my_apply_on_matching_nodes(list_t *list, void *(*f)(),
    void const *data_ref, int (*cmp)());
void add_node_to_list(list_t *list, node_t *node);
void my_putchar(char c);
int my_isneg(int nb);
int my_put_nbr(int nb);
void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(const char *str);
char *my_strcatdup(char *dest, char *src);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
char *my_strdup(char const *str);
char **my_str_to_word_array(char const *str);
int my_put_bignbr(long long int nb);
char **rev_array(char **arr);
char **sort_time(char **buffer);
int mini_printf(const char *format, ...);
int my_cat(char *filepath);
char *my_catchar(char *filepath);
char *my_int_str(int nb);


#endif /* !LIST_H_ */
