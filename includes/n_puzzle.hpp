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

typedef struct		s_map{
	int				x;
	int				y;
	int			**map;
}					t_map;

typedef struct		s_queue{
	int				x;
	int				y;
	int				g;
	int				h;
	int				f;
	int				move;
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
	int		bound;
	int		g;
	int		h;
	int		f;
	int		move;
	int		x;
	int		y;
	int		**map_start;
	int		**map_goal;
	int		**map_copy;

	/* Methods */

	/*
	 * IDA* algorithm
	 */
	int		IDA_star_search(int **map_start, int **map_goal);
	int		IDA_star_search_bound(int **map_start, int **map_goal);

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

class		Data{
	public:
		/*
		 * Constructors
		 */
		Data(void);
		/*
		 * Destructors
		 */
		~Data(void);
		/*
		 * Variables
		 */
		int			flags;
		FILE		*fd;
		t_file		*file;
		int			size;
		int			**map_start;
		int			**map_goal;

		/*
		 * Functions
		 */
		void	add_flag(int flag);
		int		flag_exists(int flag);
		int		open_file(char *file);
		int		read_file(void);
		void	push_line(char *line);
		void	print_line(void); // for test

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

// int		parse_flags(char **flags, int av, Data *data);
// int		parse_file(char *file, Data *data);
// int		parse_map(char *file, Data *data);
// int		parse_goal_state(char *file, Data *data);
void		ft_free(Data *data);











#endif
