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
	short int		i;
	short int		k;
	short int		number_names;
	short int		number_columns;
	short int		number_raws;
	struct winsize	w;

	i = -1;
	number_names = count_names(d_names);
    ioctl(0, TIOCGWINSZ, &w);
	if (w.ws_col >= check_name_len(d_names, number_names) && j == 1)
	{
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
	else if (w.ws_col < check_name_len(d_names, number_names) && j == 1)
	{
		number_columns = number_names;		
		while (w.ws_col < check_name_len(d_names, number_columns))
			number_columns = number_columns / 2;
		number_raws =  number_names / number_columns;
		k = 0;
		//ft_putnbr(number_columns);
		while (++k < number_raws)
		{
			i = -1;
			while (++i < number_columns)
			{
				if (d_names[i * number_raws * k][0] != '.')
				{
					ft_putstr(d_names[i * number_raws * k]);
					ft_putstr("  ");
				}
			}
			ft_putchar('\n');
		}
	} 
}
