/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:53:48 by alzaynou          #+#    #+#             */
/*   Updated: 2021/11/23 19:14:55 by alzaynou         ###   ########.fr       */
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

/*
 * Namespaces
 */

using namespace std;


/*
 * Macros flags
 */

#define		_IDA	1
#define		_AS		2
#define		_U		4
#define		_V		8
#define		_G		16

/*
 * Macros color
 */

#define		_DEF		""
#define		_BLAC		""
#define		_GREEN		""
#define		_YALLOW		""
#define		_RED		""


/*
 * Macros Return
 */

#define		SUCCESS		0
#define		ERROR		-1
#define		TROUBLE		1

/*
 * Structrs
 */

typedef struct		s_map
{
}			t_map;

typedef struct		s_list
{
}			t_list;

typedef struct		s_file
{

}					t_file;


/*
 * Classes
 */

class		Data
{
	public:
		Data();
		int			flags;
		FILE		*fd;
		t_list		*list;
		t_map		*map;



		void	add_flag(int flag);
		int		flag_exists(int flag);
		int		open_file(char *file);

};




/*
 * Fuctions
 */

int		parse_flags(char **flags, int av, Data *data);










#endif
