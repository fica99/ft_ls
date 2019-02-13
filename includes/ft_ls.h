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
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

typedef struct	s_dir
{
	char			*name;
	char			*path;
	struct s_dir	*f_names;
	struct s_dir	*next;
	short int		level;
	short int		total;
	struct s_flags	*flags;
	uint8_t			f_type; /* unsigned char */
	off_t			size; /* long int */
	uint8_t			err; /* errno (strerror)*/
	time_t			time_mod;
	time_t			a_time; /* int количество секунд, прошедших с 00:00:00 1 января 1970 года времени UTC. (при выводе используй time or ctime) */
	nlink_t			nlink; /*int*/
	mode_t			mode;
	char			*uid_name;
	char			*gid_name;
}				t_dir;

typedef struct	s_flags
{
	uint8_t	t;
	uint8_t	l;
	uint8_t	r_big;
	uint8_t	a;
	uint8_t	r;
	uint8_t	u;
	uint8_t	f;
	uint8_t	g;
	uint8_t	d;
	uint8_t	s_big;
}				t_flags;

typedef struct	s_prt
{
	int max;
	int cnt_elems;
	int cols;
	int rows;
	int cur_row;
	int cur_col;
}               t_prt;

t_dir			*opening(int argc, char **argv);
t_flags			*read_flags(char **argv, short int *i);
char			check_open(DIR *dir, t_dir **list);
void			check_close(int nb);
char			check_file_type(mode_t	st_mode);
t_dir			*make_list(char **arr, short int level);
t_dir			*reading(t_dir *list, short int level);
void			check_flag(t_flags *flags, char flag);
short int		double_arr_len(char **d_names);
t_dir			*sort_tree_list(t_dir *list, t_dir *(*sort)(t_dir *));
t_dir			*sort_one_list(t_dir *list);
t_dir			*swap_list(t_dir *cur, t_dir *next);
t_dir			*ft_list(void);
t_dir			*flag_r_big(t_dir *request);
t_dir			*flaging_r_big(t_dir *request);
t_dir			*find_flag(t_dir *request);
t_dir			*flaging_l(t_dir *request);
t_dir			*flag_l(t_dir *request);
t_dir			*reading_l(t_dir *request);
t_dir			*sort_list_rev(t_dir *list);
t_dir			*sort_list_time(t_dir *list);
t_dir			*sort_list_atime(t_dir *list);
t_dir			*sort_list_size(t_dir *list);
//print
void            print(t_dir *request);
void            print_cols(t_dir *request, int ws_col);
t_prt           get_print_prm(t_dir *request, int ws_col);
void            print_elem(char *str, t_prt pprm);
t_dir           *next_elem(t_dir *request, t_prt pprm);
void            print_line(t_dir  *request, t_prt pprm);
#endif
