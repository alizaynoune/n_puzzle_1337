/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_var.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:31:04 by alzaynou          #+#    #+#             */
/*   Updated: 2021/12/14 12:31:07 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"

/* golbal variables */
int     g_flags = 0;
int     g_size = 0;
FILE    *g_fd = NULL;
int     **g_init_map = NULL;
t_goalPosition	*g_goal_map = NULL;
int             g_actions[4] = { _UP, _DOWN, _RIGHT, _LEFT};
t_heuristic     g_heuristic[4] =
{
    Manhattan_distance,
    Euclidean_distance,
    Inversions_distance,
    Misplaced_distance,
};
