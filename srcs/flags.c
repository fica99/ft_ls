/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 00:26:58 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/28 17:14:26 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

ushort	read_flags(char **argv, uint8_t *i)
{
	ushort		flags;
	uint8_t		j;

	flags = 0;
	while (argv[*i] && argv[*i][0] == '-' && ft_strlen(argv[*i]) != 1)
	{
		j = 0;
		while (argv[*i][++j])
			flags = add_flag(flags, argv[*i][j]);
		(*i)++;
	}
	return (flags);
}
