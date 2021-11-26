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

/* push line to map_start */
static int push_line_to_map(Data *data, char *line, int i)
{
	int k = 0;

	if (i == data->size)
		return (_FAILURE);
	// for (int j = 0; line[j]; j++)
	// {
	// 	if ((j == 0 && isdigit(line[j])) || (!isdigit(line[j]) && isdigit(line[j + 1])))
	// 	{
	// 		data->map_start[i][k++] = atoi(&line[j]);
	// 	}
	// }

	for (int j = 0; j < line[j]; j++)
	{
		if ((j == 0 && isdigit(line[j])) || (!isdigit(line[j]) && isdigit(line[j + 1])))
		{
			data->map[i].pieces[k++].value = atoi(&line[j]);
		}
	}

	return (_SUCCESS);
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
	for (int i = 0; i < data->size; i++)
	{
		if (!(data->map[i].pieces = (t_piece *)malloc(sizeof(t_piece) * data->size)))
			return (_FAILURE);
	}





	// if (!(data->map_start = (int **)malloc(sizeof(int *) * data->size)))
	// 	return (_FAILURE);
	// if (!(data->map_goal = (int **)malloc(sizeof(int *) * data->size)))
	// 	return (_FAILURE);
	// /* set map_start and map_goal by null */
	// memset(data->map_start, 0, sizeof(int *) * data->size);
	// memset(data->map_goal, 0, sizeof(int *) * data->size);
	// /* alloc map_start  and map_goal */
	// for (int i = 0; i < data->size; i++)
	// {
	// 	if (!(data->map_start[i] = (int *)malloc(sizeof(int) * data->size)))
	// 		return (_FAILURE);
	// 	if (!(data->map_goal[i] = (int *)malloc(sizeof(int) * data->size)))
	// 		return (_FAILURE);
	//}
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
			if (i == 0)
			{
				if (count_nbr != 1)
				{
					free(line);
					throw(MyException("Invalid map size ", ""));
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
					throw(MyException("lenght of lines is not equal to map size", ""));
				}
				if (push_line_to_map(data, line, count_line) == _FAILURE)
				{
					free(line);
					throw(MyException("To much lines", ""));
				}
				count_line++;
			}
			i = 1;
		}
		free(line);
		line = NULL;
	}

	return (_SUCCESS);
}

/* check if map is valid */
static int validation_map(Data *data)
{
	int x = 0;
	int y = 0;


	for (int i = 0; i < data->size; i++)
	{
		for (int j = 0; j < data->size; j++)
		{
			printf("%d ", data->map[i].pieces[j].value);
		}
		printf("\n");
	}

	// for (int i = 0; i < (data->size * data->size); i++)
	// 	data->map_goal[i / data->size][i % data->size] = -1;

	// for (int i = 0; i < (data->size * data->size); i++)
	// {
	// 	if (data->map_start[i / data->size][i % data->size] == 0)
	// 	{
	// 		x = ((data->size * data->size) - 1) / data->size;
	// 		y = ((data->size * data->size) - 1) % data->size;
	// 	}
	// 	else
	// 	{
	// 		x = (data->map_start[i / data->size][i % data->size] - 1) / data->size;
	// 		y = (data->map_start[i / data->size][i % data->size] - 1) % data->size;
	// 	}
	// 	// printf(" %d ", data->map_start[i / data->size][i % data->size]);
	// 	// if (i % data->size == data->size - 1)
	// 	// 	printf("\n");
	// 	if (data->map_goal[x][y] != -1 || x < 0 || y < 0 || x >= data->size || y >= data->size)
	// 	{
	// 		printf("%d %d\n", data->map_start[i / data->size][i % data->size], data->map_goal[x][y]);
	// 		throw(MyException("Invalid map", ""));
	// 	}
	// 	data->map_goal[x][y] = data->map_start[i / data->size][i % data->size];
	// }

	// for (int i = 0; i < (data->size * data->size); i++)
	// {
	// 	printf("%d ", data->map_goal[i / data->size][i % data->size]);
	// 	if (i % data->size == data->size - 1)
	// 		printf("\n");
	// 	if (data->map_goal[i / data->size][i % data->size] == -1)
	// 		throw(MyException("Invalid map", ""));
	// }

	return (_SUCCESS);
}

/* check if map is solvable */
static int count_inversions(Data *data)
{
	int count = 0;

	for (int i = 0; i < (data->size * data->size); i++)
	{
		if (data->map_start[i / data->size][i % data->size])
		{
			for (int j = i + 1; j < (data->size * data->size); j++)
			{
				if (data->map_start[j / data->size][j % data->size] && data->map_start[i / data->size][i % data->size] > data->map_start[j / data->size][j % data->size]){
					count++;
					printf("[%d %d]\n", data->map_start[i / data->size][i % data->size], data->map_start[j / data->size][j % data->size]);
				}
			}
		}
	}
	return (count % 2);
}

int main(int ac, char **av)
{
	Data *data;

	try
	{
		data = new Data();
		if (ac <= 1)
			throw(MyException("No arguments", ""));
		parse_flags(av, ac, data);
		parse_file(data);
		validation_map(data);
		// printf("===>%d\n", count_inversions(data));
	}
	catch (MyException &e)
	{
		e.print_msg();
		delete data;
		return (_FAILURE);
	}
	delete data;
}
