#include "n_puzzle.hpp"

int     Euclidean_distance(int **map, int y, int x)
{
    t_position  *ptr = &g_goal_map[map[y][x] / g_size].pos[map[y][x] % g_size];

    return (floor(sqrt(((x - ptr->x) * ( x - ptr->x)) + ((y - ptr->y) * (y - ptr->y)))));
}

int     Manhattan_distance(int **map, int y, int x)
{
    t_position      *ptr = &g_goal_map[map[y][x] / g_size].pos[map[y][x] % g_size];
    
    return (abs(x - ptr->x) + abs(y - ptr->y));
}


int     Inversions_distance(int **map, int y, int x)
{
	int action      = 0;
    int y_start = y < (g_size / 2) ? y % (g_size / 2) : g_size - y - 1;
    int x_start = x < (g_size / 2) ? x % (g_size / 2) : g_size - x - 1;
    int start = y_start < x_start ? y_start : x_start;
	int end         = (g_size - 1) - start;
    int value       = map[y][x];
	int inversions  = 0;

    action = (y == start && x < end) ? _UP : action;
    action = (y < end && x == end) ? _RIGHT : action;
    action = (y == end && x > start) ? _DOWN : action;
    action = (y > start && x == start) ? _LEFT : action;
    
	while (y != (g_size / 2) || x != ((g_size - 1) / 2))
	{
		if (action == _UP && x < end)
			x++;
		else if (action == _DOWN && x > start)
			x--;
		else if (action == _RIGHT && y < end)
			y++;
		else if (action == _LEFT && y > start)
			y--;
		if (action == _LEFT && y == start)
		{
			action = _UP;
			start++;
			end--;
			x = start;
			y = start;
		}
        action == _LEFT && y == start ? action = _UP : 0;
		action == _UP && x == end ? action = _RIGHT : 0;
		action == _DOWN && x == start ? action = _LEFT : 0;
		action == _RIGHT && y == end ? action = _DOWN : 0;
         if (map[y][x] && map[y][x] < value)
        	inversions++;
	}
	return (inversions);
}

int     Misplaced_distance(int **map, int y, int x)
{
    t_position      *ptr = &g_goal_map[map[y][x] / g_size].pos[map[y][x] % g_size];
    return ((ptr->y == y && ptr->x == x) ? 0 : 1);
}


