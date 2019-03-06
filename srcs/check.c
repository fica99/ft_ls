/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:00:44 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/06 21:40:07 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

DIR		*check_open(char *path)
{
	DIR	*folder;

	if (!(folder = opendir(path)))
	{
		ft_putstr("ft_ls: ");
		perror(path);
		return (NULL);
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

uint8_t	check_stat(char *path)
{
	struct stat	buf;

	if (lstat(path, &buf) == -1)
	{
		ft_putstr("ft_ls: ");
		perror(path);
		return (0);
	}
	return (1);
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
