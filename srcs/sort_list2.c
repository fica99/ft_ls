/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 20:03:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/27 23:38:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir		*sort_list_size(t_dir *list)
{
	t_dir	*head;

	if (!(*list).next)
		return (list);
	head = list;
	while (list && (*list).next)
	{
		if (list->size < (list->next)->size)
		{
			list = swap_list(list, (*list).next);
			if ((*list).pre)
			{
				(list->pre)->next = list;
				list = (*list).pre;
			}
			else
				head = list;
			continue ;
		}
		list = (*list).next;
	}
	return (head);
}

t_dir		*sort_list_f_d(t_dir *list)
{
	t_dir	*head;

	if (!(*list).next)
		return (list);
	head = list;
	while (list && (*list).next)
	{
		if ((*list).f_names && !(*((*list).next)).f_names)
		{
			list = swap_list(list, (*list).next);
			if ((*list).pre)
			{
				(list->pre)->next = list;
				list = (*list).pre;
			}
			else
				head = list;
			continue ;
		}
		list = (*list).next;
	}
	return (head);
}
