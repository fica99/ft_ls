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

void    check_open(DIR *dir)
{
    if (dir == NULL)
    {
        ft_putstr("ls: ");
        ft_putstr(strerror(errno));
        ft_putchar('\n');
        exit(-1);
    }
}

void    check_close(int nb)
{
    if (nb == -1)
    {
        ft_putstr("ls: ");
        ft_putstr(strerror(errno));
        ft_putchar('\n');
        exit(-1);
    }
}