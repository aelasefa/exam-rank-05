#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av)
{
    if (ac != 4)
        return 1;
    int width = atoi(av[1]), height = atoi(av[2]), iterations = atoi(av[3]);
    if (width <= 0 || height <= 0 || iterations < 0)
        return 1;
    char **board = malloc(sizeof(char *) * height);
    char **new_board = malloc(sizeof(char *) * height);
    if (!board || !new_board)
        return 1;
    int i = 0;
    while (i < height)
    {
        board[i] = calloc(width, sizeof(char));
        new_board[i] = calloc(width, sizeof(char));
        if (!board[i] || !new_board[i])
            return 1;
        i++;
    }
    int x = 0;
    int y = 0;
    int pen = 0;
    char c;
    while (read(0, &c, 1))
    {
        if (c == 'w' && y > 0)
            y--;
        else if (c == 's' && y < height - 1)
            y++;
        else if (c == 'a' && x > 0)
            x--;
        else if (c == 'd' && x < width - 1)
            x++;
        else if (c == 'x')
            pen = !pen;

        if (pen)
            board[y][x] = 1;
    }
    i = 0;
    while (i < iterations)
    {
        y = 0;
        while (y < height)
        {
            x = 0;
            while (x < width)
            {
                int dy = -1;
                int d = 0;
                while (dy <= 1)
                {
                    int dx = -1;
                    while (dx <= 1)
                    {
                        if ((dx || dy) && dx + x >= 0 && dx + x < width && dy + y >= 0 && dy + y < height)
                            d += board[dy + y][dx + x];
                        dx++;
                    }
                    dy++;
                }
                if (board[y][x] && (d == 2 || d == 3))
                    new_board[y][x] = 1;
                else if (!board[y][x] && d == 3)
                    new_board[y][x] = 1;
                else
                    new_board[y][x] = 0;
                x++;
            }
            y++;
        }
        int r = 0;
        while (r  < height){
            int c = 0;
            while (c < width){
                board[r][c] = new_board[r][c];
                c++;
            }
            r++;
        }
        i++;
    }

    y = 0;
    while (y < height){
        x = 0;
        while (x < width){
            if (board[y][x])
                putchar('O');
            else
                putchar(' ');
            x++;
        }
        putchar('\n');
        y++;
    }
}