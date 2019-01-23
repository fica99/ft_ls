/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:00:30 by aashara-          #+#    #+#             */
/*   Updated: 2019/01/22 13:00:32 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	DIR			*dir;
	char		**d_names;
	short int	i;

	i = 1;
	while (argv[i] && (argv[i][0] == '-'))
		i++;
	if (argc == 1 || i == argc)
		check_open(dir = opendir("."));
	else
		check_open(dir = opendir(argv[i]));
	d_names = reading(dir);
	output(d_names);
	check_close(closedir(dir));
	return (0);
}
