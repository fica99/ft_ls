/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:00:44 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/26 17:56:12 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	check_open(DIR *dir, t_dir **list)
{
	if (dir == NULL)
	{
		ft_putstr("ft_ls: ");
		perror((*list)->path);
		(*list)->flags = add_flag((*list)->flags, 2);
		return (0);
	}
	return (1);
}

void	check_close(int nb)
{
	if (nb == -1)
	{
		perror("ft_ls");
		exit(-1);
	}
}

t_dir	*ft_list(void)
{
	t_dir	*list;

	if (!(list = (t_dir*)malloc(sizeof(t_dir))))
	{
		perror("ft_ls");
		exit(-1);
	}
	list->f_names = NULL;
	list->next = NULL;
	list->flags = 0;
	list->size = 0;
	list->gid = 0;
	list->uid = 0;
	list->total = 0;
	list->time_mod = 0;
	list->a_time = 0;
	list->nlink = 0;
	list->name = NULL;
	list->path = NULL;
	list->mode = 0;
	return (list);
}

uint8_t	double_arr_len(char **d_names)
{
	uint8_t	i;

	i = 0;
	if (!(d_names))
		return (i);
	while (d_names[i])
		i++;
	return (i);
}

t_dir	*swap_list(t_dir *cur, t_dir *next)
{
	(*cur).next = (*next).next;
	(*next).next = cur;
	return (next);
}
