/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:02:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/22 15:02:15 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*check_path(char *path, char *name, t_dir *d)
{
	if (path[ft_strlen(path) - 1] == '/')
		d->path = ft_strjoin(path, name);
	else
		d->path = ft_strjoin(ft_strjoin(path, "/"), name);
	return (d->path);
}

t_dir	*check_err(t_dir *err, t_dir **list, t_dir *elem)
{
	t_dir	*file;

	if (!err)
	{
		(*list)->f_names = elem->next;
		free(elem);
		file = (*list)->f_names;
	}
	else
	{
		err->next = elem->next;
		free(elem);
		file = err->next;
	}
	return (file);
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
	ft_putstr("\nusage: ft_ls [-RSadfglrtu] [file ...]\n");
	exit(-1);
}