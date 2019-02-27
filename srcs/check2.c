/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:02:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/27 21:43:44 by aashara-         ###   ########.fr       */
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

t_dir	*check_err(t_dir **list, t_dir *elem)
{
	t_dir	*file;

	if (!(elem->pre))
	{
		if ((*list)->f_names)
		{
			(*list)->f_names = elem->next;
			file = (*list)->f_names;
		}
		else
		{
			(*list)->next = elem->next;
			file = *list;
		}
		(elem->next)->pre = NULL;
	}
	else
	{
		(elem->pre)->next = elem->next;
		if (elem->next)
			(elem->next)->pre = elem->pre;		
		file = elem->pre;
	}
	ft_memdel((void**)&elem);
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
