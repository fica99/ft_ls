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

void		check_open(DIR *dir)
{
	if (dir == NULL)
	{
		ft_putstr("ls: ");
		ft_putstr(strerror(errno));
		ft_putchar('\n');
		exit(-1);
	}
}

void		check_close(int nb)
{
	if (nb == -1)
	{
		ft_putstr("ls: ");
		ft_putstr(strerror(errno));
		ft_putchar('\n');
		exit(-1);
	}
}

short int	check_files(char **d_names)
{
	short int	i;

	i = 0;
	while (d_names[i])
		i++;
	return (i);
}

short int	check_name_len(char **d_names, short int j)
{
	short int	i;
	short int	sum;

	i = -1;
	sum = 0;
	while (++i < j)
		sum += ft_strlen(d_names[i]);
	return (sum);
}

short int	count_names(char **d_names)
{
	short int	j;


	j = 0;
	while (d_names[j])
		j++;
	return (j);
}