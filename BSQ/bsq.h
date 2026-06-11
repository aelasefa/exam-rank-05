#ifndef BSQ_H
#define BSQ_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_map
{
    int rows;
    int cols;

    char obstacle;
    char empty;
    char full;

    char **grid;
} t_map;

int parse_header(FILE *fp, t_map *map);
int read_map(FILE *fp, t_map *map);
void bsq(t_map *map);
#endif