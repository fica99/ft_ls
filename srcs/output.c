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
	if (w.ws_col >= names_len(d_names, 0, number_names) && j == 1)
		output_short(d_names);
	else if (w.ws_col < names_len(d_names, 0, number_names) && j == 1)
		output_l(d_names, number_names, w);
}

void	output_l(char **d_names, short int n_n, struct winsize w)
{
	short int	number_raws;
	short int	number_columns;
	short int	len;
	short int	len_word;
	short int	j;
	short int	k;
	short int	d;
	short int	end;
	short int	start;

	number_columns = n_n;
	while (**d_names == '.')
		*d_names++;
	while (w.ws_col < names_len(d_names, 0, number_columns))
		number_columns--;
	start = 0;
	end = number_columns;
	number_raws = 1;
	while (end < n_n)
	{
		start += number_columns;
		end += number_columns;
		number_raws++;
		if (end > n_n)
			end = n_n;
		if (w.ws_col < names_len(d_names, start, end))
		{
			start = 0;
			end = --number_columns;
			number_raws = 1;
		}
	}
	while (number_raws * number_columns > n_n)
		number_columns--;
	if (number_columns * number_raws != n_n)
		number_columns++;
	d = 0;
	k = 0;
	while (k < number_raws)
	{
		j = 0;
		while (d < n_n)
		{
			len = longest_word(d_names, n_n, number_raws, j);
			len_word = ft_strlen(d_names[d]);
			ft_putstr(d_names[d]);
			while (len + 2 > len_word)
			{
				if (len_word == len && d + number_raws >= n_n)
					break;
				ft_putchar(' ');
				len_word++;
			}
			d += number_raws;
			j++;
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