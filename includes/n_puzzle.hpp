/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:53:48 by alzaynou          #+#    #+#             */
/*   Updated: 2021/11/24 12:01:09 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_PUZZLE_H
#define N_PUZZLE_H

/*
 * Includes
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <regex>
#include <unistd.h>
#include <cstdlib>
#include <math.h>


/*
 * Macros flags
 */

/* A Star algorithm */
#define 	_A	1
/* Greedy algorithm */
#define 	_G 2
/* Eucilidean distance */
#define 	_E 4
/* Manhattan distance */
#define 	_M 8
/* Misplaced tiles */
#define 	_MP	16
/* Invesion of the puzzle */
#define 	_I	32
/* Number of moves */
#define _MAX_MOVE		4


/*
 * Macros Return
 */

#define _SUCCESS 0
#define _FAILURE 1
#define _ERROR -1

/*
 * Macros Move
 */
#define _UP 1
#define _DOWN 2
#define _LEFT 4
#define _RIGHT 8

/*
 * extern variables
 */
extern int g_flags;
extern int g_size;
extern int	**g_init_map;
extern int	g_actions[_MAX_MOVE];



/* Define SAFE expr, function, and codeError */
# define SAFE(expr, f, codeError)if (expr){f; return (codeError);}


/*
 * Structrs
 */

typedef struct		s_piece
{
	int				g_x;
	int				g_y;
	int				value;
}					t_piece;

typedef struct		s_map
{
	t_piece			*pieces;
} 					t_map;

typedef struct		s_position
{
	int				y;
	int				x;
}					t_position;

typedef struct		s_goalPosition
{
	t_position		*pos;
}					t_goalPosition;


extern t_goalPosition	*g_goal_map;

typedef struct s_queue
{
	int g;
	int h;
	int blank[2];
	int move;
	int **current_map;
	int visited;
	struct s_queue *next;
	struct s_queue *prev;
	struct s_queue *parent;
	struct s_queue *child;
} t_queue;


typedef struct		s_data
{
	int				time_complexity;
	int				space_complexity;
	int				**map;
	int				f_bound;
	t_goalPosition	*position;
	t_queue			*head;
	t_queue			*curr;
	t_queue			*last;
}					t_data;

typedef int (*t_heuristic)(int **, int, int);

extern	t_heuristic		g_heuristic[];

void print_map(int **map);
void		ft_free_map(int **map, int size);
void		ft_free_position(t_goalPosition *map);
void        ft_free_queue(t_queue *q);
void        ft_free_child(int ***child, int len);
int			Misplaced_distance(int **map, int y, int x);
int			Manhattan_distance(int **map, int y, int x);
int			Inversions_distance(int **map, int y, int x);
int			Euclidean_distance(int **map, int y, int x);
int         greedy_search(t_data *d, int h_id);
int         a_star(t_data *d, int h_id);
int         solver(t_data *d, int *blank, int h_id, int (algo)(t_data *, int));
void        print_solution(t_data *d);
int         **new_map(int **map);
t_queue     *element_queue(int **map);
int         move_piece(int **map, int blank[2], int action);
int         open_node(t_data *d, t_queue *node, t_queue **queue, t_queue **last, int id_heuristic);
int         ft_distance(int **map, int (heuristic)(int **, int, int));


#endif