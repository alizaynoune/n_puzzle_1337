#include "n_puzzle.hpp"


// for test

void        print_queue(t_queue *tmp)
{
    printf("%d   %d   %d\n", tmp->h, tmp->g, tmp->g + tmp->h);
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

// /* push new element to end of queue */
// void        push_to_last(t_data *d, t_queue *tmp, int h, int *blank, int move)
// {
//     d->last->next = tmp;
//     tmp->prev = d->last;
    
//     d->last = tmp;
//     tmp->parent = d->curr;
//     tmp->h = h;
//     tmp->g = d->curr->g + 1;
//     tmp->move = move;
//     memcpy(tmp->blank, blank, sizeof(int) * 2);
// }

bool         is_alredy_open(int **map, t_queue *parent)
{
    t_queue     *tmp = parent;
    int         cmp = 0;
    // int         j = _MAX_MOVE + 1;

    while(tmp)
    {
        cmp = 0;
        for (int i = 0; i < g_size; i++)
        {
            if ((cmp = memcmp(tmp->current_map[i], map[i], sizeof(int) * g_size)))
                break;
        }
        if (!cmp){
            return (true);
        }
        tmp = tmp->parent;
        // j--;
    }
    return(false);
}

void        copy_map(int **dest, int **src)
{
    for(int i = 0; i < g_size; i++)
        memcpy(dest[i], src[i], sizeof(int) * g_size);
}

void        push_to_queue(t_queue **queue, t_queue *node, t_queue *parent, t_queue **last)
{
    t_queue         *tmp = (*queue);

    node->parent = parent;
    if (!*queue)
        (*queue) = node;
    else if ((*queue)->h <= node->h)
    {
        node->next = (*queue);
        (*queue)->prev = node;
        (*queue) = node;
    }
    else
    {
        while (tmp->next && tmp->h > node->h)
            tmp = tmp->next;
        if (tmp->h <= node->h)
        {
            if (tmp->prev)
            {
                tmp->prev->next = node;
                node->prev = tmp->prev;
            }
            node->next = tmp;
            tmp->prev = node;
        }
        else
        {
            if (tmp->next)
            {
                tmp->next->prev = node;
            }
            node->next = tmp->next;
            node->prev = tmp;
            tmp->next = node;
        }
    }
    if (!node->next)
        (*last) = node;
}

/* generate new child from current node */
int         open_node(t_data *d, t_queue *node, t_queue **queue, t_queue **last, int id_heuristic)
{
    int         move = _UP | _RIGHT | _DOWN | _LEFT;
    int         **map = NULL;
    int         distance = INT_MAX;
    int         blanks[2];
    t_queue     *tmp = NULL;
    // t_queue     *tmp2 = NULL;

    node->visited = 1;


    (node->move & _DOWN) || !(node->blank[0]) ? move ^= _UP : 0;
    (node->move & _LEFT) || (node->blank[1] + 1 >= g_size) ? move ^= _RIGHT : 0;
    (node->move & _RIGHT) || !(node->blank[1]) ? move ^= _LEFT : 0;
    (node->move & _UP) || (node->blank[0] + 1 >= g_size) ? move ^= _DOWN : 0;
    for (int i = 0; i < _MAX_MOVE; i++)
    {
        if (g_actions[i] & move)
        {
            if (map)
                copy_map(map, node->current_map);
            else if (!(map = new_map(node->current_map)))
            {
                ft_free_queue(*queue);
                return (_ERROR);
            }
            move_piece(map, node->blank, g_actions[i]);
            if (is_alredy_open(map, node) == false)
            {
                distance = ft_distance(map, g_heuristic[id_heuristic]);
                memcpy(blanks, node->blank, sizeof(int) * 2);
                g_actions[i] & _UP ? blanks[0] -= 1 : 0;
                g_actions[i] & _DOWN ? blanks[0] += 1 : 0;
                g_actions[i] & _LEFT ? blanks[1] -= 1 : 0;
                g_actions[i] & _RIGHT ? blanks[1] += 1 : 0;
                if (!(tmp = element_queue(map)))
                {
                    ft_free_map(map, g_size);
                    ft_free_queue(*queue);
                    return (_ERROR);
                }
                tmp->h = distance;
                tmp->g = node->g + 1;
                memcpy(tmp->blank, blanks, sizeof(int) * 2);
                push_to_queue(queue, tmp, node, last);
                // push_to_last(d, tmp, distance, blanks, g_actions[i]);
                d->space_complexity++;
                map = NULL;
            }
        }
    }
    if (tmp){
        d->time_complexity++;
    }
    if (map)
        ft_free_map(map, g_size);
    if (!tmp)
        return (_FAILURE);
    return (_SUCCESS);
}



void        print_solution(t_data *d)
{
    t_queue     *tmp = d->curr;
    int         moves = 0;

    while (tmp)
    {
        if (tmp->parent)
        {
            tmp->parent->child = tmp;
        }
        tmp = tmp->parent;
    }
    tmp = d->head;
    while (tmp)
    {
        printf("%d %d %d\n", tmp->h, tmp->g, tmp->g + tmp->h);
        print_map(tmp->current_map);
        printf("\n");
        moves++;
        tmp = tmp->child;
    }
    printf("[%d]\n", moves);
    
    
}


t_queue     *bfs(t_data *d)
{
    t_queue     *tmp = d->curr;
    t_queue     *tmp2 = d->curr;
    int         cmp = INT_MAX;

    while (tmp)
    {
        if (!tmp->visited && tmp->h < cmp)
        {
            cmp = tmp->h;
            tmp2 = tmp;
        }
        tmp = tmp->next;
    }

    return (tmp2);
}

t_queue        *ft_back(t_data *d)
{
    t_queue     *tmp = d->last;
    t_queue     *back = NULL;
    int         bound = INT_MAX;

    while (tmp)
    {
        // printf("v");
        if (!tmp->visited && tmp->h <= bound)
        {
            back = tmp;
            bound = tmp->h;
        }
        tmp = tmp->prev;
    }
    return (back);
}



int         greedy_search(t_data *d, int *blank, int h_id)
{
    t_queue     *tmp            = NULL;
    t_queue     *last           = NULL;
    // t_queue     *curr          = d->curr;
    int         ret_open        = _SUCCESS;


    while (d->curr)
    {
        tmp = NULL;
        last = NULL;
        if (!d->curr->visited)
        {
            if ((ret_open = open_node(d, d->curr, &tmp, &last, h_id)) == _FAILURE)
                d->curr = ft_back(d);
            else if (ret_open == _ERROR)
                return (_ERROR);
            else if (tmp)
            {
                d->last->next = tmp;
                tmp->prev = d->last;
                d->last = last;
                d->curr = last;
                if (d->curr->h >= d->curr->parent->h)
                    d->curr = ft_back(d);
            }
            print_queue(d->curr);
        }
        else
            d->curr = ft_back(d);
        // usleep(100000);
        // printf(">>>%d\n", ret_open);
        if (d->curr && !d->curr->h)
            break;
    }
    printf("\n");
    if (d->curr)
        print_solution(d);
    ft_free_queue(d->head);
    return (_SUCCESS);
}

t_queue         *ida_star_helper(t_data *d, int limit, int bound)
{
    t_queue     *tmp = d->last;
    t_queue     *back = NULL;
    // int         bound = INT_MAX;
    
    while (tmp)
    {
        if (!tmp->visited && tmp->g <= limit && (tmp->h + tmp->g) <= bound)
        {
            back = tmp;
            bound = tmp->h + tmp->g;
        }
        tmp = tmp->prev;
    }
    return (back);
}

int         new_bound(t_data *d, int limit)
{
    t_queue     *tmp = d->head;
    int         bound = INT_MAX;

    while (tmp)
    {
        if (!tmp->visited &&  tmp->g + tmp->h < bound)
            bound = tmp->g + tmp->h;
        // printf("\n-------------------\n");
        // print_queue(tmp);
        // printf("\n=>%d %d\n", tmp->g + tmp->h, tmp->parent->h + tmp->parent->g);
        tmp = tmp->next;
    }
    // printf(">>%d %d\n", bound, limit);
    return(bound);
}


int         ida_star(t_data *d,int *blank, int h_id)
{
    int         limit = 1;
    int         ret_open = _SUCCESS;
    int         sc = 0;
    int         tc = 0;
    int         bound = d->curr->h + d->curr->g;
    // int         n_bound = INT_MAX;

    t_queue     *tmp = NULL;
    t_queue     *last = NULL;


 print_queue(d->curr);
    while (d->curr)
    {
        tmp = NULL;
        last = NULL;
        if (!d->curr->visited && d->curr->g <= limit && d->curr->g + d->curr->h <= bound)
        {
            if (d->curr->g + d->curr->h <= bound)
                if ((ret_open = open_node(d, d->curr, &tmp, &last, h_id)) == _ERROR)
                    return (_ERROR);
            if (tmp)
            {
                d->last->next = tmp;
                tmp->prev = d->last;
                d->last = last;
                d->curr = last;
                // if ((d->curr->h + d->curr->g) > bound)
                if (d->curr && d->curr->g == limit && d->curr->g + d->curr->h > bound)
                {
                    d->curr = ida_star_helper(d, limit, bound);
                    // if (d->curr)
                    // n_bound = d->curr->h + d->curr->g;
                }
            }
                
        }
        else if (d->curr)
            d->curr = d->curr->prev;
            // d->curr = ida_star_helper(d, limit, bound);
        
        if (d->curr && !d->curr->h)
            break;
        if (!d->curr)
        {
            printf("<<s%d  t%d>>\n", d->space_complexity, d->time_complexity);
            bound = new_bound(d, limit);
            ft_free_queue(d->head->next);
            d->head->next = NULL;
            d->curr = d->head;
            d->last = d->head;
            d->head->visited = 0;
            d->space_complexity = 1;
            d->time_complexity = 1;
            limit++;
        }
    }

    
    // new_bound(d, limit);

    if (d->curr)
        print_solution(d);
    ft_free_queue(d->head);
    


    
    return (_SUCCESS);
}

t_queue     *help_star(t_data *d)
{
    t_queue     *tmp = d->last;
    t_queue     *back = NULL;
    int         bound = INT_MAX;
    
    while (tmp)
    {
        if (!tmp->visited && (tmp->h + tmp->g) <= bound)
        {
            back = tmp;
            bound = tmp->h + tmp->g;
        }
        tmp = tmp->prev;
    }
    return (back);
    
}


int         a_star(t_data *d, int *blank, int h_id)
{
    t_queue     *tmp            = NULL;
    t_queue     *last           = NULL;
    t_queue     *curr          = d->curr;
    int         ret_open        = _SUCCESS;


    while (d->curr)
    {
        tmp = NULL;
        last = NULL;
        if (!d->curr->visited)
        {
            if ((ret_open = open_node(d, d->curr, &tmp, &last, h_id)) == _ERROR)
                return (_ERROR);
            else if (tmp)
            {
                d->last->next = tmp;
                tmp->prev = d->last;
                d->last = last;
                d->curr = last;
                if (d->curr->parent || (d->curr->h + d->curr->g) >= (d->curr->parent->h + d->curr->parent->g))
                    d->curr = help_star(d);
            }
            if (d->curr)
            print_queue(d->curr);
        }
        else
            d->curr = help_star(d);
        // if ((d->curr->h + d->curr->g) >= (d->curr->parent->h + d->curr->parent->g))
        //             d->curr = help_star(d);
        if (d->curr && !d->curr->h)
            break;
        // tmp = NULL;
    }
    printf("\n");
    if (d->curr)
        print_solution(d);
    ft_free_queue(d->head);
    return (_SUCCESS);
}

int         solver(t_data *d, int *blank, int h_id, int (algo)(t_data *, int *, int))
{
    if (!(d->map = new_map(g_init_map)))
        return (_ERROR);
    if (!(d->curr = element_queue(g_init_map)))
        return (_ERROR);
    d->space_complexity++;
    d->time_complexity++;
    d->head = d->curr;
    d->last = d->curr;
    d->head->g = 0;
    d->curr->h = ft_distance(d->curr->current_map, g_heuristic[h_id]);
    memcpy(d->curr->blank, blank, sizeof(int) * 2);
    SAFE((algo(d, blank, h_id) == _ERROR), ft_free_queue(d->head), _ERROR)

    // ft_free_queue(d->head);
    return (_SUCCESS);
}
