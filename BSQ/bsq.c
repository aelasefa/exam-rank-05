#include "bsq.h"

int valid_char(t_map *map, char c)
{
    return (c == map->obstacle || c == map->empty);
}

int min3(int a, int b, int c)
{
    int m = a;
    if (b < m)
        m = b;
    if (c < m)
         m = c;
    return m;
}

int ft_atoi(char *str)
{
    int i = 0, sign = 1, res = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-') sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res * sign);
}

int ft_strlen (char *str)
{
    int i = 0;
    while (str[i]) i++;
    return (i);
}

int parse_header(FILE *fp, t_map *map)
{
    char *line = NULL;
    size_t len = 0;
    int len_line;

    if (getline(&line, &len, fp) == -1)
        return (0);
    len_line = ft_strlen(line);
    if (len_line < 5 || line[len_line - 1] != '\n')
        return (0);
    map->empty = line[len_line - 4];
    map->obstacle = line[len_line - 3];
    map->full = line[len_line - 2];
    line[len_line - 4] = '\0';
    map->rows = ft_atoi(line);
    if (map->rows <= 0)
        return (0);
    if (map->empty == map->obstacle || map->empty == map->full
        || map->obstacle == map->full)
        return (0);
    return (1);
}

int read_map(FILE *fp, t_map *map)
{
    char *line =  NULL;
    size_t len = 0;

    map->grid = malloc(sizeof(char *)* map->rows);
    if (!map->grid)
        return 0;
    int i = 0;
    while (i < map->rows)
    {
        if (getline(&line , &len, fp) == -1)
            return 0;
        int j = 0;
        while (line[j] && line[j] != '\n')
            j++;
        if (i == 0)
            map->cols = j;
        if (j != map->cols)
            return 0;
        map->grid[i] = malloc(j + 1);
        for (int j = 0; line[j] && line[j] != '\n'; j++)
        {
            if (!valid_char(map, line[j]))
                return 0;
            map->grid[i][j] = line[j];
        }
        map->grid[i][j] = '\0';
        i++;
    }
    free(line);
    return 1;
}

void bsq(t_map *map)
{
    int **dp;
    dp = malloc(sizeof(int *) * map->rows);
    if (!dp)
        return ;
    int max = 0;
    int max_i = 0;
    int max_j = 0;

    for (int i = 0; i < map->rows; i++)
    {
        dp[i] = calloc(map->cols, sizeof(int));
    }

    for (int i = 0; i < map->rows; i++)
    {
        for (int j = 0; j < map->cols; j++)
        {
            if (map->grid[i][j] == map->obstacle)
                dp[i][j] = 0;
            else if (map->grid[i][j] == map->empty)
            {
                if (i == 0 || j == 0)
                    dp[i][j] = 1;
                else 
                {
                    dp[i][j] = 1 + min3(dp[i][j -1], dp[i - 1][j], dp[i - 1][j -1]);
                }
            }
            
            if (dp[i][j] > max)
            {
                max = dp[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }
    for (int i = max_i - max + 1; i <= max_i; i++)
    {
        for (int j = max_j - max + 1; j <= max_j; j++)
        {
            map->grid[i][j] = map->full;
        }
    }
    for (int i = 0; i < map->rows; i++)
    {
        printf("%s\n", map->grid[i]);
    }
}