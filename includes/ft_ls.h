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
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>

void		check_open(DIR *dir);
void		check_close(int nb);
char		**reading(DIR *dir);
void		output(char **d_names);
char		**sort_names(char	**d_names);
short int	check_files(char **d_names);
void		change_names(char **d_names, short int i);
void		opening(int argc, char **argv);
#endif
