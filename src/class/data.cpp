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
	map			= NULL;
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




