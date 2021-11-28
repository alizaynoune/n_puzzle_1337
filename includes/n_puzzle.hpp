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
// #include <limits.h>

/*
 * Namespaces
 */

using namespace std;

/*
 * Macros flags
 */
/* IDA* algorithm */
#define _IDA 1
/* A* algorithm */
#define _AS 2
/* Uniform Cost Search */
#define _U 4
/* Manhattan distance */
#define _M 8
/* Euclidean distance */
#define _E 16
/* Visualization */
#define _V 32
/* Generate random puzzle */
#define _G 64

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
 * Structrs
 */

typedef struct s_piece
{
	int g_x;
	int g_y;
	int value;
} t_piece;

typedef struct s_map
{
	t_piece *pieces;
} t_map;

typedef struct s_queue
{
	int g;
	int h;
	int f;
	int blank[2];
	int action;
	t_map *current_map;
	int visited;
	struct s_queue *next;
	struct s_queue *prev;
} t_queue;

typedef struct s_file
{
	char *line;
	s_file *next;
} t_file;

/*
 * Classes
 */

class IDA_star
{
	/* Constructors */
	IDA_star(void);
	/* Destructors */
	~IDA_star(void);

	/* Attributes */
	int bound;
	int open_list_size;
	int closed_list_size;
	int depth;
	int x_blank;
	int y_blank;
	int blank[2];
	t_queue *open_list;

	/* Methods */
	int get_bound(t_map *map);
	int init_childrent(t_map *map, t_queue *parent, int old_action);
	int push_childrent(t_map *map, t_queue *parent);
};

class A_star
{
	/* Constructors */
	A_star(void);
	/* Destructors */
	~A_star(void);
};

/* initioalize the data */
class Data
{
public:
	/* Constructors */
	Data(void);

	/* Destructors */
	~Data(void);

	/* Attributes */
	int flags;
	FILE *fd;
	t_file *file;
	int size;
	int x_blank;
	int y_blank;
	int blank[2];
	t_map *map;
	t_map *map_copy;

	/* Methods */
	void print_map(t_map *map); // delete it
	void add_flag(int flag);
	int flag_exists(int flag);
	int open_file(char *file);
	void copy_map(t_map *src, t_map *dest);
	int move_piece(t_map *map, int blank[2], int action);
	size_t manhattan_distance(t_map *map);
};
class Greedy
{
public:
	/* Constructors */
	Greedy(void);

	/* Destructors */
	~Greedy(void);

	/* Attributes */
	size_t _heuristic;
	size_t n_open;
	size_t n_closed;
	size_t n_generated;
	t_queue *open_list;

	/* Methods */
	void		print_queue(Data *data);
	t_map		*new_map(Data *data, t_map *map, int size);
	size_t		get_heuristic(t_map *map, int size);
	int			init_childrent(Data *data, t_map *map, t_queue *parent, int old_action);
	int			push_childrent(t_map *map, t_queue *parent, size_t h, int action, int *blank);
};
/*
 * My Exceptions
 */

class MyException : public exception
{
public:
	MyException(const char *msg, const char *msg2);
	~MyException(void) throw();
	void print_msg(void);

private:
	const char *msg;
	const char *msg2;
};

/*
 * Fuctions
 */

void ft_free(Data *data);
void free_map(t_map *map, int size);

#endif
