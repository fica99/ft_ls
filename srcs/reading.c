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

t_request	opening(int argc, char **argv)
{
	short int	i;
	short int	j;
	DIR			*dir;
	t_request	*request;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		j = 0;
		while (argv[i][++j])
			{
				if (argv[i][j] == 'a')
					request->a = 1; 
				if (argv[i][j] == 'l')
					request->l = 1; 
				if (argv[i][j] == 'r')
					request->r = 1; 
				if (argv[i][j] == 't')
					request->t = 1;
				if (argv[i][j] == 'R')
					request->r_big = 1;  
			}
		i++;
	}
	if (argc == 1 || argc - i == 0)
		check_open(dir = opendir("."));
	else if (argc - i == 1)
		check_open(dir = opendir(argv[--argc]));
	else
		request = open_few_d(argv);
	if (request == NULL)
	{
		d_names = reading(dir);
		check_close(closedir(dir));
		output(d_names, i);
	}
}

t_request	open_few_d(char **argv)
{
	short int	j;
	DIR			*dir;
	char		**d_names;
	char		*name;

	name = argv[0];
	argv = sort_names(argv);
	j = 0;
	while (argv[j])
	{
		while (argv[j][0] == '-' || ft_strcmp(argv[j], name) == 0)
			j++;
		ft_putstr(argv[j]);
		ft_putstr(":\n");
		check_open(dir = opendir(argv[j]));
		d_names = reading(dir);
		check_close(closedir(dir));
		output(d_names, 1);
		if (argv[++j])
			ft_putchar('\n');
	}
	exit(0);
}

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
