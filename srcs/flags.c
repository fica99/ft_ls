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

ushort	read_flags(char **argv, uint8_t *i)
{
	ushort		flags;
	uint8_t		j;

	flags = 0;
	while (argv[*i] && argv[*i][0] == '-' && ft_strlen(argv[*i]) != 1)
	{
		j = 0;
		while (argv[*i][++j])
			flags = add_flag(flags, argv[*i][j]);
		(*i)++;
	}
	return (flags);
}

t_dir	*find_flag(t_dir *request)
{
	ushort	f;

	f = request->flags;
	if (is_flags(f, 'R'))
		request->f_names = flaging_r_big(request->f_names, f);
	if (is_flags(f, 'l'))
		request->f_names = flaging_l(request->f_names);
	if (is_flags(f, 'r'))
		request->f_names = sort_tree(request->f_names, sort_list_rev);
	if (is_flags(f, 't') || is_flags(f, 'u')
		|| is_flags(f, 'S') || is_flags(f, 'g'))
	{
		if (!(is_flags(f, 'l')))
			request->f_names = flaging_l(request->f_names);
		if (is_flags(f, 't'))
			request->f_names = sort_tree(request->f_names, sort_list_time);
		if (is_flags(f, 'u'))
			request->f_names = sort_tree(request->f_names, sort_list_atime);
		if (is_flags(f, 'S'))
			request->f_names = sort_tree(request->f_names, sort_list_size);
	}
	if ((!(is_flags(f, 't')) && !(is_flags(f, 'r')) && !(is_flags(f, 'u'))
		&& !(is_flags(f, 'f')) && !(is_flags(f, 'S'))))
		request->f_names = sort_tree(request->f_names, sort_one_list);
	return (request);
}

t_dir	*flaging_r_big(t_dir *request, ushort flags)
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

t_dir	*flag_r_big(t_dir *request, ushort flags)
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
			request->f_names = reading(request, flags);
			request->f_names = flag_r_big(request->f_names, flags);
		}
		request = request->next;
	}
	return (head);
}
