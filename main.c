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
	DIR		*dir;
	char	**d_names;

	if (argc == 1)
		check_open(dir = opendir("."));
	else
		check_open(dir = opendir(argv[1]));
	d_names = reading(dir);
	output(d_names);
	check_close(closedir(dir));
	return (0);
}
