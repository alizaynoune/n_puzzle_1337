#include "n_puzzle.hpp"

float     Euclidean_distance(int **map, t_goalPosition *goal_map)
{

    return(0);
}

int     Manhattan_distance(int **map, t_goalPosition *goal_map)
{

    return (0);
}


int     Inversions(int **map, t_goalPosition *goal_map)
{

    return (0);
}

int     Misplaced(int **map, t_goalPosition *goal_map)
{
    int     count = 0;
    int     y = 0;
    int     x = 0;
    int     value = 0;
    t_position *ptr = NULL;

    for (int i = 0; i < (g_size * g_size); i++)
    {
        y = i / g_size;
        x = i % g_size;
        value = map[y][x];
        value = value == 0 ? 15 : value -1;
        // printf("%d %d \n", value / g_size, value % g_size);
        ptr = &goal_map[value / g_size].pos[value % g_size];
        if (y != ptr->y || x != ptr->x)
            count++;
        // {
        //     printf("%4d  %d %d   %d %d %d\n", map[y][x], ptr->y, ptr->x, y, x, count);

        // }
    }

    return (count);
}

