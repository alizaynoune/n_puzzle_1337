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

#include "n_puzzle.h"

/*
 * init Data Class
 */
Data::Data()
{
	flags	= 0;
	fd 		= 0;
	list	= NULL;
	map		= NULL;
}

/*
 * add new flag to var flags
 */
void	Data::add_flag(int flag)
{
	flags = flags | flag;
}

/*
 * chech fi flag exists
 */
int		Data::flag_exists(int flag)
{
	return (flags & flag);
}

/*
 * open file in var fd
 */
int		Data::open_file(char *name)
{
	if (!(fd = fopen(name, "r")))
		return (ERROR);
	return (SUCCESS);
}
