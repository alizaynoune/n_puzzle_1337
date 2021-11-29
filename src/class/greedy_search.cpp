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
    size_t m_b = 0;
    int x = 0;
    int y = 0;

    for (int i = 0; i < (size * size); i++)
    {
        y = i / size;
        x = i % size;
        // printf("y=>%d x=>%d i=>%d size=>%d\n", y, x, i, (size * size));
        if (map[y].pieces[x].value != 0 && (map[y].pieces[x].g_y != y || map[y].pieces[x].g_x != x))
        {
            // printf("val=%d g_y=%d g_x=%d y=%d x=%d\n", map[y].pieces[x].value, map[y].pieces[x].g_y, map[y].pieces[x].g_x, y , x);
            distance += abs(map[y].pieces[x].g_x - x);
            distance += abs(map[y].pieces[x].g_y - y);
            m_b++;
        }
    }
    // printf("distance=>%lu\n\n", distance);
    return (distance + m_b);
}

/* push a new node in the open list */
int Greedy::push_childrent(t_map *map, size_t h, int action, int *blank, t_queue *parent)
{
    t_queue *tmp;

    // printf("[%d]\n", action);
    if (!(tmp = (t_queue *)malloc(sizeof(t_queue))))
        return (_FAILURE);
    memset(tmp, 0, sizeof(t_queue));
    tmp->current_map = map;

    if (this->open_list)
    {
        tmp->prev = this->open_list;
        this->open_list->next = tmp;
        // this->queue = tmp;
    }
    if (!this->queue)
        this->queue = tmp;
    tmp->h = h;
    tmp->action = action;
    tmp->blank[0] = blank[0];
    tmp->blank[1] = blank[1];
    tmp->parent = parent;
    // if (parent)
    //     parent->child = tmp;
    this->open_list = tmp;
    return (_SUCCESS);
}

/* init childrent */
int Greedy::init_childrent(Data *data, t_map *map, t_queue *parent)
{
    int action[4] = {_UP, _DOWN, _LEFT, _RIGHT};
    int old_action = 0;
    size_t h = SIZE_T_MAX;
    size_t h_tmp[4] = {0, 0, 0, 0};
    t_map *map_tmp[4] = {NULL, NULL, NULL, NULL};
    int *blank = !(parent) ? data->blank : parent->blank;
    int blank_tmp[2] = {0, 0};

    // printf("[%d]\n", old_action);
    parent->action == _UP ? old_action = _DOWN : 0;
    parent->action == _DOWN ? old_action = _UP : 0;
    parent->action == _LEFT ? old_action = _RIGHT : 0;
    parent->action == _RIGHT ? old_action = _LEFT : 0;
    for (int i = 0; i < 4; i++)
    {
        if (old_action == action[i])
            continue;
        if (!(map_tmp[i] = new_map(data, map, data->size)))
        {
            for (int i = 0; i < 4; i++)
                if (map_tmp[i])
                    free_map(map_tmp[i], data->size);
            return (_FAILURE);
        }
        if (data->move_piece(map_tmp[i], blank, action[i]) == _SUCCESS)
            h_tmp[i] = this->get_heuristic(map_tmp[i], data->size);
        else
        {
            h_tmp[i] = SIZE_T_MAX;
            free_map(map_tmp[i], data->size);
            map_tmp[i] = NULL;
        }
        h = (h_tmp[i] < h) ? h_tmp[i] : h;
    }
    for (int i = 0; i < 4; i++)
    {
        if (h_tmp[i] == h && map_tmp[i])
        {
            if (action[i] == _UP)
            {
                blank_tmp[0] = blank[0] - 1;
                blank_tmp[1] = blank[1];
            }
            else if (action[i] == _DOWN)
            {
                blank_tmp[0] = blank[0] + 1;
                blank_tmp[1] = blank[1];
            }
            else if (action[i] == _LEFT)
            {
                blank_tmp[0] = blank[0];
                blank_tmp[1] = blank[1] - 1;
            }
            else if (action[i] == _RIGHT)
            {
                blank_tmp[0] = blank[0];
                blank_tmp[1] = blank[1] + 1;
            }
            if (this->push_childrent(map_tmp[i], h_tmp[i], action[i], blank_tmp, parent) == _FAILURE)
            {
                for (int i = 0; i < 4; i++)
                    if (map_tmp[i])
                        free_map(map_tmp[i], data->size);
                return (_FAILURE);
            }
            else
            {
                this->n_generated++;
                map_tmp[i] = NULL;
            }
        }
        else if (map_tmp[i])
            free_map(map_tmp[i], data->size);
    }
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
        printf("g=%d h=%d f=%d y=%d x=%d action=%d vis=%d\n", tmp->g, tmp->h, tmp->f, tmp->blank[0], tmp->blank[1], tmp->action, tmp->visited);
        tmp = tmp->prev;
    }
}

/* Greedy algorithm */
int Greedy::greedy_search(Data *data)
{
    t_map *map = data->map;
    size_t h = this->get_heuristic(map, data->size);
    t_queue *tmp = NULL;
    int *blank = data->blank;
    int action = 0;
    int old_action = 0;

    if (!h)
        return (_SUCCESS);
    n_open++;
    this->push_childrent(map, h, action, blank, NULL);
    tmp = this->queue;
    while (tmp)
    {
        if (!tmp->h)
            break;
        if (!tmp->visited && this->init_childrent(data, tmp->current_map, tmp) == _SUCCESS)
        {
            h = tmp->h;
            tmp->visited = 1;
        }
        tmp = tmp->next;
    }
    printf("\n");
    if (tmp)
    {
        t_queue *tmp2 = NULL;
        while (tmp)
        {
            tmp2 = tmp;
            tmp = tmp->parent;
            if (tmp)
                tmp->child = tmp2;
        }
        this->print_step(data, tmp2);
    }

    this->free_queue(data);

    return (_FAILURE);
}

void Greedy::print_step(Data *data, t_queue *parent)
{
    t_queue *tmp = parent;

    while (tmp)
    {
        if (tmp->action == _UP)
            printf("UP\n");
        else if (tmp->action == _DOWN)
            printf("DOWN\n");
        else if (tmp->action == _LEFT)
            printf("LEFT\n");
        else if (tmp->action == _RIGHT)
            printf("RIGHT\n");
        data->print_map(tmp->current_map);
        tmp = tmp->child;
    }
}

void Greedy::free_queue(Data *data)
{
    t_queue *queue = this->queue;
    t_queue *tmp = NULL;
    while (queue)
    {
        tmp = queue;
        queue = queue->next;
        if (tmp->current_map)
            free_map(tmp->current_map, data->size);
        free(tmp);
    }
}
