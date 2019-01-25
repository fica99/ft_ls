/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 14:42:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/01/22 14:42:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	output(char **d_names, short int j)
{
	short int		number_names;
	struct winsize	w;

	number_names = count_names(d_names);
    ioctl(0, TIOCGWINSZ, &w);
	if (w.ws_col >= check_name_len(d_names, number_names) && j == 1)
		output_small(d_names);
	else if (w.ws_col < check_name_len(d_names, number_names) && j == 1)
		output_long(d_names, number_names, w);
}

void	output_long(char **d_names, short int number_names, struct winsize w)
{
	short int	number_columns;
	short int	number_raws;
	short int	i;
	short int	k;
	short int	d;

	number_columns = number_names;
	i = 0;
	while (w.ws_col < check_name_len(d_names, number_columns))
		number_columns = number_columns / 2;
	number_raws = number_names / number_columns;
	if (number_names % number_columns != 0)
		number_raws++;
	while (d_names[i][0] == '.')
		i++;
	d = 0;
	k = 0;
	while (k <= number_raws)
	{
		while (d < number_names)
		{
			ft_putstr(d_names[d + i]);
			ft_putstr("  ");
			d = d + number_raws;
		}
		k++;
		ft_putchar('\n');
		d = 0;
		while (d < k)
			d++;
	}
}

void	output_small(char **d_names)
{
	short int	i;

	i = -1;
	while (d_names[++i])
		{
			if (d_names[i][0] != '.')
			{
				ft_putstr(d_names[i]);
				ft_putstr("  ");
			}
		}
		ft_putchar('\n');
}