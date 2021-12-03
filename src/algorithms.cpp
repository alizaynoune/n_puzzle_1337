#include "n_puzzle.hpp"

// int         **new_map(int **map)
// {

//     return()
// }

int         move_piece(int **map, int *blank, int action)
{
    int     bck;
    if (action == _UP)
    {
        if (!blank[0])
            return (_FAILURE);
        map[blank[0]][blank[1]] = map[blank[0] - 1][blank[1]];
        map[blank[0] - 1][blank[1]] = 0;
        blank[0]--;
    }
    else if (action == _DOWN)
    {
        if (blank[0] + 1 >= g_size)
            return (_FAILURE);
        map[blank[0]][blank[1]] = map[blank[0] + 1][blank[1]];
        map[blank[0] + 1][blank[1]] = 0;
        blank[1]++;
    }
    else if (action == _RIGHT)
    {
        if (blank[1] + 1 >= g_size)
            return (_FAILURE);
        map[blank[0]][blank[1]] = map[blank[1]][blank[1] + 1];
        map[blank[0]][blank[1] + 1] = 0;
        blank[1]++;
    }
        
    else if (action == _LEFT)
    {
        if (!blank[1])
            return (_FAILURE);
        map[blank[0]][blank[1]] = map[blank[0]][blank[1] - 1];
        map[blank[0]][blank[1] - 1] = 0;
        blank[1]--;
    }

    return (_SUCCESS);
}

int         ft_distance(int **map, int (heuristic)(int **, int, int))
{
    int distance = 0;

    for (int i = 0; i < (g_size * g_size); i++)
    {
        distance += heuristic(map, i / g_size, i % g_size);
    }
    printf("<<%d>>>\n", distance);
    return(distance);
}



// ft_lstdel(t_list **alst, void (*del)(void *, size_t))
int         ida_star(int *blank, int h_id)
{

    ft_distance(g_init_map, g_heuristic[h_id]);
    if (move_piece(g_init_map, blank, _UP) == _SUCCESS)
        print_map(g_init_map);
    return (_SUCCESS);
}

int         greedy_search(int *blank, int h_id)
{

    return (_SUCCESS);
}


int         a_star(int *blank, int h_id)
{

    return (_SUCCESS);
}

int         solver(int *blank, int h_id, int (algo)(int *, int))
{
    algo(blank, h_id);
    return (_SUCCESS);
}


int         dfs(int **map)
{


    return (_SUCCESS);
}
