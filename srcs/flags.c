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

t_flags	*read_flags(char **argv, uint8_t *i)
{
	t_flags		*flags;
	uint8_t		j;

	flags = flags_init();
	while (argv[*i] && argv[*i][0] == '-' && ft_strlen(argv[*i]) != 1)
	{
		j = 0;
		while (argv[*i][++j])
			check_flag(flags, argv[*i][j]);
		(*i)++;
	}
	return (flags);
}

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
		print_usage(flag);
}

t_dir	*find_flag(t_dir *request)
{
	t_dir	*head;
	t_flags	*f;

	head = request;
	f = request->flags;
	if (f->r_big)
		request->f_names = flaging_r_big(request->f_names, f);
	if (f->l)
		request->f_names = flaging_l(request->f_names);
	if (f->r)
		request->f_names = sort_tree(request->f_names, sort_list_rev);
	if (f->t || f->u || f->s_big || f->g)
	{
		if (!(f->l))
			request->f_names = flaging_l(request->f_names);
		if (f->t)
			request->f_names = sort_tree(request->f_names, sort_list_time);
		if (f->u)
			request->f_names = sort_tree(request->f_names, sort_list_atime);
		if (f->s_big)
			request->f_names = sort_tree(request->f_names, sort_list_size);
	}
	if ((!(f->t) && !(f->r) && !(f->u) && !(f->f) && !(f->s_big)))
		request->f_names = sort_tree(request->f_names, sort_one_list);
	return (head);
}

t_dir	*flaging_r_big(t_dir *request, t_flags *flags)
{
	t_dir	*dir;

	if (!request)
		return (NULL);
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

	if (!request)
		return (NULL);
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
