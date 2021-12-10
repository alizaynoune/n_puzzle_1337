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
// #include <limits.h>

/*
 * Namespaces
 */

using namespace std;

/*
 * Macros flags
 */
/* IDA* algorithm */
#define		_IDA 1

#define 	_A	2
/* Greedy algorithm */
#define 	_G 4
/* Eucilidean distance */
#define 	_E 8
/* Manhattan distance */
#define 	_M 16
/* Heuristic */
#define 	_H 32
/* Visualization */
#define 	_V 64

#define 	_MP	128
#define 	_I	256

#define _MAX_MOVE		4

// 0 1 2 3

/*
 * Macros color
 */

#define _DEF "\033[0m"
#define _BLAC "\033[30m"
#define _GREEN "\033[32m"
#define _YALLOW "\033[33m"
#define _RED "\033[31m"
#define _BLUE "\033[34m"
#define _PURPLE "\033[35m"
#define _CYAN "\033[36m"
#define _GRAY "\033[37m"

/*
 * Macros Return
 */

#define _SUCCESS 0
#define _FAILURE 1
#define _ERROR 2

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
// extern int g_heuristic;
extern FILE	*g_fd;
extern int	**g_init_map;
extern int	g_actions[_MAX_MOVE];
// extern int **g_goal_map;

/* 
 * Define Return Errors
 */
# define FT_EXPR(expr, f) if (expr){f; return (_ERROR);}
# define FT_ERROR(f, codeError){f; return (codeError);}

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
	int f;
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
	// int				blank[2];
	int				time_complexity;
	int				space_complexity;
	int				**map;
	int				f_bound;
	// int				*blanks[_MAX_MOVE];
	t_goalPosition	*position;
	t_queue			*head;
	t_queue			*curr;
	t_queue			*last;
}					t_data;

typedef int (*t_heuristic)(int **, int, int);

extern	t_heuristic		g_heuristic[];

void print_map(int **map);// for test

void		ft_free_map(int **map, int size);
void		ft_free_position(t_goalPosition *map);
void        ft_free_queue(t_queue *q);
void        ft_free_child(int ***child, int len);


int     Misplaced_distance(int **map, int y, int x);
int     Manhattan_distance(int **map, int y, int x);
int     Inversions_distance(int **map, int y, int x);
int     Euclidean_distance(int **map, int y, int x);

int         ida_star(t_data *d, int *blank, int h_id);
int         greedy_search(t_data *d, int *blank, int h_id);
int         a_star(t_data *d, int *blank, int h_id);

int         solver(t_data *d, int *blank, int h_id, int (algo)(t_data *, int *, int));


#endif
