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
Data::Data(){
	flags		= 0;
	fd 			= 0;
	file 		= NULL;
	size 		= 0;
	map_start 	= NULL;
	map_goal 	= NULL;
}
/* Destructor */
Data::~Data(){

	ft_free(this);
}

/* add new flag */
void	Data::add_flag(int flag){
	this->flags |= flag;
}

/* Check if flag is set */
int		Data::flag_exists(int flag){
	return (flags & flag);
}

/* Set the file descriptor */
int		Data::open_file(char *name){
	if (!(this->fd = fopen(name, "r")))
		throw (MyException(strerror(errno), name));
	return (_SUCCESS);
}


/* Push a new line to the file */
void	Data::push_line(char *line){
	t_file *new_line;
	t_file *tmp;

	if (!(new_line = (t_file *)malloc(sizeof(t_file))))
		throw (MyException("malloc", ""));
	if (!(new_line->line = strdup(line))){
		free(new_line);
		throw (MyException("malloc", ""));
	}
	// new_line->line = line;
	new_line->next = NULL;
	if (!this->file)
		this->file = new_line;
	else{
		tmp = this->file;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_line;
	}
}

/* Read the file */
int		Data::read_file(void){
	size_t		len = 0;
	char	*line = NULL;
	int		ret = 1;

	while (ret > 0){
		ret = getline(&line, &len, fd);
		push_line(line);
		free(line);
		line = NULL;
	}
	return (_SUCCESS);
}


/* print the file for test */
void	Data::print_line(void){
	t_file *tmp;

	tmp = this->file;
	while (tmp){
		printf("%s", tmp->line);
		tmp = tmp->next;
	}
}




