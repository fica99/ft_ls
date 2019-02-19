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
		perror("ft_ls: ");
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

t_flags	*flags_init(void)
{
	t_flags	*flags;

	if (!(flags = (t_flags*)malloc(sizeof(t_flags))))
	{
		perror("ft_ls");
		exit(-1);
	}
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
	return (flags);
}

void	print_usage(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putstr("\nusage: ft_ls [-RSadfglrtu] [file ...]\n");
	exit(-1);
}
