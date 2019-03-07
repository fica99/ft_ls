/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 22:02:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/07 19:20:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print(t_dir *request)
{
	struct winsize	size;

	if (!request || ioctl(0, TIOCGWINSZ, (char*)&size) < 0)
		exit(-1);
	if (is_flags(request->flags, 'd'))
	{
		(is_flags(request->flags, 'l') || is_flags(request->flags, 'g')) ?
			print_rows(request, size.ws_col, request->flags) :
			print_cols(request, size.ws_col, request->flags);
	}
	print_all_rek(request, size.ws_col, (is_flags(request->flags, 'l') ||
		is_flags(request->flags, 'g')) ? print_rows : print_cols, request->flags);
}

void	print_all_rek(t_dir *request, ushort size,
		void (f)(t_dir *, ushort, ushort), ushort flags)
{
	while (request)
	{
		if (!(request->f_names) && is_flags(flags, 'R') &&
		get_type(request->mode) == 'd' && (ft_strcmp(request->name, ".") != 0)
		&& (ft_strcmp(request->name, "..") != 0))
			//request->f_names = reading(request);
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
		free_list(&request);
	}
}

void	free_list(t_dir **request)
{	
	ft_memdel((void**)&((*request)->name));
	ft_memdel((void**)&((*request)->path));
	(*request)->f_names = NULL;
	(*request)->next = NULL;
	(*request)->pre = NULL;
	free(*request);
	*request = NULL;
}