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

t_dir	*opening(int argc, char **argv)
{
	short int	i;
	DIR			*dir;
	t_dir		*request;

	i = 1;
	request = read_flags(argv, &i);
	if (argc - i == 0)
	{
		argv[double_arr_len(argv) + 1] = NULL;
		argv[double_arr_len(argv)] = ".";
	}
	request->f_names = make_list((argv = sort_names(argv)), 1);
	return (request);
}

t_dir	*read_flags(char **argv, short int *i)
{
	t_dir		*request;
	short int	j;

	request = (t_dir*)malloc(sizeof(t_dir));
	while (argv[*i] && argv[*i][0] == '-')
	{
		j = 0;
		while (argv[*i][++j])
			{
				if (argv[*i][j] == 'a')
					request->a = 1;
				else if (argv[*i][j] == 'l')
					request->l = 1; 
				else if (argv[*i][j] == 'r')
					request->r = 1; 
				else if (argv[*i][j] == 't')
					request->t = 1;
				else if (argv[*i][j] == 'R')
					request->r_big = 1;  
			}
		(*i)++;
	}
	request->level = 0;
	return (request);
}

t_dir	*make_list(char **arr, short int level)
{
	t_dir		*head;
	t_dir		*dir;
	DIR			*folder;
	short int	i;

	dir = (t_dir*)malloc(sizeof(t_dir));
	head = dir;
	i = -1;
	while (arr[++i])
	{
		if (arr[i][0] != '-' && ft_strcmp(arr[i], "./ls") != 0)
		{
			if (i != 0)
			{
				dir->next = (t_dir*)malloc(sizeof(t_dir));
				dir = dir->next;
			}
			dir->level = level;
			dir->name = arr[i];
			if (level == 1)
			{
				check_open(folder = opendir(arr[i]));
				dir->f_names = make_list(reading(folder), ++level);
				check_close(closedir(folder));
			}
			dir->next = NULL;
		}
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