/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:14:50 by aashara-          #+#    #+#             */
/*   Updated: 2019/01/22 13:14:51 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir		*opening(int argc, char **argv)
{
	uint8_t	i;
	t_dir	*request;
	t_dir	*list;

	i = 1;
	request = ft_list();
	request->flags = read_flags(argv, &i);
	if (argc - i == 0)
	{
		argv[double_arr_len(argv) + 1] = NULL;
		argv[double_arr_len(argv)] = ".";
	}
	request->f_names = make_list(argv, 1, &i);
	list = request->f_names;
	while (list)
	{
		if ((request->flags)->d)
			break ;
		list->f_names = reading(list, 2, request->flags);
		list = list->next;
	}
	return (find_flag(request));
}

t_dir		*make_list(char **arr, uint8_t level, uint8_t *i)
{
	t_dir		*head;
	t_dir		*dir;

	dir = ft_list();
	head = dir;
	while (arr[(*i)])
	{
		if (arr[(*i) - 1][0] != '-' && ((*i) - 1) != 0)
		{
			dir->next = ft_list();
			dir = dir->next;
		}
		dir->level = level;
		dir->name = arr[*i];
		dir->path = ft_strjoin("./", arr[(*i)++]);
	}
	return (head);
}

t_dir		*reading(t_dir *list, short int level, t_flags *flags)
{
	t_dir			*head;
	t_dir			*d;
	struct dirent	*file;
	DIR				*folder;

	if (!(check_open(folder = opendir(list->path), list->path + 2)))
		return (NULL);
	d = ft_list();
	head = d;
	while ((file = readdir(folder)) != NULL)
	{
		if (!(flags->a) && !(flags->f) && (file->d_name)[0] == '.')
			continue ;
		if (d->name)
		{
			d->next = ft_list();
			d = d->next;
		}
		d->name = ft_strdup(file->d_name);
		d->path = ft_strjoin(ft_strjoin(list->path, "/"), d->name);
		d->level = level;
	}
	check_close(closedir(folder));
	return (head);
}
