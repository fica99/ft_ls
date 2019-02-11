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

	if (!(request->next))
		return (request);
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
	if (request->level == 1)
		request->f_type = check_file_type(buf.st_mode);
	request->size = buf.st_size;
	request->time = buf.st_mtime;
	request->nlink = buf.st_nlink;
	
	//ft_putnbr(buf.st_mode);
	ft_putchar('\n');
	return (file);
}
