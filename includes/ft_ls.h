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
# include <time.h>

typedef struct	s_dir
{
	char			*name;
	char			*path;
	struct s_dir	*f_names;
	struct s_dir	*next;
	short int		total;
	ushort			flags;
	off_t			size;
	time_t			time_mod;
	time_t			a_time;
	nlink_t			nlink;
	mode_t			mode;
	uid_t			uid;
	gid_t			gid;
	uint8_t			is_print;
}				t_dir;

typedef struct	s_prt
{
	uint8_t	max;
	ushort	cnt_elems;
	ushort	cols;
	ushort	rows;
	ushort	cur_row;
	ushort	cur_col;
}				t_prt;

typedef struct	s_prt_r
{
	ushort		total;
	u_int8_t	max_nlink;
	u_int8_t	max_size;
	ushort		max_uid;
	ushort		max_gid;
}				t_prt_r;

t_dir			*opening(int argc, char **argv);
ushort			read_flags(char **argv, uint8_t *i);
char			check_open(DIR *dir, char *name);
void			check_close(int nb);
t_dir			*make_list(char **arr, uint8_t *i);
t_dir			*reading(t_dir *list, ushort flags);
uint8_t			double_arr_len(char **d_names);
t_dir			*sort_tree(t_dir *list, t_dir *(*sort)(t_dir *));
t_dir			*sort_one_list(t_dir *list);
t_dir			*swap_list(t_dir *cur, t_dir *next);
t_dir			*ft_list(void);
t_dir			*flag_r_big(t_dir *request, ushort flags);
t_dir			*flaging_r_big(t_dir *request, ushort flags);
t_dir			*find_flag(t_dir *request);
t_dir			*flaging_l(t_dir *request);
t_dir			*flag_l(t_dir *request);
t_dir			*reading_l(t_dir *request);
t_dir			*sort_list_rev(t_dir *list);
t_dir			*sort_list_time(t_dir *list);
t_dir			*sort_list_atime(t_dir *list);
t_dir			*sort_list_size(t_dir *list);
t_dir			*sort_list_f_d(t_dir *list);
void			print(t_dir *request);
void			print_cols(t_dir *request, ushort ws_col, ushort flags);
t_prt			get_print_prm(t_dir *request, ushort ws_col);
void			print_elem(char *str, uint8_t max);
t_dir			*next_elem(t_dir *request, t_prt pprm);
void			print_line(t_dir  *request, t_prt pprm);
void			print_all_rek(t_dir *request, ushort size, void (f)(t_dir *, ushort, ushort), ushort flags);
t_dir			*print_files(t_dir *request, ushort size);
t_dir			*print_files(t_dir *request, ushort ws_col);
void			print_rows(t_dir *request, ushort ws_cols, ushort flags);
t_prt_r			get_print_prm_r(t_dir *request, ushort ws_col);
uint8_t			get_bit(int nlink);
void			print_line_rows(t_dir *request, ushort flags, ushort ws_cols, t_prt_r pprm);
void			print_type(mode_t mode);
void			print_mode_bits(mode_t mode);
void			cheak_usr(mode_t mode, char *str);
void			cheak_grp(mode_t mode, char *str);
void			cheak_oth(mode_t mode, char *str);
void			print_number(long int num, long int max);
void			print_gu_ids(t_dir *request, t_prt_r pprm, ushort flags);
void			print_time(time_t time);
void			print_usage(char c);
//flags
ushort 			add_flag(ushort flags, char flag);
ushort 			is_flags(ushort flags, char flag);
#endif
