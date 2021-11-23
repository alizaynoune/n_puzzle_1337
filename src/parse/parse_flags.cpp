/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:38:21 by alzaynou          #+#    #+#             */
/*   Updated: 2021/11/23 19:21:54 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

int		parse_flags(char **flags, int av, Data *data)
{
	if (data->open_file(flags[1]) == ERROR)
		return (ERROR);
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
			return (ERROR);
		printf("%d>>\n", data->flags);

	}

	return (SUCCESS);
}
