/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:00:30 by aashara-          #+#    #+#             */
/*   Updated: 2019/01/22 13:00:32 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_dir	*request;
	t_dir	*dir;
	
	request = opening(argc, argv);
	request = request->f_names;
	while (request)
	{
		ft_putstr(request->name);
		ft_putchar('\n');
		dir = request->f_names;
		while (dir)
		{
			ft_putstr(dir->name);
			dir = dir->next;
		}
		ft_putstr("\n\n");
		request = request->next;
	}
	return (0);
}
