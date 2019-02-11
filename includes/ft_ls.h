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
	struct s_flags	*flags;
	uint8_t			f_type; /* unsigned char */
	off_t			size; /* long int */
	uint8_t			err; /* errno (используй perror)*/
	time_t			time; /* int количество секунд, прошедших с 00:00:00 1 января 1970 года времени UTC. (при выводе используй time or ctime) */
	nlink_t			nlink; /*int*/
	char			mode[9];
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
}				t_flags;

typedef struct	s_prt
{
	int max;
	int count;
	int elem;
	int elems;
	int cur_chr;
	int elem_in_line;
	int len;
}				t_prt;

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
void    		print(t_dir *request);
t_prt           get_print_prm(t_dir *request);
void            print_lvl(t_dir *request, int col_len);
void            print_elem(char *str, int elem_size);
int             print_end_elem(int elem_lost, int elems_brk);
#endif
