/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 00:26:58 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/10 00:26:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_flag(t_flags *flags, char flag)
{
	if (flag == 'a')
		(flags)->a = 1;
	else if (flag == 'l')
		(flags)->l = 1;
	else if (flag == 'r')
		(flags)->r = 1;
	else if (flag == 't')
		(flags)->t = 1;
	else if (flag == 'R')
		(flags)->r_big = 1;
	else if (flag == 'u')
		(flags)->u = 1;
	else if (flag == 'f')
		(flags)->f = 1;
	else if (flag == 'g')
		(flags)->g = 1;
	else if (flag == 'd')
		(flags)->d = 1;
	else if (flag == 'S')
		(flags)->s_big = 1;
	else
	{
		ft_putstr("ft_ls: invalid option -- '");
		ft_putchar(flag);
		ft_putstr("'\n");
		exit (-1);
	}
}

t_dir	*find_flag(t_dir *request)
{
	t_dir	*head;
	t_flags	*flags;

	head = request;
	flags = request->flags;
	if (flags->r_big)
		request->f_names = flaging_r_big(request->f_names, flags);
	if (flags->l)
		request->f_names = flaging_l(request->f_names);
	if (flags->r)
		request->f_names = sort_tree_list(request->f_names, sort_list_rev);
	if (flags->t || flags->u || flags->s_big || flags->g)
	{
		if (!(flags->l))
			request->f_names = flaging_l(request->f_names);
		if (flags->t)
			request->f_names = sort_tree_list(request->f_names, sort_list_time);
		if (flags->u)
			request->f_names = sort_tree_list(request->f_names, sort_list_atime);
		if (flags->s_big)
			request->f_names = sort_tree_list(request->f_names, sort_list_size);
	}
	return (head);
}

t_dir	*flaging_r_big(t_dir *request, t_flags *flags)
{
	t_dir	*dir;

	dir = request;
	while (request)
	{
		request->f_names = flag_r_big(request->f_names, flags);
		request = request->next;
	}
	return (dir);
}

t_dir	*flag_r_big(t_dir *request, t_flags *flags)
{
	t_dir	*head;

	head = request;
	while (request)
	{
		if ((ft_strcmp(request->name, ".") != 0) &&
			(ft_strcmp(request->name, "..") != 0))
		{
			request->f_names = reading(request, (request->level) + 1, flags);
			request->f_names = flag_r_big(request->f_names, flags);
		}
		request = request->next;
	}
	return (head);
}
