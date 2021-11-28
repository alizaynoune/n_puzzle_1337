#include "n_puzzle.hpp"

/* Constructor */
Greedy::Greedy(void)
{
    this->_heuristic = 0;
    this->n_open = 0;
    this->n_closed = 0;
    this->n_generated = 0;
    this->open_list = NULL;
}

/* Destructor */
Greedy::~Greedy(void)
{
    this->_heuristic = 0;
    this->n_open = 0;
    this->n_closed = 0;
    this->n_generated = 0;
    this->open_list = NULL;
}

/* Create a new map */
t_map *Greedy::new_map(Data *data, t_map *map, int size)
{
    t_map *n_map;

    if (!(n_map = (t_map *)malloc(sizeof(t_map) * size)))
        return (NULL);
    memset(n_map, 0, sizeof(t_map) * size);
    for (int i = 0; i < size; i++)
    {
        if (!(n_map[i].pieces = (t_piece *)malloc(sizeof(t_piece) * size)))
        {
            free_map(n_map, i);
            return (NULL);
        }
    }
    data->copy_map(map, n_map);
    return (n_map);
}

/* Gernerate heuristic value */
size_t Greedy::get_heuristic(t_map *map, int size)
{
    size_t distance = 0;

    for (int i = 0; i < (size * size); i++)
    {
        if (map[i / size].pieces[i % size].value != 0)
        {
            distance += abs(map[i / size].pieces[i % size].g_x - i % size);
            distance += abs(map[i / size].pieces[i % size].g_y - i / size);
        }
    }
    return (distance);
}

/* push a new node in the open list */
int Greedy::push_childrent(t_map *map, t_queue *parent, size_t h, int action, int *blank)
{
    t_queue *tmp;

    printf("%d\n", action);
    if (!(tmp = (t_queue *)malloc(sizeof(t_queue))))
        return (_FAILURE);
    memset(tmp, 0, sizeof(t_queue));
    tmp->current_map = map;

    if (parent)
    {
        tmp->prev = parent;
        parent->next = tmp;
    }
    tmp->h = h;
    tmp->action = action;
    tmp->blank[0] = blank[0];
    tmp->blank[1] = blank[1];
    this->open_list = tmp;
    return (_SUCCESS);
}

/* init childrent */
int Greedy::init_childrent(Data *data, t_map *map, t_queue *parent, int old_action)
{
    int action = 0;
    size_t h = SIZE_T_MAX;
    size_t h_tmp[4] = {0, 0, 0, 0};
    t_map *map_tmp[4] = {NULL, NULL, NULL, NULL};
    int *blank = !(parent) ? data->blank : parent->blank;
    int blank_tmp[2] = {0, 0};

    action = _UP | _DOWN | _LEFT | _RIGHT;
    action ^= old_action;

    if (action & _UP)
    {
        if (!(map_tmp[0] = new_map(data, map, data->size)))
        {
            return (_FAILURE);
        }
        if (data->move_piece(map_tmp[0], blank, _UP) == _SUCCESS)
        {
            h_tmp[0] = this->get_heuristic(map_tmp[0], data->size);
            h_tmp[0] > h ? action ^= _UP : h = h_tmp[0];
        }
        else
            action ^= _UP;
    }
    if (action & _DOWN)
    {
        if (!(map_tmp[1] = new_map(data, map, data->size)))
        {
            return (_FAILURE);
        }
        if (data->move_piece(map_tmp[1], blank, _DOWN) == _SUCCESS)
        {
            h_tmp[1] = this->get_heuristic(map_tmp[1], data->size);
            h_tmp[1] > h ? action ^= _DOWN : h = h_tmp[1];
        }
        else
            action ^= _DOWN;
    }
    if (action & _LEFT)
    {
        if (!(map_tmp[2] = new_map(data, map, data->size)))
        {
            return (_FAILURE);
        }
        if (data->move_piece(map_tmp[2], blank, _LEFT) == _SUCCESS)
        {
            h_tmp[2] = this->get_heuristic(map_tmp[2], data->size);
            h_tmp[2] > h ? action ^= _LEFT : h = h_tmp[2];
        }
        else
            action ^= _LEFT;
    }
    if (action & _RIGHT)
    {
        if (!(map_tmp[3] = new_map(data, map, data->size)))
        {
            return (_FAILURE);
        }
        if (data->move_piece(map_tmp[3], blank, _RIGHT) == _SUCCESS)
        {
            h_tmp[3] = this->get_heuristic(map_tmp[3], data->size);
            h_tmp[3] > h ? action ^= _RIGHT : h = h_tmp[3];
        }
        else
            action ^= _RIGHT;
    }




    if (action & _UP)
    {
        blank_tmp[0] = blank[0] - 1;
        blank_tmp[1] = blank[1];
        if (this->push_childrent(map_tmp[0], parent, h_tmp[0], _UP, blank_tmp) == _FAILURE)
        {
            for (int i = 0; i < 4; i++)
                free_map(map_tmp[i], data->size);
            return (_FAILURE);
        }
        map_tmp[0] = NULL;
    }
    if (action & _DOWN)
    {
        blank_tmp[0] = blank[0] + 1;
        blank_tmp[1] = blank[1];
        if (this->push_childrent(map_tmp[1], parent, h_tmp[1], _DOWN, blank_tmp) == _FAILURE)
        {
            for (int i = 1; i < 4; i++)
                free_map(map_tmp[i], data->size);
            return (_FAILURE);
        }
        map_tmp[1] = NULL;
    }
    if (action & _LEFT)
    {
        blank_tmp[0] = blank[0];
        blank_tmp[1] = blank[1] - 1;
        if (this->push_childrent(map_tmp[2], parent, h_tmp[2], _LEFT, blank_tmp) == _FAILURE)
        {
            for (int i = 2; i < 4; i++)
                free_map(map_tmp[i], data->size);
            return (_FAILURE);
        }
        map_tmp[2] = NULL;
    }
    if (action & _RIGHT)
    {
        blank_tmp[0] = blank[0];
        blank_tmp[1] = blank[1] + 1;
        if (this->push_childrent(map_tmp[3], parent, h_tmp[3], _RIGHT, blank_tmp) == _FAILURE)
        {
            free_map(map_tmp[3], data->size);
            return (_FAILURE);
        }
        map_tmp[3] = NULL;
    }
    for (int i = 0; i < 4; i++)
    {
        if (map_tmp[i])
            free_map(map_tmp[i], data->size);
    }
    for (int i = 0; i < 4; i++)
    {
        printf("[%lu %d] ", h_tmp[i], action);
    }
    printf("\n");
    return (_SUCCESS);
}

/* for test print queue */
void Greedy::print_queue(Data *data)
{
    t_queue *tmp = this->open_list;

    while (tmp)
    {
        printf("%d\n", tmp->action);
        data->print_map(tmp->current_map);
        printf("\n");
        tmp = tmp->prev;
    }
}
