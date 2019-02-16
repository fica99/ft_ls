/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:00:44 by aashara-          #+#    #+#             */
/*   Updated: 2019/01/22 13:00:45 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		check_open(DIR *dir, t_dir **list)
{
	if (dir == NULL && errno != ENOTDIR)
		(*list)->err = errno;
	else if (dir)
		return (1);
	return (0);
}

void		check_close(int nb)
{
	if (nb == -1)
	{
		perror("ls");
		exit(-1);
	}
}

t_dir		*ft_list(void)
{
	t_dir	*list;

	if (!(list = (t_dir*)malloc(sizeof(t_dir))))
		exit(-1);
	list->f_names = NULL;
	list->next = NULL;
	list->flags = NULL;
	list->err = 0;
	list->size = 0;
	list->gid = 0;
	list->uid = 0;
	list->level = 0;
	list->total = 0;
	list->time_mod = 0;
	list->a_time = 0;
	list->nlink = 0;
	list->name = NULL;
	list->path = NULL;
	list->mode = 0;
	list->files = 0;
	return (list);
}

uint8_t	double_arr_len(char **d_names)
{
	uint8_t	i;

	i = 0;
	while (d_names[i])
		i++;
	return (i);
}
