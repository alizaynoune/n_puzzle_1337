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
static int parse_flags(char **av)
{

	// for (int i = 0; i < ac; i++)
	// {
		if (!strcmp(av[0], "-ida"))
			g_flags |= _IDA;
		else if (!strcmp(av[0], "-greedy"))
			g_flags |= _G;
		else
		{
			fprintf(stderr, "usage: ./n_puzzle [-ida] [-greedy] [-e] [-m] [-h]\n");
			return (_ERROR);
		}

		if (!strcmp(av[1], "-e"))
			g_flags |= _E;
		else if (!strcmp(av[1], "-m"))
			g_flags |= _M;
		else if (!strcmp(av[1], "-mp"))
			g_flags |= _MP;
		else if(!strcmp(av[1], "-i"))
			g_flags |= _I;
		else
		{
			fprintf(stderr, "usage: ./n_puzzle [-ida] [-greedy] [-e] [-m] [-h]\n");
			return (_ERROR);
		}
	// }

	return (_SUCCESS);
}

static int help_inversions(int **map,int action, int start, int end, int x, int y, int i)
{
	int count = 0;
	int value = map[y][x];
	while (i < (g_size * g_size))
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

		if (map[y][x] && map[y][x] < value)
			count++;
		else if (map[y][x] == value)
			return (-1); // where duplicate value
		i++;
	}
	return (count);
}

/* check if map is solvable */
static int count_inversions(int **map)
{
	int count = 0;
	int action = _UP;
	int start = 0;
	int end = g_size - 1;
	int x = 0;
	int y = 0;
	int blank = 0;
	int inversions = 0;

	for (int i = 0; i < (g_size * g_size); i++)
	{
		if (map[y][x])
		{
			if ((inversions = help_inversions(map, action, start, end, x, y, i + 1)) == -1)
				return (-1);
			count += inversions;
		}
		else{
			blank++;
			if (blank > 1)
				return (-1);
		}
		// printf("%4d", map[y][x]);
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
	// printf("%d\n", count);
	return (count);
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

/* allocate memory for map */
static int **alloc_map(int size)
{
	int **map = NULL;

	SAFE(!(map = (int **)malloc(sizeof(int *) * size)), fprintf(stderr, "%s\n", strerror(errno)), NULL)
	memset(map, 0, sizeof(int *) * size);
	for (int i = 0; i < size; i++)
		SAFE(!(map[i] = (int *)malloc(sizeof(int) * size)), (ft_free_map(map, size), fprintf(stderr, "%s\n", strerror(errno))), NULL)
	return (map);
}

/* push line to map */
static int push_line_to_map(char *line, int i)
{
	int k = 0;
	int value = 0;

	for (int j = 0; line[j]; j++)
	{
		if ((j == 0 && isdigit(line[j])) || (!isdigit(line[j]) && isdigit(line[j + 1])))
		{
			value = atoi(&line[j]);
			SAFE((value < 0 || value >= (g_size * g_size)), fprintf(stderr, "Value is out of range %d\n", value), _ERROR)
			g_init_map[i][k++] = value;
		}
	}
	return (_SUCCESS);
}

/* parse file and fill data */
static int parse_file(FILE *fd)
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
		ret = getline(&line, &len, fd);
		/* search for comment */
		ptr = strchr(line, '#');
		/* delete comment from line */
		(ptr) ? *ptr = '\0' : 0;

		if (ret > 0 && line[0])
		{
			SAFE((count_nbr = is_digits(line)) <= 0, (free(line), fprintf(stderr, "Invalid line\n")), _ERROR)
			if (i == 0)
			{
				SAFE(count_nbr != 1 || atoi(line) < 3, (free(line), fprintf(stderr, "Invalid puzzle size\n")), _ERROR)
				g_size = atoi(line);
				SAFE(!(g_init_map = alloc_map(g_size)), free(line), _ERROR)
			}
			else
			{
				SAFE(count_nbr != g_size, (free(line), fprintf(stderr, "lenght of lines is not equal to puzzle size\n")), _ERROR)
				SAFE(count_line == g_size, (free(line), fprintf(stderr, "Too many lines\n")), _ERROR)
				SAFE(push_line_to_map(line, count_line) == _ERROR, free(line), _ERROR)
				count_line++;
			}
			i = 1;
		}
		free(line);
		line = NULL;
	}

	return (_SUCCESS);
}

void print_map(int **map)
{
	// printf("%d\n", g_size);
	for (int i = 0; i < (g_size * g_size); i++)
	{
		printf("%4d", map[i / g_size][i % g_size]);
		if ((i + 1) % g_size == 0)
			printf("\n");
	}
}

void					goal_position(int value, int *y, int *x)
{
	int count = 0;
	int action = _UP;
	int start = 0;
	int end = g_size - 1;
	int i = 0;

	// printf("<%d ", value);
	value = value == 0 ? g_size * g_size : value - 1;
	// value--;
	while (i < value)
	{
		if (action == _UP && *x < end)
			*x += 1;
		else if (action == _DOWN && *x > start)
			*x -= 1;
		else if (action == _RIGHT && *y < end)
			*y += 1;
		else if (action == _LEFT && *y > start)
			*y -= 1;
		if (action == _LEFT && *y == start)
		{
			action = _UP;
			start++;
			end--;
			*x = start;
			*y = start;
		}
		action == _UP && *x == end ? action = _RIGHT : 0;
		action == _DOWN && *x == start ? action = _LEFT : 0;
		action == _RIGHT && *y == end ? action = _DOWN : 0;
		i++;
	}
	// printf("%d %d>\n",*y, *x);
}



t_goalPosition		*init_goal_position(int **map, int *blank)
{
	t_goalPosition	*new_map = NULL;

	SAFE(!(new_map = (t_goalPosition *) malloc(sizeof(t_goalPosition) * g_size)), fprintf(stderr, "%s\n", strerror(errno)) , NULL)
	memset(new_map, 0, sizeof(t_goalPosition) * g_size);
	for (int i = 0; i < g_size; i++)
	{
		SAFE(!(new_map[i].pos = (t_position *) malloc(sizeof(t_position) * g_size)),(ft_free_position(new_map),fprintf(stderr, "%s\n", strerror(errno))) , NULL)
		memset(new_map[i].pos, 0, sizeof(t_position) * g_size);
		for(int j = 0; j < g_size; j++){
			goal_position((i * g_size) + j, &new_map[i].pos[j].y, &new_map[i].pos[j].x);
			if (!map[i][j])
			{
				blank[0] = i;
				blank[1] = j;
			}
			// printf("[%4d, %d, %d]", (i * g_size) + j, new_map[i].pos[j].y, new_map[i].pos[j].x);
		}
		// printf("\n");
	}
	return (new_map);
}

int main(int ac, char **av)
{
	FILE 	*fd = NULL;
	t_data	*data = NULL;
	int		inversion = 0;
	int		blank[2] = {0, 0};
	int		f_h = 0;

	SAFE((ac != 4 && ac != 2), fprintf(stderr, "Usage: ./n_puzzle [file] -[flags]\n"), _ERROR)
	SAFE(!(fd = fopen(av[1], "r")), fprintf(stderr, "%s %s\n", strerror(errno), av[1]), _ERROR)
	SAFE((ac == 4 && parse_flags(&av[2]) == _ERROR), fclose(fd), _ERROR)
	SAFE(parse_file(fd) == _ERROR, ft_free_map(g_init_map, g_size), _ERROR)
	fclose(fd);
	SAFE((inversion = count_inversions(g_init_map)) == -1, (ft_free_map(g_init_map, g_size), fprintf(stderr, "Duplicate value\n")), _ERROR)
	SAFE(inversion % 2, (ft_free_map(g_init_map, g_size), fprintf(stderr, "This puzzle is unsolvable\n")), _ERROR);
	SAFE(!(data = (t_data *) malloc(sizeof(t_data))), fprintf(stderr, "%s\n", strerror(errno)), _ERROR)
	memset(data, 0, sizeof(t_data));
	SAFE(!(data->position = init_goal_position(g_init_map, blank)), free(data), _ERROR)
	g_goal_map = data->position;
	f_h = (g_flags & _E) ? 1 : f_h;
	f_h = (g_flags & _I) ? 2:f_h;
	f_h = (g_flags & _MP) ? 3: f_h;
	printf("\n%d\n", f_h);
	if (solver(data, blank, f_h, (g_flags & _G) ? greedy_search : ida_star) == _ERROR)
	{
		ft_free_map(g_init_map, g_size);
		ft_free_position(data->position);
		// ft_free_map(data->up, g_size);
		// ft_free_map(data->down, g_size);
		// ft_free_map(data->left, g_size);
		// ft_free_map(data->right, g_size);
		ft_free_map(data->map, g_size);
		free(data);
		return(_ERROR);
	}
	printf("s%d, t%d\n", data->space_complexity, data->time_complexity);
	// print_map(g_init_map);

	// int x = 0;
	// int y = 0;
	// goal_position(0, &y, &x);
	// printf("%d, %d\n", y, x);
	// init_data();
	// printf("%d\n", ++g_size);
	// try
	// {
	// 	data = new Data();
	// 	if (ac <= 1)
	// 		throw(MyException("No arguments", ""));
	// 	parse_flags(av, ac, data);
	// 	parse_file(data);
	// 	fclose(data->fd);
	// 	data->fd = NULL;
	// 	validation_map(data);
	// 	if (count_inversions(data) == _FAILURE)
	// 		throw(MyException("This puzzle is unsolvable", ""));
	// 	data->print_map(data->map);
	// 	printf("\n");
	// 	greedy = new Greedy();
	// 	greedy->greedy_search(data);
	// 	delete(greedy);

	// }
	// catch (MyException &e)
	// {
	// 	e.print_msg();
	// 	delete data;
	// 	return (_FAILURE);
	// }
	// if (data)
	// 	delete data;
	ft_free_map(data->map, g_size);
	// ft_free_map(data->up, g_size);
	// ft_free_map(data->down, g_size);
	// ft_free_map(data->left, g_size);
	// ft_free_map(data->right, g_size);
	ft_free_position(data->position);
	free(data);
	
	return (_SUCCESS);
}
