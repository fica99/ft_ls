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
	short int		number_columns;
	struct winsize	w;

	number_names = count_names(d_names);
    ioctl(0, TIOCGWINSZ, &w);
	if (w.ws_col >= names_len(d_names, number_names) && j == 1)
		output_short(d_names);
	else if (w.ws_col < names_len(d_names, number_names) && j == 1)
	{
		number_columns = number_names;
		while (w.ws_col < names_len(d_names, number_columns))
			number_columns = number_columns / 2;
		output_l(d_names, number_names, number_columns, w);
	}
}

void	output_l(char **d_names, short int n_n, short int n_c, struct winsize w)
{
	short int	number_raws;
	short int	i;
	short int	k;
	short int	d;

	i = 0;
	number_raws = n_n / n_c;
	if (n_n % n_c != 0)
		number_raws++;
	while (d_names[i][0] == '.')
		i++;
	d = 0;
	k = 0;
	while (k <= number_raws)
	{
		while (d < n_n)
		{
			ft_putstr(d_names[d + i]);
			ft_putstr("  ");
			d += number_raws;
		}
		ft_putchar('\n');
		d = ++k;
	}
}

void	output_short(char **d_names)
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