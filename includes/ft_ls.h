/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:00:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/01/22 13:00:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <sys/types.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

typedef struct	s_dir
{
	char			*name;
	char			**f_names;
	struct s_dir	*next;
}				t_dir;

typedef struct	s_request
{
	t_dir			*directories;
	unsigned char	t : 1;
	unsigned char	l : 1;
	unsigned char	r_big : 1;
	unsigned char	a : 1;
	unsigned char	r : 1;
}				t_request;

t_request		*opening(int argc, char **argv);
void			check_open(DIR *dir);
void			check_close(int nb);
t_dir			*open_few_d(char **argv);
char			**sort_names(char **d_names);
void			change_names(char **d_names, short int i);
short int		double_arr_len(char **d_names);
char			**reading(DIR *dir);
#endif
