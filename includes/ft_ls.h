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
	struct s_dir	*f_names;
	struct s_dir	*next;
	short int		level;
	struct s_flags	*flags;
}				t_dir;

typedef struct	s_flags
{
	unsigned char	t : 1;
	unsigned char	l : 1;
	unsigned char	r_big : 1;
	unsigned char	a : 1;
	unsigned char	r : 1;
}				t_flags;

t_dir		*opening(int argc, char **argv);
t_flags		*read_flags(char **argv, short int *i);
void		check_open(DIR *dir);
void		check_close(int nb);
char		**sort_names(char **d_names);
void		change_names(char **d_names, short int i);
short int	double_arr_len(char **d_names);
t_dir		*make_list(char **arr, short int level, char *name);
char		**reading(DIR *dir);
#endif
