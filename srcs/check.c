/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:00:44 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/01 15:25:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*check_open(char *path, u_int8_t f)
{
	DIR	*folder;

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
	mode_t		mode;

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
