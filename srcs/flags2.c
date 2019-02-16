/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 19:37:28 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/10 19:37:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*flaging_l(t_dir *request)
{
	t_dir	*dir;

	dir = request;
	while (request)
	{
		if (request->f_names)
			if (!(request->f_names = flaging_l(request->f_names)))
				return (NULL);
		request = request->next;
	}
	return (flag_l(dir));
}

t_dir	*flag_l(t_dir *request)
{
	t_dir	*head;

	head = request;
	while (request)
	{
		request = reading_l(request);
		request = request->next;
	}
	return (head);
}

t_dir	*reading_l(t_dir *request)
{
	t_dir		*file;
	struct stat	buf;

	file = request;
	if (lstat(request->path, &buf) == -1)
	{
		request->err = errno;
		return (file);
	}
	request->size = buf.st_size;
	request->time_mod = buf.st_mtime;
	request->a_time = buf.st_atime;
	request->nlink = buf.st_nlink;
	request->uid = buf.st_uid;
	request->gid = buf.st_gid;
	request->mode = buf.st_mode;
	request->total = buf.st_blksize;
	return (file);
}
