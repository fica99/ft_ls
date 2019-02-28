/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:02:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/28 17:23:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*check_path(char *path, char *name)
{
	char	*d;
	
	if (path[ft_strlen(path) - 1] == '/')
		d = ft_strjoin(path, name);
	else
		d = ft_strjoin(ft_strjoin(path, "/"), name);
	return (d);
}

char	**check_dir(int argc, char **argv, uint8_t i)
{
	if (argc - i == 0)
	{
		argv[double_arr_len(argv) + 1] = NULL;
		argv[double_arr_len(argv)] = ".";
	}
	return (argv);
}

void	print_usage(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putstr("\nusage: ft_ls [-@RSadfglrtu] [file ...]\n");
	exit(-1);
}

t_dir	*next_elem(t_dir *request, t_prt_cols pprm)
{
	ushort	i;

	i = 0;
	while (++i <= pprm.rows && request)
		request = (*request).next;
	return (request);
}
