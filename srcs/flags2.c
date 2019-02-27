/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 19:37:28 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/27 19:29:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		ft_putstr("ft_ls: ");
		perror(file->path);
		file->flags = add_flag(file->flags, 2);
		return (file);
	}
	request->size = buf.st_size;
	request->time_mod = buf.st_mtime;
	request->a_time = buf.st_atime;
	request->nlink = buf.st_nlink;
	request->uid = buf.st_uid;
	request->gid = buf.st_gid;
	request->mode = buf.st_mode;
	request->total = buf.st_blocks;
	return (file);
}

ushort	add_flag(ushort flags, char flag)
{
	if (flag == 'a')
		return (flags | 1);
	if (flag == 'l')
		return (flags | 2);
	if (flag == 'r')
		return (flags | 4);
	if (flag == 't')
		return (flags | 8);
	if (flag == 'R')
		return (flags | 16);
	if (flag == 'u')
		return (flags | 32);
	if (flag == 'f')
		return (flags | 64);
	if (flag == 'g')
		return (flags | 128);
	if (flag == 'd')
		return (flags | 256);
	if (flag == 'S')
		return (flags | 512);
	if (flag == 1)
		return (flags | 1024);
	if (flag == 2)
		return (flags | 2048);
	if (flag == '@')
		return (flags | 4096);
	if (flag == 'G')
	{
		ft_putstr("\033[32;1m");
		return (flags | 8192);
	}
	print_usage(flag);
	return (0);
}

ushort	is_flags(ushort flags, char flag)
{
	if (flag == 'a' && (flags & 1) == 1)
		return (1);
	if (flag == 'l' && (flags & 2) == 2)
		return (1);
	if (flag == 'r' && (flags & 4) == 4)
		return (1);
	if (flag == 't' && (flags & 8) == 8)
		return (1);
	if (flag == 'R' && (flags & 16) == 16)
		return (1);
	if (flag == 'u' && (flags & 32) == 32)
		return (1);
	if (flag == 'f' && (flags & 64) == 64)
		return (1);
	if (flag == 'g' && (flags & 128) == 128)
		return (1);
	if (flag == 'd' && (flags & 256) == 256)
		return (1);
	if (flag == 'S' && (flags & 512) == 512)
		return (1);
	if (flag == 1 && (flags & 1024) == 1024)
		return (1);
	if (flag == 2 && (flags & 2048) == 2048)
		return (1);
	if (flag == '@' && (flags & 4096) == 4096)
		return (1);
	if (flag == 'G' && (flags & 8192) == 8192)
		return (1);
	return (0);
}
