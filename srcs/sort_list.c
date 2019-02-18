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

t_dir		*sort_tree(t_dir *list, t_dir *(*sort)(t_dir *))
{
	t_dir	*head;

	if (!list)
		return (NULL);
	head = list;
	while (list)
	{
		if ((*list).f_names)
			if (!((*list).f_names = sort_tree((*list).f_names, sort)))
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
		return (NULL);
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

t_dir		*sort_list_rev(t_dir *list)
{
	t_dir	*head;
	t_dir	*pre;

	if (!list)
		return (NULL);
	if (!(*list).next)
		return (list);
	head = list;
	while (list && (*list).next)
	{
		if (ft_strcmp((*list).name, (*((*list).next)).name) < 0)
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

t_dir		*sort_list_time(t_dir *list)
{
	t_dir	*head;
	t_dir	*pre;

	if (!list)
		return (NULL);
	if (!(*list).next)
		return (list);
	head = list;
	while (list && (*list).next)
	{
		if (list->time_mod < (list->next)->time_mod)
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

t_dir		*sort_list_atime(t_dir *list)
{
	t_dir	*head;
	t_dir	*pre;

	if (!list)
		return (NULL);
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
