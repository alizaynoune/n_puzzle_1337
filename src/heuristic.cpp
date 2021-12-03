#include "n_puzzle.hpp"

int     Euclidean_distance(int **map, t_goalPosition *goal_map)
{
    int         distance = 0;
    int         x = 0;
    int         y = 0;
    int         value = 0;
    t_position  *ptr = NULL;

    for (int i = 0; i < (g_size * g_size); i++)
    {
        y = i / g_size;
        x = i % g_size;
        value = map[y][x];
        ptr = &goal_map[value / g_size].pos[value % g_size];
        if (y != ptr->y || x != ptr->x)
        {
            distance += ((x - ptr->x) * ( x - ptr->x)) + ((y - ptr->y) * (y - ptr->y));
        }
    }

    return (distance);
}

int     Manhattan_distance(int **map, t_goalPosition *goal_map)
{
    int         distance = 0;
    int         x = 0;
    int         y = 0;
    int         value = 0;
    t_position  *ptr = NULL;

    for (int i = 0; i < (g_size * g_size); i++)
    {
        y = i / g_size;
        x = i % g_size;
        value = map[y][x];
        ptr = &goal_map[value / g_size].pos[value % g_size];
        if (y != ptr->y || x != ptr->x)
        {
            distance += (abs(x - ptr->x) + abs(y - ptr->y));
        }
    }

    return (distance);
}

static int help_inversions(int **map,int action, int start, int end, int x, int y, int i)
{
	int count = 0;
	int value = map[y][x];
	while (i < (g_size * g_size))
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
		action == _UP &&x == end ? action = _RIGHT : 0;
		action == _DOWN &&x == start ? action = _LEFT : 0;
		action == _RIGHT &&y == end ? action = _DOWN : 0;

		if (map[y][x] && map[y][x] < value)
			count++;
		i++;
	}
	return (count);
}


int     Inversions_distance(int **map, int y, int x, int i)
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
            // printf("\n");
		}
        // if (action == _LEFT && y == start){
        //     action = _UP;
        //     printf("\n");
        // }
        // else if (action == _UP && x == end){
        //     action = _RIGHT;
        //     // printf("\n");
        // }
        // else if (action == _DOWN && x == start){
        //     action = _LEFT;
        //     // printf("\n");
        // }
        // else if (action == _RIGHT && y == end){
        //     action = _DOWN;
        //     // printf("\n");
        // }
        // if (start == end)
        //     break;
        action == _LEFT && y == start ? action = _UP : 0;
		action == _UP && x == end ? action = _RIGHT : 0;
		action == _DOWN && x == start ? action = _LEFT : 0;
		action == _RIGHT && y == end ? action = _DOWN : 0;
    //    len--;
        // i++;
         if (map[y][x] && map[y][x] < value){
            // printf("[%d, %d]", value, map[y][x]);
        	inversions++;
        }
	}
    // printf("{%d, %d}", i, len);
    // printf("(%d %d)\n", value, inversions);
    // printf("_%d %d_\n", start, end);
	return (inversions);
}

int     Misplaced_distance(int **map, t_goalPosition *goal_map)
{
    int         count = 0;
    int         y = 0;
    int         x = 0;
    int         value = 0;
    t_position *ptr = NULL;

    for (int i = 0; i < (g_size * g_size); i++)
    {
        y = i / g_size;
        x = i % g_size;
        value = map[y][x];
        ptr = &goal_map[value / g_size].pos[value % g_size];
        if (y != ptr->y || x != ptr->x)
            count++;
    }

    return (count);
}


