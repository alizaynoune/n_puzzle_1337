#include "n_puzzle.hpp"

int     g_flags = 0;
int     g_size = 0;
FILE    *g_fd = NULL;
int     **g_init_map = NULL;
t_goalPosition	*g_goal_map = NULL;
t_heuristic     g_heuristic[4] =
{
    Manhattan_distance,
    Inversions_distance,
    Euclidean_distance,
    Misplaced_distance,
};
