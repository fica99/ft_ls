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
		printf("ls: %s\n", strerror(errno));
		exit(-1);
	}
}

void		check_close(int nb)
{
	if (nb == -1)
	{
		printf("ls: %s\n", strerror(errno));
		exit(-1);
	}
}