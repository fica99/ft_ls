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
	argv = check_dir(argc, argv, i);
	request->f_names = make_list(argv, &i);
	if (!(is_flags(request->flags, 'd')))
		request = read_request(request);
	return (find_flag(request));
}

t_dir		*make_list(char **arr, uint8_t *i)
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
		dir->name = arr[*i];
		dir->path = arr[(*i)++];
		dir = reading_l(dir);
	}
	return (head);
}

t_dir		*reading(t_dir *list, ushort flags)
{
	t_dir			*head;
	t_dir			*d;
	struct dirent	*file;
	DIR				*folder;

	if ((get_type(list->mode) != 'd') ||
		!(check_open(folder = opendir(list->path), &list)) || !list)
			return (NULL);
	d = ft_list();
	head = d;
	while ((file = readdir(folder)) != NULL)
	{
		if (!(is_flags(flags, 'a')) && !(is_flags(flags, 'f'))
			&& (file->d_name)[0] == '.')
			continue ;
		if (d->name)
		{
			d->next = ft_list();
			d = d->next;
		}
		d->mode = DTTOIF(file->d_type);
		d->name = ft_strdup(file->d_name);
		d->path = check_path(list->path, file->d_name, d);
	}
	check_close(closedir(folder));
	return (head);
}

t_dir		*read_request(t_dir *list)
{
	t_dir	*file;
	t_dir	*err;

	file = list->f_names;
	err = NULL;
	while (file)
	{
		file->f_names = reading(file, list->flags);
		if (!is_flags(file->flags, 2))
		{
			err = file;
			file = file->next;
			continue;
		}
		file = check_err(err, &list, file);
	}
	return (list);
}
