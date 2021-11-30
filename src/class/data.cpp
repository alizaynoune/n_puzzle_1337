/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:11:50 by alzaynou          #+#    #+#             */
/*   Updated: 2021/11/23 18:49:57 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"

/*
* Handle Class Data
*/
/* Constructor */
Data::Data()
{
	flags = 0;
	fd = 0;
	// file = NULL;
	size = 0;
	map = NULL;
	x_blank = 0;
	y_blank = 0;
}
/* Destructor */
Data::~Data()
{

	ft_free(this);
}

/* add new flag */
void Data::add_flag(int flag)
{
	this->flags |= flag;
}

/* Check if flag is set */
int Data::flag_exists(int flag)
{
	return (this->flags & flag);
}

/* Set the file descriptor */
int Data::open_file(char *name)
{
	if (!(this->fd = fopen(name, "r")))
		throw(MyException(strerror(errno), name));
	return (_SUCCESS);
}


/* copy the map src to dst */
void Data::copy_map(t_map *src, t_map *dest)
{
	for (int i = 0; i < this->size; i++)
	{
		memcpy(dest[i].pieces, src[i].pieces, sizeof(t_piece) * this->size);
	}
}

/* move the blank */
int 	Data::move_piece(t_map *map, int blank[2], int action)
{
	int		g_x_blank =  map[blank[0]].pieces[blank[1]].g_x;
	int		g_y_blank = map[blank[0]].pieces[blank[1]].g_y;
	
	if (action == _UP && blank[0])
	{
		memcpy(&map[blank[0]].pieces[blank[1]], &map[blank[0] - 1].pieces[blank[1]], sizeof(t_piece));
		map[blank[0] - 1].pieces[blank[1]].g_x = g_x_blank;
		map[blank[0] - 1].pieces[blank[1]].g_y = g_y_blank;
		map[blank[0] - 1].pieces[blank[1]].value = 0;
		return (_SUCCESS);
	}
	else if (action == _DOWN && blank[0] < this->size - 1)
	{
		memcpy(&map[blank[0]].pieces[blank[1]], &map[blank[0] + 1].pieces[blank[1]], sizeof(t_piece));
		map[blank[0] + 1].pieces[blank[1]].g_x = g_x_blank;
		map[blank[0] + 1].pieces[blank[1]].g_y = g_y_blank;
		map[blank[0] + 1].pieces[blank[1]].value = 0;
		return (_SUCCESS);
	}
	else if (action == _LEFT && blank[1])
	{
		memcpy(&map[blank[0]].pieces[blank[1]], &map[blank[0]].pieces[blank[1] - 1], sizeof(t_piece));
		map[blank[0]].pieces[blank[1] - 1].g_x = g_x_blank;
		map[blank[0]].pieces[blank[1] - 1].g_y = g_y_blank;
		map[blank[0]].pieces[blank[1] - 1].value = 0;
		return (_SUCCESS);
	}
	else if (action == _RIGHT && blank[1] < this->size - 1)
	{
		memcpy(&map[blank[0]].pieces[blank[1]], &map[blank[0]].pieces[blank[1] + 1], sizeof(t_piece));
		map[blank[0]].pieces[blank[1] + 1].g_x = g_x_blank;
		map[blank[0]].pieces[blank[1] + 1].g_y = g_y_blank;
		map[blank[0]].pieces[blank[1] + 1].value = 0;
		return (_SUCCESS);
	}

	// printf("move_piece failure: %d %d %d\n", g_x_blank, g_y_blank, action);
	return (_FAILURE);
}


size_t 		Data::manhattan_distance(t_map *map)
{
	size_t		distance = 0;

	for (int i = 0; i < (this->size * this->size); i++)
	{
		if (map[i / this->size].pieces[i % this->size].value != 0)
		{
			distance += abs(map[i / this->size].pieces[i % this->size].g_x - i % this->size);
			distance += abs(map[i / this->size].pieces[i % this->size].g_y - i / this->size);
		}
	}
	return (distance);
}



void Data::print_map(t_map *map)
{
	for (int i = 0; i < (this->size * this->size); i++){
		// printf("[%3d %2d %2d] ", map[i / this->size].pieces[i % this->size].value,
		// map[i / this->size].pieces[i % this->size].g_x, map[i / this->size].pieces[i % this->size].g_y);
		printf("%3d ", map[i / this->size].pieces[i % this->size].value);
		if ((i + 1) % this->size == 0)
			printf("\n");
	}

}

// void Data::print_step(t_map *map, t_queue *parent)
// {
	
// }