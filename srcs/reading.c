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
	short int	i;
	t_dir		*request;
	t_dir		*list;

	i = 1;
	request = ft_list();
	request->flags = read_flags(argv, &i);
	if (argc - i == 0)
	{
		argv[double_arr_len(argv) + 1] = NULL;
		argv[double_arr_len(argv)] = ".";
	}
	request->f_names = make_list(argv, 1);
	list = request->f_names;
	while (list)
	{
		if (request->flags && (request->flags)->d)
			break ;
		list->f_names = reading(list, 2);
		list = list->next;
	}
	if (request->flags && ((!(request->flags)->a) || (!(request->flags)->f) ||
	(!(request->flags)->g) || (!(request->flags)->d)))
		request = find_flag(request);
	return (request);
}

t_flags		*read_flags(char **argv, short int *i)
{
	t_flags		*flags;
	short int	j;

	if (!(flags = (t_flags*)malloc(sizeof(t_flags))))
		exit(-1);
	flags->d = 0;
	flags->a = 0;
	flags->f = 0;
	flags->g = 0;
	flags->l = 0;
	flags->r = 0;
	flags->r_big = 0;
	flags->u = 0;
	flags->t = 0;
	flags->s_big = 0;
	while (argv[*i] && argv[*i][0] == '-')
	{
		j = 0;
		while (argv[*i][++j])
			check_flag(flags, argv[*i][j]);
		(*i)++;
	}
	if ((*i) == 1)
		ft_memdel((void**)&flags);
	return (flags);
}

t_dir		*make_list(char **arr, short int level)
{
	t_dir		*head;
	t_dir		*dir;
	short int	i;

	dir = ft_list();
	head = dir;
	i = 0;
	while (arr[++i])
	{
		if (arr[i][0] != '-')
		{
			if (i != 1 && arr[i - 1][0] != '-')
			{
				dir->next = ft_list();
				dir = dir->next;
			}
			dir->level = level;
			dir->name = arr[i];
			dir->path = ft_strjoin("./", arr[i]);
		}
	}
	return (head);
}

t_dir		*reading(t_dir *list, short int level)
{
	t_dir			*head;
	t_dir			*d;
	struct dirent	*file;
	DIR				*folder;
	short int		i;

	if (!(check_open(folder = opendir(list->path), &list)))
		return (NULL);
	d = ft_list();
	head = d;
	i = -1;
	while ((file = readdir(folder)) != NULL)
	{
		if (++i != 0)
		{
			d->next = ft_list();
			d = d->next;
		}
		d->name = ft_strdup(file->d_name);
		d->path = ft_strjoin(ft_strjoin(list->path, "/"), d->name);
		d->level = level;
		d->f_type = file->d_type;
	}
	check_close(closedir(folder));
	return (head);
}
