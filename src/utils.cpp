/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:31:27 by alzaynou          #+#    #+#             */
/*   Updated: 2021/12/14 12:31:30 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"


void        print_solution(t_data *d)
{
    t_queue     *tmp = d->curr;
    int         moves = 0;

    while (tmp)
    {
        if (tmp->parent)
        {
            tmp->parent->child = tmp;
            moves++;
        }
        tmp = tmp->parent;
    }
    tmp = d->head;
    printf("TIME: %d\nSPACE: %d\nMOVES: %d\nSIZE: %d\n", d->time_complexity, d->space_complexity, moves, g_size);
    while (tmp)
    {
        printf("\n");
        print_map(tmp->current_map);
        tmp = tmp->child;
    } 
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

bool         is_alredy_open(int **map, t_queue *parent)
{
    t_queue     *tmp = parent;
    int         cmp = 0;

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

void print_map(int **map)
{
	for (int i = 0; i < (g_size * g_size); i++)
	{
		printf("%4d", map[i / g_size][i % g_size]);
		if ((i + 1) % g_size == 0)
			printf("\n");
	}
}


