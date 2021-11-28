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


/*
 * Namespaces
 */

using namespace std;


/*
 * Macros flags
 */
/* IDA* algorithm */
#define		_IDA	1
/* A* algorithm */
#define		_AS		2
/* Uniform Cost Search */
#define		_U		4
/* Manhattan distance */
#define		_M		8
/* Euclidean distance */
#define		_E		16
/* Visualization */
#define		_V		32
/* Generate random puzzle */
#define		_G		64

/*
 * Macros color
 */

#define		_DEF		"\033[0m"
#define		_BLAC		"\033[30m"
#define		_GREEN		"\033[32m"
#define		_YALLOW		"\033[33m"
#define		_RED		"\033[31m"
#define		_BLUE		"\033[34m"
#define		_PURPLE		"\033[35m"
#define		_CYAN		"\033[36m"
#define		_GRAY		"\033[37m"

/*
 * Macros Return
 */

#define		_SUCCESS	0
#define		_FAILURE	1
#define		_ERROR		2

/*
 * Macros Move
 */
#define		_UP			1
#define		_DOWN		2
#define		_LEFT		4
#define		_RIGHT		8


/*
 * Structrs
 */

typedef struct		s_piece{
	int				g_x;
	int				g_y;
	int				value;
}					t_piece;

typedef struct		s_map{
	t_piece			*pieces;
}					t_map;

typedef struct		s_queue{
	int				g;
	int				h;
	int				f;
	int				action;
	t_map			*current_map;
	int				visited;
	struct s_queue	*next;
	struct s_queue	*prev;
}					t_queue;



typedef struct		s_file{
	char			*line;
	s_file			*next;
}					t_file;


/*
 * Classes
 */




class		IDA_star{
	/* Constructors */
	IDA_star(void);
	/* Destructors */
	~IDA_star(void);
	
	/* Attributes */
	int			bound;
	int			open_list_size;
	int			closed_list_size;
	int			depth;
	int			x_blank;
	int			y_blank;
	t_queue		*open_list;


	/* Methods */
	int			get_bound(t_map *map);
	int			init_child(t_map *map, t_queue *child, int old_action);	


};

class		A_star{
	/* Constructors */
	A_star(void);
	/* Destructors */
	~A_star(void);
};

class		Greedy{
	/* Constructors */
	Greedy(void);
	
	/* Destructors */
	~Greedy(void);
};

/* initioalize the data */
class		Data{
	public:
		/* Constructors */
		Data(void);
		
		/* Destructors */
		~Data(void);
		
		/* Attributes */
		int			flags;
		FILE		*fd;
		t_file		*file;
		int			size;
		int			x_blank;
		int			y_blank;
		t_map		*map;
		t_map		*map_copy;

		/* Methods */
		void		print_map(t_map *map);
		void		add_flag(int flag);
		int			flag_exists(int flag);
		int			open_file(char *file);
		void		copy_map(t_map *src, t_map *dest);
		int			move_piece(t_map *map, int x_blank, int y_blank, int action);
		size_t		manhattan_distance(t_map *map);
};

/*
 * My Exceptions
 */

class	MyException : public exception{
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

void		ft_free(Data *data);
void        free_map(t_map *map, int size);










#endif
