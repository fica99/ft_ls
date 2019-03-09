/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 19:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/09 19:57:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*check_name(char *name)
{
	char	*file;
	char	*file_name;

	if (!(file = ft_strrchr(name, '/')))
		file_name = ft_strdup(name);
	else
		file_name = ft_strdup(file + 1);
	return (file_name);
}