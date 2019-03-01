/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 22:02:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/01 20:32:45 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print(t_dir *request)
{
	struct winsize	size;
	t_dir			*dir;

	if (!request || ioctl(0, TIOCGWINSZ, (char*)&size) < 0)
		exit(-1);
	if (is_flags(request->flags, 'd'))
	{
		(is_flags(request->flags, 'l') || is_flags(request->flags, 'g')) ?
			print_rows(request, size.ws_col, request->flags) :
			print_cols(request, size.ws_col, request->flags);
		exit(0);
	}
	request = sort_one_list(request, list_f_d);
	dir = print_files(request, size.ws_col, request->flags);
	if (dir != request)
		request->flags = add_flag(request->flags, 1);
	print_all_rek(dir, size.ws_col, (is_flags(request->flags, 'l') ||
		is_flags(request->flags, 'g')) ? print_rows : print_cols, request->flags);
}

t_dir	*print_files(t_dir *request, ushort size, ushort flags)
{
	t_dir	*files;
	t_dir	*dir;

	if (!(request))
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
	(is_flags(flags, 'l') || is_flags(flags, 'g')) ?
	print_rows(files, size, 0) : print_cols(files, size, 0);
	return (dir);
}

void	print_all_rek(t_dir *request, ushort size,
		void (f)(t_dir *, ushort, ushort), ushort flags)
{
	while (request)
	{
		if (!(request->f_names) && is_flags(flags, 'R') &&
		get_type(request->mode) == 'd' && (ft_strcmp(request->name, ".") != 0)
		&& (ft_strcmp(request->name, "..") != 0))
			request->f_names = reading(request);
		if (request->f_names)
		{
			if (request->next || is_flags(flags, 1))
			{
				if (is_flags(flags, 1))
					ft_putchar('\n');
				ft_putstr(request->path);
				ft_putstr(":\n");
			}
			request->f_names = sorting(request->f_names, flags);
			f(request->f_names, size, flags);
			flags = add_flag(flags, 1);
			print_all_rek(request->f_names, size, f, flags);
		}
		request = free_list(&request);
	}
}

t_dir	*free_list(t_dir **request)
{
	t_dir	*next;
	
	if (!(*request))
		return (NULL);
	next = (*request)->next;
	ft_memdel((void**)&((*request)->name));
	ft_memdel((void**)&((*request)->path));
	(*request)->f_names = NULL;
	(*request)->next = NULL;
	(*request)->pre = NULL;
	free(*request);
	request = NULL;
	return (next);
}