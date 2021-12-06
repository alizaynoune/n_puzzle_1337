#include "n_puzzle.hpp"


// for test

void        print_queue(t_queue *tmp)
{
    printf("%d\n", tmp->h);
    print_map(tmp->current_map);
}

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
    return (elem);
}

int         move_piece(int **map, int blank[2], int action)
{
    if (action == _UP)
    {
        if (!blank[0])
            return (_FAILURE);
        map[blank[0]][blank[1]] = map[blank[0] - 1][blank[1]];
        map[blank[0] - 1][blank[1]] = 0;
    }
    else if (action == _DOWN)
    {
        if (blank[0] + 1 >= g_size)
            return (_FAILURE);
        map[blank[0]][blank[1]] = map[blank[0] + 1][blank[1]];
        map[blank[0] + 1][blank[1]] = 0;
    }
    else if (action == _RIGHT)
    {
        if (blank[1] + 1 >= g_size)
            return (_FAILURE);
        map[blank[0]][blank[1]] = map[blank[0]][blank[1] + 1];
        map[blank[0]][blank[1] + 1] = 0;
    }
        
    else if (action == _LEFT)
    {
        if (!blank[1])
            return (_FAILURE);
        map[blank[0]][blank[1]] = map[blank[0]][blank[1] - 1];
        map[blank[0]][blank[1] - 1] = 0;
    }
    return (_SUCCESS);
}


int         ft_distance(int **map, int (heuristic)(int **, int, int))
{
    int distance = 0;

    for (int i = 0; i < (g_size * g_size); i++)
    {
        if (map[i / g_size][i % g_size])
            distance += heuristic(map, i / g_size, i % g_size);
    }
    
    return(distance);
}

/* push new element to end of queue */
void        push_to_last(t_data *d, t_queue *tmp, int h, int *blank, int move)
{
    d->last->next = tmp;
    tmp->prev = d->last;
    
    d->last = tmp;
    tmp->parent = d->curr;
    tmp->h = h;
    tmp->g = d->curr->g + 1;
    tmp->move = move;
    memcpy(tmp->blank, blank, sizeof(int) * 2);
}

bool         is_alredy_open(t_data *d, int **map)
{
    t_queue     *tmp = d->curr;
    int         cmp = 0;

    while(tmp)
    {
        cmp = 0;
        for (int i = 0; i < g_size; i++)
        {
            if ((cmp = memcmp(tmp->current_map[i], map[i], sizeof(int) * g_size)))
                break;
        }
        if (!cmp)
            return (true);
        tmp = tmp->parent;
    }
    return(false);
}

void        copy_map(int **dest, int **src)
{
    for(int i = 0; i < g_size; i++)
        memcpy(dest[i], src[i], sizeof(int) * g_size);
}

/* generate new child from current node */
int         generated_child(t_data *d, int h_id)
{
    int         move = _UP | _RIGHT | _DOWN | _LEFT;
    int         moves[_MAX_MOVE] = {_UP, _DOWN, _LEFT, _RIGHT};
    int         **map = NULL;
    int         distance[_MAX_MOVE] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
    bool        is_exists[_MAX_MOVE] = {true, true, true, true};
    int         cmp_d = INT_MAX;
    int         blanks[2];
    t_queue     *tmp = NULL;

    d->curr->visited = 1;

    (d->curr->move & _DOWN) || !(d->curr->blank[0]) ? move ^= _UP : 0;
    (d->curr->move & _LEFT) || (d->curr->blank[1] + 1 >= g_size) ? move ^= _RIGHT : 0;
    (d->curr->move & _RIGHT) || !(d->curr->blank[1]) ? move ^= _LEFT : 0;
    (d->curr->move & _UP) || (d->curr->blank[0] + 1 >= g_size) ? move ^= _DOWN : 0;

    if (move & _UP){
        // printf("UP\n");
        copy_map(d->map, d->curr->current_map);
        move_piece(d->map, d->curr->blank, _UP);
        if (is_alredy_open(d, d->map) == false)
            distance[0] = ft_distance(d->map, g_heuristic[h_id]);
        cmp_d > distance[0] ? cmp_d = distance[0] : 0;
    }
    if (move & _DOWN){
        // printf("DOWN\n");
        copy_map(d->map, d->curr->current_map);
        move_piece(d->map, d->curr->blank, _DOWN);
        if (is_alredy_open(d, d->map) == false)
            distance[1] = ft_distance(d->map, g_heuristic[h_id]);
        cmp_d > distance[1] ? cmp_d = distance[1] : 0;
    }
    if (move & _LEFT){
        // printf("LEFT\n");
        copy_map(d->map, d->curr->current_map);
        move_piece(d->map, d->curr->blank, _LEFT);
        if (is_alredy_open(d, d->map) == false)
            distance[2] = ft_distance(d->map, g_heuristic[h_id]);
        cmp_d > distance[2] ? cmp_d = distance[2] : 0;
    }
    if (move & _RIGHT){
        // printf("RIGHT\n");
        copy_map(d->map, d->curr->current_map);
        move_piece(d->map, d->curr->blank, _RIGHT);
        // if (is_alredy_open(d, d->map) == _FAILURE)
        if (is_alredy_open(d, d->map) == false)
            distance[3] = ft_distance(d->map, g_heuristic[h_id]);
        cmp_d > distance[3] ? cmp_d = distance[3] : 0;
    }
    if (cmp_d == INT_MAX)
        return (_SUCCESS);
    for (int i = 0; i < _MAX_MOVE; i++)
    {
        if (cmp_d == distance[i])
        {
            // printf("[%d]\n", moves[i]);
            if (!(map = new_map(d->curr->current_map)))
                return (_ERROR);
            move_piece(map, d->curr->blank, moves[i]);
            memcpy(blanks, d->curr->blank, sizeof(int) * 2);
             d->space_complexity++;
            if (!(tmp = element_queue(map)))
            {
                // ft_free_child(maps, _MAX_MOVE);
                // free(distance);
                free(map);
                return (_ERROR);
            }
            moves[i] & _UP ? blanks[0] -= 1 : 0;
            moves[i] & _DOWN ? blanks[0] += 1 : 0;
            moves[i] & _RIGHT ? blanks[1] += 1 : 0;
            moves[i] & _LEFT ? blanks[1] -= 1 : 0;
            push_to_last(d, tmp, cmp_d, blanks, moves[i]);
            // break;
        }
    }
    if (tmp){
        d->curr = tmp;
        d->time_complexity++;
    }
    return (_SUCCESS);
}


// ft_lstdel(t_list **alst, void (*del)(void *, size_t))
int         ida_star(t_data *d,int *blank, int h_id)
{

    // ft_distance(g_init_map, g_heuristic[h_id]);
    // if (move_piece(g_init_map, blank, _UP) == _SUCCESS)
    //     print_map(g_init_map);
    return (_SUCCESS);
}

void        free_curr_node(t_queue *curr)
{
    if (curr->next)
        curr->next->prev = curr->prev;
    if (curr->prev)
        curr->prev->next = curr->next;
    ft_free_map(curr->current_map, g_size);
    free(curr);
}



int         greedy_search(t_data *d, int *blank, int h_id)
{
    int         h               = 0;
    int         old_move        = 0;
    t_queue     *tmp            = NULL;
    int         ret_gen         = _SUCCESS;
    int         dest            = 0;

    if (!(d->curr = element_queue(g_init_map)))
        return (_ERROR);
    d->space_complexity++;
    d->head = d->curr;
    d->last = d->curr;
    d->curr->h = ft_distance(d->curr->current_map, g_heuristic[h_id]);
    dest = d->curr->h;
    memcpy(d->curr->blank, blank, sizeof(int) * 2);
    

    while (d->curr && ret_gen == _SUCCESS)
    {
        if (!d->curr->visited){
            ret_gen = generated_child(d, h_id);
            // print_queue(d->curr);
            // d->curr = d->curr->next;
            // usleep(100000);
        }
        else{
            // printf("%dprev\n", d->curr->h);
            // tmp = d->curr;
            d->curr = d->curr->prev;
            // d->space_complexity--;
            // free_curr_node(tmp);
        }
        if (d->curr && d->curr->h == 0)
            break;
        // else
        //     d->curr = d->curr->next;
    }





    printf("\n");
    if (d->curr)
        print_map(d->curr->current_map);
    return (_SUCCESS);
}


int         a_star(t_data *d, int *blank, int h_id)
{

    return (_SUCCESS);
}

int         solver(t_data *d, int *blank, int h_id, int (algo)(t_data *, int *, int))
{
    if (!(d->map = new_map(g_init_map)))
        return (_ERROR);
    SAFE((algo(d, blank, h_id) == _ERROR), ft_free_queue(d->head), _ERROR)

    ft_free_queue(d->head);
    return (_SUCCESS);
}


int         dfs(int **map)
{


    return (_SUCCESS);
}
