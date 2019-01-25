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

void		check_open(DIR *dir);
void		check_close(int nb);
char		**reading(DIR *dir);
void		output(char **d_names, short int j);
char		**sort_names(char	**d_names);
short int	check_files(char **d_names);
void		change_names(char **d_names, short int i);
void		opening(int argc, char **argv);
void		open_few_d(char **argv);
short int   check_name_len(char **d_names, short int j);
short int	count_names(char **d_names);
void		output_long(char **d_names, short int number_names, struct winsize w);
void		output_small(char **d_names);
#endif
