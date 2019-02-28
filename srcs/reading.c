/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:14:50 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/28 17:16:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir		*opening(int argc, char **argv)
{
	uint8_t	i;
	t_dir	*request;

	i = 1;
	request = ft_list();
	request->flags = read_flags(argv, &i);
	argv = check_dir(argc, argv, i);
	request->f_names = make_list(argv, &i);
	if (!(is_flags(request->flags, 'd')))
		request = read_request(request);
	return (request);
}

t_dir		*make_list(char **arr, uint8_t *i)
{
	t_dir		*head;
	t_dir		*dir;
	mode_t		mode;

	dir = NULL;
	head = dir;
	(*i)--;
	while (arr[++(*i)])
	{
		if (!(mode = check_stat(arr[*i])))
			continue;
		if (get_type(mode) == 'd' && !check_open(arr[*i], 0))
			continue ;
		if (dir)
		{
			dir->next = ft_list();
			(dir->next)->pre = dir;
			dir = dir->next;
		}
		else
		{
			dir = ft_list();
			head = dir;
		}
		dir->mode = mode;
		dir->name = arr[(*i)];
		dir->path = arr[(*i)];
	}
	return (sort_one_list(head, list_sort));
}

t_dir		*reading(t_dir *list, ushort flags)
{
	t_dir			*head;
	t_dir			*d;
	struct dirent	*file;
	DIR				*folder;

	if ((get_type(list->mode) != 'd') ||
		!(folder = (DIR *)check_open(list->path, 1)) || !list)
		return (NULL);
	d = NULL;
	head = d;
	while ((file = readdir(folder)) != NULL)
	{
		if (!(check_stat(check_path(list->path, file->d_name))))
			continue;
		if (!(is_flags(flags, 'a')) && !(is_flags(flags, 'f'))
			&& (file->d_name)[0] == '.')
			continue ;
		if (d && d->name)
		{
			d->next = ft_list();
			(d->next)->pre = d;
			d = d->next;
		}
		else
		{
			d = ft_list();
			head = d;
		}
		d->mode = DTTOIF(file->d_type);
		d->name = ft_strdup(file->d_name);
		d->path = check_path(list->path, file->d_name);
		if (is_flags(flags, 't') || is_flags(flags, 'u')
		|| is_flags(flags, 'S') || is_flags(flags, 'g') || is_flags(flags, 'l'))
			d = get_data(d);
	}
	check_close(closedir(folder));
	return (head);
}

t_dir		*read_request(t_dir *list)
{
	t_dir	*file;

	file = list->f_names;
	while (file)
	{
		file->f_names = reading(file, list->flags);
		file = file->next;
	}
	return (list);
}
