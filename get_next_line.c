/*
** EPITECH PROJECT, 2018
** getnextline
** File description:
** Thomas Meurice <thomas.meurice@epitech.eu>
*/

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

char *my_strcat(char *str, char *buffer)
{
    int i = 0;
    int j = 0;
    int to_ret = 0;
    char *ret = NULL;

    for (; str[i] != '\0'; i++);
    for (; buffer[j] != '\0'; j++);
    ret = malloc(sizeof(char) * (i + j + 1));
    if (ret == NULL)
        return (NULL);
    for (int nb = 0; str[nb] != '\0'; nb++) {
        ret[to_ret] = str[nb];
        to_ret++;
    }
    for (int nb = 0; buffer[nb] != '\0'; nb++) {
        ret[to_ret] = buffer[nb];
        to_ret++;
    }
    ret[to_ret] = '\0';
    free(str);
    return (ret);
}

int verif_end_str(char *str, int *nb)
{
    int nb1 = *nb;

    for (; str[nb1] != '\0'; nb1++)
        if (str[nb1] == '\n')
            return (1);
    return (0);
}

char *verif_str(char *str, int *nb)
{
    int nb_malloc = *nb;
    int i = 0;
    char *ret = NULL;
    int j = 0;

    for (; str[nb_malloc] != '\0' && str[nb_malloc] != '\n'; nb_malloc++)
        i++;
    ret = malloc(sizeof(char) * (i + 1));
    ret[i] = '\0';
    while (i > 0) {
        ret[j] = str[*nb];
        (*nb)++;
        i--;
        j++;
    }
    (*nb)++;
    return (ret);
}

char *get_next_line(int fd)
{
    char *buffer = malloc(sizeof(char) * (READ_SIZE + 1));
    static char *str = NULL;
    static int nb = 0;
    char *to_ret = NULL;

    if (str == NULL) {
        str = malloc(sizeof(char) * 1);
        if (str == NULL) return (NULL);
        str[0] = '\0';
    }
    if (buffer == NULL || fd < 0) return (NULL);
    for (int i = 0; (i = read(fd, buffer, READ_SIZE)) > 0;) {
        buffer[i] = '\0';
        str = my_strcat(str, buffer);
        if (verif_end_str(str, &nb) == 1) {
            to_ret = verif_str(str, &nb), free(buffer);
            return (to_ret);
        }
    }
    free(buffer);
    return (NULL);
}