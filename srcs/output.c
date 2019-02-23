/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 22:02:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/15 22:02:48 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print(t_dir *request)
{
	struct winsize	size;
	ushort			flags;
	t_dir			*dir;

	if (!request || ioctl(0, TIOCGWINSZ, (char*)&size) < 0)
		exit(-1);
	flags = (*request).flags;
	request = request->f_names;
	if (is_flags(flags, 'd'))
	{
		if (is_flags(flags, 'l') || is_flags(flags, 'g'))
			print_rows(request, 85, flags);
		else
			print_cols(request, 85, flags);
		exit(0);
	}
	request = sort_list_f_d(request);
	dir = print_files(request, size.ws_col, flags);
	if (dir != request)
		flags = add_flag(flags, 1);
	print_all_rek(dir, size.ws_col, (is_flags(flags, 'l') ||
		is_flags(flags, 'g')) ? print_rows : print_cols, flags);
}

t_dir	*print_files(t_dir *request, ushort size, ushort flags)
{
	t_dir	*files;
	t_dir	*dir;

	if (!request)
		return (NULL);
	files = request;
	dir = request;
	while (request)
	{
		if (!request->f_names && request->next && (request->next)->f_names)
		{
			dir = request->next;
			request->next = NULL;
		}
		request = request->next;
	}
	if (files == dir)
	{
		if (!(dir->f_names))
			dir = NULL;
		else
			return (dir);
	}
	(is_flags(flags, 'l') || is_flags(flags, 'g')) ? print_rows(files, size, 0) : print_cols(files, size, 0);
	return (dir);
}

void	print_all_rek(t_dir *request, ushort size,
		void (f)(t_dir *, ushort, ushort), ushort flags)
{
	while (request)
	{
		if (request->f_names)
		{
			if (request->next || is_flags(flags, 1))
			{
				if (is_flags(flags, 1))
					ft_putchar('\n');
				ft_putstr(request->path + 2);
				ft_putstr(":\n");
			}
			f(request->f_names, size, flags);
			flags = add_flag(flags, 1);
			print_all_rek(request->f_names, size, f, flags);
		}
		request = request->next;
	}
}

t_dir	*next_elem(t_dir *request, t_prt_cols pprm)
{
	ushort	i;

	i = 0;
	while (++i <= pprm.rows && request)
		request = (*request).next;
	return (request);
}
