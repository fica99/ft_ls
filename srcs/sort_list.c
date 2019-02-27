/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 00:21:48 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/27 23:38:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir		*sort_one_list(t_dir *list)
{
	t_dir	*head;

	if (!(*list).next)
		return (list);
	head = list;
	while (list && (*list).next)
	{
		if (ft_strcmp((*list).name, (*((*list).next)).name) > 0)
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

t_dir		*sort_list_rev(t_dir *list)
{
	t_dir	*head;

	if (!(*list).next)
		return (list);
	head = list;
	while (list && (*list).next)
	{
		if (ft_strcmp((*list).name, (*((*list).next)).name) < 0)
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

t_dir		*sort_list_time(t_dir *list)
{
	t_dir	*head;

	if (!(*list).next)
		return (list);
	head = list;
	while (list && (*list).next)
	{
		if (list->time_mod < (list->next)->time_mod)
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

t_dir		*sort_list_atime(t_dir *list)
{
	t_dir	*head;

	if (!(*list).next)
		return (list);
	head = list;
	while (list && (*list).next)
	{
		if (list->a_time < (list->next)->a_time)
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
