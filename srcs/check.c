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

char		check_file_type(mode_t st_mode)
{
	if (S_ISLNK(st_mode))
		return (DT_LNK);
	else if (S_ISREG(st_mode))
		return (DT_REG);
	else if (S_ISDIR(st_mode))
		return (DT_DIR);
	else if (S_ISCHR(st_mode))
		return (DT_CHR);
	else if (S_ISBLK(st_mode))
		return (DT_BLK);
	else if (S_ISFIFO(st_mode))
		return (DT_FIFO);
	else if (S_ISSOCK(st_mode))
		return (DT_SOCK);
	return (DT_UNKNOWN);
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
	list->gid_name = NULL;
	list->uid_name = NULL;
	list->level = 0;
	list->total = 0;
	list->time_mod = 0;
	list->a_time = 0;
	list->f_type = 0;
	return (list);
}

short int	double_arr_len(char **d_names)
{
	short int	i;

	i = 0;
	while (d_names[i])
		i++;
	return (i);
}
