#include "n_puzzle.hpp"

int         **new_map(int **map)
{
    int     **n_map = NULL;

    SAFE(!(n_map = (int **)malloc(sizeof(int *) * g_size)), (fprintf(stderr, "%s\n", strerror(errno))) , NULL)
    memset(n_map, 0, sizeof(int *) * g_size);

    for(int i = 0; i < g_size; i++)
    {
        SAFE(!(n_map[i] = (int *)malloc(sizeof(int) * g_size)), (ft_free_map(n_map, i), fprintf(stderr, "%s\n", strerror(errno))), NULL)
        memcpy(n_map[i], map[i], sizeof(int) * g_size);
    }

    return(n_map);
}

t_queue     *element_queue(int **map)
{
    t_queue     *elem = NULL;

    SAFE(!(elem = (t_queue *)malloc(sizeof(t_queue))), fprintf(stderr, "%s\n", strerror(errno)), NULL)
    memset(elem, 0, sizeof(t_queue));
    elem->current_map = map;
    // *space_complexity += 1;
    return (elem);
}

int         move_piece(int **map, int *blank, int action)
{
    // printf("<<[[%d, %d]]>>>\n", blank[0], blank[1]);
    if (action == _UP)
    {
        if (!blank[0])
            return (_FAILURE);
        map[blank[0]][blank[1]] = map[blank[0] - 1][blank[1]];
        map[blank[0] - 1][blank[1]] = 0;
        blank[0]--;
        // printf("_UP\n");
    }
    else if (action == _DOWN)
    {
        if (blank[0] + 1 >= g_size)
            return (_FAILURE);
        map[blank[0]][blank[1]] = map[blank[0] + 1][blank[1]];
        map[blank[0] + 1][blank[1]] = 0;
        blank[0]++;
        // printf("_DOWN\n");
    }
    else if (action == _RIGHT)
    {
        if (blank[1] + 1 >= g_size)
            return (_FAILURE);
        map[blank[0]][blank[1]] = map[blank[0]][blank[1] + 1];
        map[blank[0]][blank[1] + 1] = 0;
        blank[1]++;
        // printf("_RIGHT\n");
    }
        
    else if (action == _LEFT)
    {
        if (!blank[1])
            return (_FAILURE);
        map[blank[0]][blank[1]] = map[blank[0]][blank[1] - 1];
        map[blank[0]][blank[1] - 1] = 0;
        blank[1]--;
        // printf("_LEFT\n");
    }
    // printf("<<[[%d, %d]]>>>\n\n", blank[0], blank[1]);
    return (_SUCCESS);
}


int         ft_distance(int **map, int (heuristic)(int **, int, int))
{
    int distance = 0;

    for (int i = 0; i < (g_size * g_size); i++)
    {
        distance += heuristic(map, i / g_size, i % g_size);
        // printf("<<%d>>>\n", distance);
    }
    
    return(distance);
}

int         generated_child(t_data *d, int h_id, int flag)
{
    int         len = 0;
    int         move[_MAX_MOVE] = {_UP, _RIGHT, _DOWN, _LEFT};
    int         ***maps = NULL;
    int         *distance = NULL;
    int         cmp_d = d->curr->h;
    int         *blanks;
    t_queue     *tmp = NULL;
    t_queue     *tmp2 = NULL;

    d->curr->visited = 1;
    (d->curr->move & _UP) || (d->curr->blank[0] + 1 >= g_size) ? move[2] ^= _DOWN : 0;
    (d->curr->move & _RIGHT) || !(d->curr->blank[1]) ? move[3] ^= _LEFT : 0;
    (d->curr->move & _DOWN) || !(d->curr->blank[0]) ? move[0] ^= _UP : 0;
    (d->curr->move & _LEFT) || (d->curr->blank[1] + 1 >= g_size) ? move[1] ^= _RIGHT : 0;

    if (!(maps = (int ***)malloc(sizeof(int **) * _MAX_MOVE)))
        return (_ERROR);
    memset(maps, 0, sizeof(int **) * 4);
    if (!(distance = (int *)malloc(sizeof(int) * _MAX_MOVE)))
    {
        free(maps);
        return (_ERROR);
    }
    if (!(blanks = (int *)malloc((sizeof(int) * _MAX_MOVE) * 2)))
    {
        free(maps);
        free(distance);
        return (_ERROR);
    }
    for (int i = 0; i < _MAX_MOVE; i++)
    {
        blanks[i * 2] = d->curr->blank[0];
        blanks[(i * 2) + 1] = d->curr->blank[1];
        if (move[i])
        {
             if (!(maps[i] = new_map(d->curr->current_map)))
            {
                ft_free_child(maps, i);
                free(distance);
                free(maps);
                return (_ERROR);
            }
            move_piece(maps[i], &blanks[i * 2], move[i]);
            distance[i] = ft_distance(maps[i], g_heuristic[h_id]);
            cmp_d = (distance[i] < cmp_d) ? distance[i] : cmp_d;
        }
        else
            distance[i] = INT_MAX;
    }
        for (int i = 0; i < _MAX_MOVE; i++)
        {
            if (distance[i] == cmp_d)
            {
                d->space_complexity++;
                if (!(tmp = element_queue(maps[i])))
                {
                    ft_free_child(maps, len);
                    free(distance);
                    free(maps);
                    return (_ERROR);
                }
                else if (!flag)
                {
                    d->last->next = tmp;
                    tmp->prev = d->last;
                    d->last = tmp;
                    tmp->prev = d->curr;
                    memcpy(tmp->blank, &blanks[i * 2], sizeof(int) * 2);
                    tmp->h = cmp_d;
                    tmp->move = move[i];
                }
                else
                {
                    tmp->next = d->curr->next;
                    d->curr->next = tmp;
                    // tmp->prev = d->curr;
                    memcpy(tmp->blank, &blanks[i * 2], sizeof(int) * 2);
                    tmp->h = cmp_d;
                    tmp->move = move[i];
                }
                maps[i] = NULL;
            }
        }
        d->time_complexity++;
    // }
    // else if (!flag)
    //     d->curr = d->curr->next;
    ft_free_child(maps, _MAX_MOVE);
    free(distance);
    free(maps);
    free(blanks);

    

    return (_SUCCESS);
}

t_queue     *best_destance(t_queue *curr)
{
    t_queue     *tmp = curr->next;
    t_queue     *tmp2 = NULL;

    while (tmp)
    {
        if (!tmp->visited && tmp->h < curr->h)
            tmp2 = tmp;
        tmp = tmp->next;
    }

    return (tmp2);
}


// ft_lstdel(t_list **alst, void (*del)(void *, size_t))
int         ida_star(t_data *d,int *blank, int h_id)
{

    // ft_distance(g_init_map, g_heuristic[h_id]);
    // if (move_piece(g_init_map, blank, _UP) == _SUCCESS)
    //     print_map(g_init_map);
    return (_SUCCESS);
}

int         greedy_search(t_data *d, int *blank, int h_id)
{
    int         h               = 0;
    int         old_move        = 0;
    int         **current_map   = NULL;
    t_queue     *tmp            = NULL;
    int         ret_gen         = _SUCCESS;

    if(!(current_map = new_map(g_init_map)))
        return(_ERROR);
    SAFE(!(d->curr = element_queue(current_map)), ft_free_map(current_map, g_size), _ERROR)
    d->space_complexity++;
    d->head = d->curr;
    d->last = d->curr;
    d->curr->h = ft_distance(d->curr->current_map, g_heuristic[h_id]);
    // d->curr->visited = 1;
    // d->curr->blank = blank;
    memcpy(d->curr->blank, blank, sizeof(int) * 2);
    // if (generated_child(d, h_id, 1) == _ERROR)
    //     return(_ERROR);
   
    

    while (d->curr && ret_gen == _SUCCESS)
    {
        // if (!d->curr->visited)
        // {
        //     ret_gen = generated_child(d, h_id, 0);
        //     if (d->curr->h == 0)
        //         break;
        // }
        // else
        //     d->curr = d->curr->next;
        if (!d->curr->visited)
            ret_gen = generated_child(d, h_id, 0);
        // d->curr = d->curr->next;
        // tmp = best_destance(d->head);
        // if (d->curr && d->curr->h == 0)
        //     break;
        // if (tmp)
        //     d->curr = tmp;
        // else
            d->curr = d->curr->next;
        if (d->curr && d->curr->h == 0)
            break;
        // else
        //     d->curr = d->curr->next;
        // // usleep(100000);
    }
    // printf("%d<<\n", d->curr->h);
    if (d->curr)
        print_map(d->curr->current_map);
    // tmp = d->head;
    // while (tmp)
    // {
    //     printf("\n<<[%d]", tmp->h);
    //     print_map(tmp->current_map);
    //     tmp = tmp->next;
    // }
    return (_SUCCESS);
}


int         a_star(t_data *d, int *blank, int h_id)
{

    return (_SUCCESS);
}

int         solver(t_data *d, int *blank, int h_id, int (algo)(t_data *, int *, int))
{
    SAFE((algo(d, blank, h_id) == _ERROR), ft_free_queue(d->head), _ERROR)

    ft_free_queue(d->head);
    return (_SUCCESS);
}


int         dfs(int **map)
{


    return (_SUCCESS);
}
