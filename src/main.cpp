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

#include "n_puzzle.h"

int		main(int ac, char **av)
{
	Data *data;

	data = new Data();

	if (ac > 1)
	{
		if (parse_flags(av, ac, data) == ERROR)
			exit(EXIT_FAILURE);
	}

	printf("%d\n", data->flags);
	delete data;
}
