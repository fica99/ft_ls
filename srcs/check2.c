/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:02:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/01 15:38:47 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*check_path(char *path, char *name)
{
	char	*d;

	d = NULL;
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

t_dir	*check_exist(t_dir *dir, t_dir **head)
{
	if (dir)
	{
		dir->next = ft_list();
		(dir->next)->pre = dir;
		dir = dir->next;
	}
	else
	{
		dir = ft_list();
		*head = dir;
	}
	return (dir);
}
