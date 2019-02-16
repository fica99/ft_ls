/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 20:03:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/12 20:03:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir		*sort_list_atime(t_dir *list)
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
		if (list->a_time < (list->next)->a_time)
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

t_dir		*sort_list_size(t_dir *list)
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
		if (list->size < (list->next)->size)
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

t_dir		*sort_list_f_d(t_dir *list)
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
		if ((*list).f_names && !(*((*list).next)).f_names)
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