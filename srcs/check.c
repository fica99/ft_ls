/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:00:44 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/27 22:50:15 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*check_open(char *path, u_int8_t f)
{
	DIR				*folder;
	
	if (!(folder = opendir(path)))
	{
		ft_putstr("ft_ls: ");
		perror(path);
		return (NULL);
	}
	if (!f)
	{
	 	check_close(closedir(folder));
		return (path);
	}
	return (folder);
}

void	check_close(int nb)
{
	if (nb == -1)
	{
		perror("ft_ls");
		exit(-1);
	}
}

mode_t	check_stat(char *path)
{
	struct stat	buf;
	mode_t	mode;
	
	mode = 0;
	if (lstat(path, &buf) == -1)
	{
			ft_putstr("ft_ls: ");
			perror(path);
	}
	else
		mode = buf.st_mode;
	return (mode);
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
	list->pre = NULL;
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
	(*next).pre = (*cur).pre;
	(*cur).next = (*next).next;
	(*next).next = cur;
	(*cur).pre = next;
	if ((*cur).next)
		(*((*cur).next)).pre = cur;
	return (next);
}
