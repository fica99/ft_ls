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

t_request	*opening(int argc, char **argv)
{
	short int	i;
	short int	j;
	DIR			*dir;
	t_request	*request;

	i = 1;
	request = (t_request*)malloc(sizeof(request));
	while (argv[i] && argv[i][0] == '-')
	{
		j = 0;
		while (argv[i][++j])
			{
				if (argv[i][j] == 'a')
					request->a = 1;
				else if (argv[i][j] == 'l')
					request->l = 1; 
				else if (argv[i][j] == 'r')
					request->r = 1; 
				else if (argv[i][j] == 't')
					request->t = 1;
				else if (argv[i][j] == 'R')
					request->r_big = 1;  
			}
		i++;
	}
	if (argc == 1 || argc - i == 0)
	{
		argv[double_arr_len(argv) + 1] = NULL;
		argv[double_arr_len(argv)] = ".";
	}
	request->directories = open_few_d(argv);
	return (request);
}

t_dir		*open_few_d(char **argv)
{
	short int	j;
	t_dir		*dir;
	t_dir		*head;
	DIR			*folder;
	char		*name;
	short int	i;

	name = argv[0];
	argv = sort_names(argv);
	j = -1;
	dir = (t_dir*)malloc(sizeof(t_dir));
	head = dir;
	while (argv[++j])
	{
		if (j != 0)
		{
			dir->next = (t_dir*)malloc(sizeof(t_dir));
			dir = dir->next;
		}
		while (argv[j] && (argv[j][0] == '-' || ft_strcmp(argv[j], name) == 0))
			j++;
		if (j >= double_arr_len(argv))
		{
			free(dir);
			dir = NULL;
			break;
		}
		dir->name = argv[j];
		check_open(folder = opendir(argv[j]));
		dir->f_names = reading(folder);
		check_close(closedir(folder));
		dir->next = NULL;
	}	
	while (head)
	{
		ft_putstr(head->name);
		i = -1;
		while (++i < double_arr_len(head->f_names))
			ft_putstr(head->f_names[i]);
	
		head = head->next;
	}
	return (head);
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