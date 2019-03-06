/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:14:50 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/06 23:16:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*opening(int argc, char **argv)
{
	uint8_t	i;
	t_dir	*request;
	ushort	flags;

	i = 1;
	flags = read_flags(argv, &i);
	argv = check_dir(argc, argv, i);
	i--;
	request = make_list(argv, &i, flags);
	return (request);
}

t_dir	*make_list(char **arr, uint8_t *i, ushort flags)
{
	t_dir		*head;
	t_dir		*dir;
	t_dir		*file;
	mode_t		mode;

	dir = NULL;
	head = dir;
	while (arr[++(*i)])
	{
		dir = check_exist(dir, &head, flags);
		if (!(file = get_data(arr[(*i)])))
		{
			if (dir->pre)
			{
				dir = dir->pre;
				free_list(&(dir->next));
			}
			else
			{
				free_list(&dir);
				head = dir;
			}
			continue ;
		}
		else
			dir = file;
		dir->name = ft_strdup(arr[(*i)]);
//	if (!(is_flags(flags, 'd')))
//		dir ->f_names = reading(dir);
	}
	if (!head)
		exit(-1);
	return (sort_one_list(head, list_sort));
}

t_dir	*reading(t_dir *list)
{
	t_dir			*head;
	t_dir			*d;
	t_dir			*f;
	struct dirent	*file;
	DIR				*folder;

	if (get_type(list->mode) != 'd' || !(folder = check_open(list->path)))
		return (NULL);
	d = NULL;
	head = d;
	while ((file = readdir(folder)) != NULL)
	{
		d = check_exist(d, &(head), list->flags);
		d->mode = DTTOIF(file->d_type);
		d->name = ft_strdup(file->d_name);
		d->path = check_path(list->path, file->d_name);
		if (is_flags(list->flags, 't') || is_flags(list->flags, 'u')
		|| is_flags(list->flags, 'S') || is_flags(list->flags, 'g')
		|| is_flags(list->flags, 'l'))
		{
			if (!(f = get_data(d)))
			{
				if (d->pre)
				{
					d = d->pre;
					free_list(&(d->next));
				}
				else
				{
					free_list(&d);
					head = d;
				}
				continue ;
			}
			else
				d = f;
		}
	}
	check_close(closedir(folder));
	return (head);
}

t_dir	*get_data(char *path)
{
	t_dir		*request;
	struct stat	buf;

	if (!path || !(check_stat(path)))
		return (NULL);
	request->size = buf.st_size;
	request->time_mod = buf.st_mtime;
	request->a_time = buf.st_atime;
	request->nlink = buf.st_nlink;
	request->uid = buf.st_uid;
	request->gid = buf.st_gid;
	request->mode = buf.st_mode;
	request->total = buf.st_blocks;
	request->path = path;
	return (request);
}
