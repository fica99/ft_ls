/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:14:50 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/09 19:56:26 by aashara-         ###   ########.fr       */
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
	return (make_list(argv, &i, flags));
}

t_dir	*make_list(char **arr, uint8_t *i, ushort flags)
{
	t_dir		*head;
	t_dir		*dir;
	t_dir		*head_files;

	dir = NULL;
	head = dir;
	head_files = NULL;
	while (arr[++(*i)])
	{
		dir = check_exist(dir, &head, flags);	
		dir->name = check_name(arr[*i]);
		dir->path = ft_strdup(arr[(*i)]);
		if (!(get_data(&dir)))
		{
			delete_from_list(&dir, &head);
			continue ;
		}
		if (get_type(dir->mode) != 'd' && !(is_flags(flags, 'd')))
			dir = make_file_list(dir, &head_files, &head);
	}
	if (head_files)
	{
		print(sorting(head_files, head_files->flags));
		if (head)
			ft_putchar('\n');
	}
	if (head)
		return (sorting(head, head->flags));
	return (NULL);
}

t_dir	*make_file_list(t_dir *dir, t_dir **head_files, t_dir **head)
{
	t_dir	*files;

	if (!(*head_files))
	{
		*head_files = dir;
		(*head_files)->pre = NULL;
	}
	else
	{
		files = *head_files;
		while (files->next)
			files = files->next;
		files->next = dir;
		files->next->pre = files;
	}
	return (make_dir_list(head, dir));
}

t_dir	*reading(t_dir *list)
{
	t_dir			*head;
	t_dir			*d;
	struct dirent	*file;
	DIR				*folder;

	if (get_type(list->mode) != 'd' || !(folder = check_open(list->path, list->name)))
		return (NULL);
	d = NULL;
	head = d;
	while ((file = readdir(folder)) != NULL)
	{
		if ((!(is_flags(list->flags, 'a')) && !(is_flags(list->flags, 'f'))) && (file->d_name)[0] == '.')
			continue ;
		d = check_exist(d, &(head), list->flags);
		d->mode = DTTOIF(file->d_type);
		d->name = ft_strdup(file->d_name);
		d->path = check_path(list->path, file->d_name);
		if (is_flags(list->flags, 't') || is_flags(list->flags, 'u')
		|| is_flags(list->flags, 'S') || is_flags(list->flags, 'g')
		|| is_flags(list->flags, 'l'))
		{
			if (!(get_data(&d)))
				delete_from_list(&d, &head);
		}
	}
	check_close(closedir(folder));
	return (head);
}

t_dir	*get_data(t_dir **request)
{
	struct stat	buf;

	if (!(*request))
		return (NULL);
	if (lstat((*request)->path, &buf) == -1)
	{
		ft_putstr("ft_ls: ");
		perror((*request)->name);
		return (NULL);
	}
	(*request)->size = buf.st_size;
	(*request)->time_mod = buf.st_mtime;
	(*request)->a_time = buf.st_atime;
	(*request)->nlink = buf.st_nlink;
	(*request)->uid = buf.st_uid;
	(*request)->gid = buf.st_gid;
	(*request)->mode = buf.st_mode;
	(*request)->total = buf.st_blocks;
	return (*request);
}
