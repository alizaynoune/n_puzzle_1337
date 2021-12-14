/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:30:54 by alzaynou          #+#    #+#             */
/*   Updated: 2021/12/14 12:30:58 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"

t_queue        *help_greedy(t_data *d)
{
    t_queue     *tmp = d->head;
    t_queue     *back = d->curr;
    int         bound = d->curr->h;

    while (tmp)
    {
        if (!tmp->visited && tmp->h <= bound)
        {
            back = tmp;
            bound = tmp->h;
        }
        tmp = tmp->next;
    }
    return (back);
}



int         greedy_search(t_data *d, int h_id)
{
    t_queue     *tmp            = NULL;
    t_queue     *last           = NULL;
    int         ret_open        = _SUCCESS;


    while (d->curr)
    {
        tmp = NULL;
        last = NULL;
        if (!d->curr->visited)
        {
            if ((ret_open = open_node(d, d->curr, &tmp, &last, h_id)) == _FAILURE)
                d->curr = help_greedy(d);
            else if (ret_open == _ERROR)
                return (_ERROR);
            else if (tmp)
            {
                d->last->next = tmp;
                tmp->prev = d->last;
                d->last = last;
                d->curr = last;
                if (d->curr && !d->curr->h)
                    break;
                if (d->curr->h > d->curr->parent->h)
                    d->curr = help_greedy(d);
            }
        }
        else
        {
            d->curr = d->curr->prev;
            if (d->curr)
            d->curr = help_greedy(d);
        }
        if (d->curr && !d->curr->h)
            break;
    }
    if (d->curr)
        print_solution(d);
    ft_free_queue(d->head);
    return (_SUCCESS);
}

t_queue     *help_star(t_data *d)
{
    t_queue     *tmp = d->curr;
    t_queue     *back = d->curr;
    int         bound_h = d->curr->h;
    int         bound_g = d->curr->g;
    int         bound = d->curr->h + d->curr->g;

    while (tmp)
    {
        if (!tmp->visited && (tmp->h <= bound_h && tmp->g <= bound_g))
        {
            back = tmp;
            bound_h = tmp->h;
            bound_g = tmp->g;
            bound   = tmp->h + tmp->g;
        }
        tmp = tmp->prev;
    }
    return (back);
    
}


int         a_star(t_data *d, int h_id)
{
    t_queue     *tmp            = NULL;
    t_queue     *last           = NULL;
    // t_queue     *curr          = d->curr;
    int         ret_open        = _SUCCESS;
    // int         bound           = INT_MAX;


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
                if (d->curr->h > d->curr->parent->h)
                    d->curr = help_star(d);
            }
        }
        else
        {
            d->curr = d->curr->prev;
            d->curr = help_star(d);

        }
        if (d->curr && !d->curr->h)
            break;
    }
    if (d->curr)
        print_solution(d);
    ft_free_queue(d->head);
    return (_SUCCESS);
}

int         solver(t_data *d, int *blank, int h_id, int (algo)(t_data *, int))
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
    SAFE((algo(d, h_id) == _ERROR), ft_free_queue(d->head), _ERROR)
    return (_SUCCESS);
}
