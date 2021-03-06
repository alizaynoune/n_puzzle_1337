/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:04:52 by alzaynou          #+#    #+#             */
/*   Updated: 2021/12/14 13:04:54 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"

/* Free the memory allocated for the board */
void ft_free_map(int **map, int size)
{
    if (map)
    {
        for (int i = 0; i < size; i++)
        {
            if (map[i])
                free(map[i]);
        }
        free(map);
    }
}

/* Free the memory allocated for the board */
void        ft_free_position(t_goalPosition *map)
{
    if (map)
    {
        for (int i = 0; i < g_size; i++)
        {
            if (map[i].pos)
                free(map[i].pos);
        }
        free(map);
    }
}

/* Free the memory allocated for the queue */
void        ft_free_queue(t_queue *q)
{
    t_queue     *tmp;

    while (q)
    {
        tmp = q;
        q = q->next;
        ft_free_map(tmp->current_map, g_size);
        free(tmp);
    }
}

