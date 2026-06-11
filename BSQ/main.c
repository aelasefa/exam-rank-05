#include "bsq.h"

int main(int ac, char **av)
{
    FILE *fp;
    t_map map;
    int i;

    if (ac == 1)
    {
        if (!parse_header(stdin, &map) || !read_map(stdin, &map))
        {
            fprintf(stderr, "error map\n");
            return 1;
        }
        bsq(&map);
        return 0;
    }
    i = 1;
    while (i <  ac)
    {
        fp = fopen(av[i], "r");
        if (!fp || !parse_header(fp, &map) || !read_map(fp, &map))
        {
            fprintf(stderr, "error map\n");
            if (fp != NULL)
                fclose(fp);
            return 1;
        }
        bsq(&map);
        if (i < ac - 1)
            printf("\n");
        fclose(fp);
        i++;
    }
}