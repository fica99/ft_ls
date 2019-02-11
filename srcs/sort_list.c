/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 00:21:48 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/10 00:21:50 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir		*sort_tree_list(t_dir *list, t_dir *(*sort)(t_dir *))
{
	t_dir	*head;

	if (!list)
		exit(-1);
	head = list;
	while (list)
	{
		if ((*list).f_names)
			if (!((*list).f_names = sort_tree_list((*list).f_names, sort)))
				return (NULL);
		list = (*list).next;
	}
	return (sort(head));
}

t_dir		*sort_one_list(t_dir *list)
{
	t_dir	*head;
	t_dir	*pre;

	if (!list)
		exit(-1);
	if (!(*list).next)
		return (list);
	head = list;
	while (list && (*list).next)
	{
		if (ft_strcmp((*list).name, (*((*list).next)).name) > 0)
		{
			if (list == head)
				head = swap_list(list, (*list).next);
			else
				(*pre).next = swap_list(list, (*list).next);
			list = head;
			continue ;
		}
		pre = list;
		list = list->next;
	}
	return (head);
}

t_dir		*swap_list(t_dir *cur, t_dir *next)
{
	(*cur).next = (*next).next;
	(*next).next = cur;
	return (next);
}
