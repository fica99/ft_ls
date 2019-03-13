/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 19:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/13 15:23:46 by aashara-         ###   ########.fr       */
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

void	check_err(char *name, char *path)
{
	if (errno == EACCES)
	{
		ft_putstr(path);
		ft_putstr(":\nft_ls: ");
		perror(name);
	}
	else
	{
		ft_putstr("ft_ls: ");
		perror(path);
	}
}

void	data_init(struct dirent *file, t_dir *list, t_dir **d, t_dir **head)
{
	(*d)->mode = DTTOIF(file->d_type);
	(*d)->name = ft_strdup(file->d_name);
	(*d)->path = check_path(list->path, file->d_name);
	(*d)->len = file->d_namlen;
	(*d)->level = (list->level) + 1;
	if (is_flags(list->flags, 't') || is_flags(list->flags, 'u')
		|| is_flags(list->flags, 'S') || is_flags(list->flags, 'g')
		|| is_flags(list->flags, 'l'))
		if (!(get_data(d)))
			delete_from_list(d, head);
}
