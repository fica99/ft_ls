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
short int   names_len(char **d_names, short int start, short int end);
short int	count_names(char **d_names);
void		output_l(char **d_names, short int n_n, struct winsize w);
void		output_short(char **d_names);
short int   longest_word(char  **d_names, short int n_n, short int n_r, short int n_c);
#endif
