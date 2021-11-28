/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:51:52 by alzaynou          #+#    #+#             */
/*   Updated: 2021/11/23 19:00:46 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"

/* handle flags */
static int parse_flags(char **flags, int av, Data *data)
{
	data->open_file(flags[1]);

	for (int i = 2; i < av; i++)
	{
		if (!strcmp(flags[i], "-ida"))
			data->add_flag(_IDA);
		else if (!strcmp(flags[i], "-as"))
			data->add_flag(_AS);
		else if (!strcmp(flags[i], "-u"))
			data->add_flag(_U);
		else if (!strcmp(flags[i], "-v"))
			data->add_flag(_V);
		else if (!strcmp(flags[i], "-g"))
			data->add_flag(_G);
		else
			throw(MyException("Unknown flag", flags[i]));
		printf("%d>>\n", data->flags);
	}

	return (_SUCCESS);
}

/* line is digit and return count of nubers */
static int is_digits(char *str)
{
	int i = 0;
	int count_nbr = 0;

	while (str[i])
	{
		if (!isdigit(str[i]) && !strchr(" \t\n\r\f\v", str[i]))
			return (-1);
		else if (isdigit(str[i]) && strchr(" \t\n\r\f\v", str[i + 1]))
			count_nbr++;
		i++;
	}
	return (count_nbr);
}

/* push line to map */
static void push_line_to_map(Data *data, char *line, int i)
{
	int k = 0;
	int value = 0;

	if (i == data->size)
	{
		free(line);
		throw(MyException("Too many lines", ""));
	}

	for (int j = 0; line[j]; j++)
	{
		if ((j == 0 && isdigit(line[j])) || (!isdigit(line[j]) && isdigit(line[j + 1])))
		{
			data->map[i].pieces[k].g_x = -1;
			data->map[i].pieces[k].g_y = -1;
			value = atoi(&line[j]);
			if (value < 0 || value >= (data->size * data->size))
			{
				free(line);
				throw(MyException("Value is out of range", ""));
			}
			data->map[i].pieces[k++].value = value;
		}
	}
}

static int read_file(Data *data)
{
	return (_SUCCESS);
}

/* allocate memory for map */
static int alloc_map(Data *data)
{
	if (!(data->map = (t_map *)malloc(sizeof(t_map) * data->size)))
		return (_FAILURE);
	memset(data->map, 0, sizeof(t_map) * data->size);
	for (int i = 0; i < data->size; i++)
	{
		if (!(data->map[i].pieces = (t_piece *)malloc(sizeof(t_piece) * data->size)))
			return (_FAILURE);
	}
	return (_SUCCESS);
}

/* parse file and fill data */
static int parse_file(Data *data)
{
	size_t len = 0;
	char *line = NULL;
	char *ptr = NULL;
	int ret = 1;
	int i = 0;
	int count_line = 0;
	int count_nbr = 0;

	while (ret > 0)
	{
		ret = getline(&line, &len, data->fd);
		/* search for comment */
		ptr = strchr(line, '#');
		/* delete comment from line */
		(ptr) ? *ptr = '\0' : 0;

		if (ret > 0 && line[0])
		{
			if ((count_nbr = is_digits(line)) == -1)
			{
				free(line);
				throw(MyException("Invalid line", ""));
			}
			else if (!count_nbr)
			{
				free(line);
				line = NULL;
				continue;
			}
			/* get size of map */
			if (i == 0)
			{
				if (count_nbr != 1 || atoi(line) < 3)
				{
					free(line);
					throw(MyException("Invalid puzzle size ", ""));
				}
				data->size = atoi(line);
				if (alloc_map(data) == _FAILURE)
				{
					free(line);
					throw(MyException("Can't alloc map", ""));
				}
			}
			else
			{
				if (count_nbr != data->size)
				{
					free(line);
					throw(MyException("lenght of lines is not equal to puzzle size", ""));
				}
				push_line_to_map(data, line, count_line);
				count_line++;
			}
			i = 1;
		}
		free(line);
		line = NULL;
	}

	return (_SUCCESS);
}

static int goal_piece(int size, t_piece *piece, t_map *map_copy)
{
	int action = _UP;
	int x = 0;
	int y = 0;
	int start = 0;
	int end = size - 1;

	for (int i = 0; i < (size * size); i++)
	{
		if ((piece->value == 0 && i == ((size * size) - 1)) || (i == piece->value - 1))
		{
			if (map_copy[y].pieces[x].value || map_copy[y].pieces[x].g_x || map_copy[y].pieces[x].g_y)
			{
				free_map(map_copy, size);
				throw(MyException("Duplicate value", ""));
			}
			// map_copy[y].pieces[x].g_x = x;
			// map_copy[y].pieces[x].g_y = y;
			piece->g_x = x;
			piece->g_y = y;
			memcpy(&map_copy[y].pieces[x], piece, sizeof(t_piece));
			// map_copy[y].pieces[x].value = (piece->value) ? piece->value : -1;
			return (_SUCCESS);
		}
		if (action == _UP && x < end)
			x++;
		else if (action == _DOWN && x > start)
			x--;

		else if (action == _RIGHT && y < end)
			y++;
		else if (action == _LEFT && y > start)
			y--;
		if (action == _LEFT && y == start)
		{
			action = _UP;
			start++;
			end--;
			x = start;
			y = start;
		}
		action == _UP &&x == end ? action = _RIGHT : 0;
		action == _DOWN &&x == start ? action = _LEFT : 0;
		action == _RIGHT &&y == end ? action = _DOWN : 0;
	}

	return (_FAILURE);
}

/* check if map is valid */
static int validation_map(Data *data)
{
	/* use this map to check if goal piece is in the map and is valid */
	t_map *map = NULL;

	/* alloc memory for new map */
	if (!(map = (t_map *)malloc(sizeof(t_map) * data->size)))
		throw(MyException("Can't alloc map", ""));
	for (int i = 0; i < data->size; i++)
	{
		if (!(map[i].pieces = (t_piece *)malloc(sizeof(t_piece) * data->size)))
		{
			free_map(map, i);
			throw(MyException("Can't alloc map", ""));
		}
		memset(map[i].pieces, 0, sizeof(t_piece) * data->size);
	}
	/* loop for check map */
	for (int i = 0; i < (data->size * data->size); i++)
	{
		if (goal_piece(data->size, &data->map[i / data->size].pieces[i % data->size], map) == _FAILURE)
		{
			free_map(map, data->size);
			throw(MyException("Invalid puzzle", ""));
		}
		if (data->map[i / data->size].pieces[i % data->size].value == 0)
		{
			// data->y_blank = i / data->size;
			// data->x_blank = i % data->size;
			data->blank[0] = i / data->size;
			data->blank[1] = i % data->size;
			// printf("%d\n", data->map[i / data->size].pieces[i % data->size].value);
		}
	}
	data->map_copy = map;

	return (_SUCCESS);
}

static int help_inversions(Data *data, int value, int action, int start, int end, int x, int y, int i)
{
	int count = 0;
	while (i < (data->size * data->size))
	{
		if (action == _UP && x < end)
			x++;
		else if (action == _DOWN && x > start)
			x--;
		else if (action == _RIGHT && y < end)
			y++;
		else if (action == _LEFT && y > start)
			y--;
		if (action == _LEFT && y == start)
		{
			action = _UP;
			start++;
			end--;
			x = start;
			y = start;
		}
		action == _UP &&x == end ? action = _RIGHT : 0;
		action == _DOWN &&x == start ? action = _LEFT : 0;
		action == _RIGHT &&y == end ? action = _DOWN : 0;

		if (data->map[y].pieces[x].value && data->map[y].pieces[x].value < value)
			count++;
		i++;
	}
	return (count);
}

/* check if map is solvable */
static int count_inversions(Data *data)
{
	int count = 0;
	int action = _UP;
	int start = 0;
	int end = data->size - 1;
	int x = 0;
	int y = 0;

	for (int i = 0; i < (data->size * data->size); i++)
	{
		if (data->map[y].pieces[x].value)
			count += help_inversions(data, data->map[y].pieces[x].value, action, start, end, x, y, i + 1);
		if (action == _UP && x < end)
			x++;
		else if (action == _DOWN && x > start)
			x--;
		else if (action == _RIGHT && y < end)
			y++;
		else if (action == _LEFT && y > start)
			y--;
		if (action == _LEFT && y == start)
		{
			action = _UP;
			start++;
			end--;
			x = start;
			y = start;
		}
		action == _UP &&x == end ? action = _RIGHT : 0;
		action == _DOWN &&x == start ? action = _LEFT : 0;
		action == _RIGHT &&y == end ? action = _DOWN : 0;
	}
	return (count % 2 ? _FAILURE : _SUCCESS);
}

int main(int ac, char **av)
{
	Data *data;
	Greedy *greedy;

	try
	{
		data = new Data();
		if (ac <= 1)
			throw(MyException("No arguments", ""));
		parse_flags(av, ac, data);
		parse_file(data);
		fclose(data->fd);
		data->fd = NULL;
		validation_map(data);
		// printf("%d\n", count_inversions(data));
		if (count_inversions(data) == _FAILURE)
			throw(MyException("This puzzle is unsolvable", ""));
		// goal_piece(data, data->size, NULL);
		// printf("===>%d\n", count_inversions(data));
		data->print_map(data->map);
		printf("\n");
		// printf("%lu\n", data->manhattan_distance(data->map));
		// data->copy_map(data->map, data->map_copy);
		// data->move_piece(data->map_copy, data->blank, _UP);
		// data->print_map(data->map_copy);
		// printf("%lu\n", data->manhattan_distance(data->map_copy));
		// data->copy_map(data->map, data->map_copy);
		// data->move_piece(data->map_copy, data->blank, _DOWN);
		// data->print_map(data->map_copy);
		// printf("%lu\n", data->manhattan_distance(data->map_copy));
		// data->copy_map(data->map, data->map_copy);
		// data->move_piece(data->map_copy, data->blank, _LEFT);
		// data->print_map(data->map_copy);
		// printf("%lu\n", data->manhattan_distance(data->map_copy));
		// data->copy_map(data->map, data->map_copy);
		// data->move_piece(data->map_copy, data->blank, _RIGHT);
		// data->print_map(data->map_copy);
		// printf("%lu\n", data->manhattan_distance(data->map_copy));
		// printf("%d\n", _LEFT ^ _LEFT);
		greedy = new Greedy();
		greedy->init_childrent(data, data->map, greedy->open_list, 0);
		
		greedy->print_queue(data);

	}
	catch (MyException &e)
	{
		e.print_msg();
		delete data;
		return (_FAILURE);
	}
	delete data;
}
