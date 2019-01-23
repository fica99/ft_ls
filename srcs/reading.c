/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:14:50 by aashara-          #+#    #+#             */
/*   Updated: 2019/01/22 13:14:51 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**reading(DIR *dir)
{
	char			**d_names;
	char			**arr;
	short int		i;
	short int		j;
	struct dirent	*file;

	i = 0;
	while ((file = readdir(dir)) != NULL)
	{
		arr = (char **)malloc(sizeof(char *) * (i + 2));
		arr[i] = ft_strdup(file->d_name);
		j = i++;
		while (--j >= 0)
		{
			arr[j] = ft_strdup(d_names[j]);
			ft_memdel((void **)&d_names[j]);
		}
		d_names = arr;
	}
	d_names[i] = NULL;
	return (sort_names(d_names));
}

void	change_names(char **d_names, short int i)
{
	char	*arr;

	arr = d_names[i];
	d_names[i] = d_names[i + 1];
	d_names[i + 1] = arr;
}

char	**sort_names(char **d_names)
{
	short int	i;
	short int	j;

	i = 0;
	j = check_files(d_names);
	while (i < j - 1)
	{
		if (ft_strcmp(d_names[i], d_names[i + 1]) > 0)
		{
			change_names(d_names, i);
			i = -1;
		}
		i++;
	}
	return (d_names);
}
