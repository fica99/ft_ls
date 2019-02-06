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
	t_dir		*request;
	char		*name;

	i = 1;
	request = (t_dir*)malloc(sizeof(t_dir));
	request->level = 0;
	request->flags = read_flags(argv, &i);
	if (argc - i == 0)
	{
		argv[double_arr_len(argv) + 1] = NULL;
		argv[double_arr_len(argv)] = ".";
	}
	name = argv[0];
	request->f_names = make_list((argv = sort_names(argv)), 1, name);
	return (request);
}

t_flags	*read_flags(char **argv, short int *i)
{
	t_flags		*flags;
	short int	j;

	flags = (t_flags*)malloc(sizeof(t_flags));
	while (argv[*i] && argv[*i][0] == '-')
	{
		j = 0;
		while (argv[*i][++j])
			{
				if (argv[*i][j] == 'a')
					flags->a = 1;
				else if (argv[*i][j] == 'l')
					flags->l = 1; 
				else if (argv[*i][j] == 'r')
					flags->r = 1; 
				else if (argv[*i][j] == 't')
					flags->t = 1;
				else if (argv[*i][j] == 'R')
					flags->r_big = 1;  
			}
		(*i)++;
	}
	return (flags);
}

t_dir	*make_list(char **arr, short int level, char *name)
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
		if (arr[i][0] != '-' && ft_strcmp(arr[i], name) != 0)
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
				dir->f_names = make_list(reading(folder), ++level, name);
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
			if (j == 0)
				free(d_names);
		}
		d_names = arr;
	}
	d_names[i] = NULL;
	return (sort_names(d_names));
}