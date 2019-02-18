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
	uint8_t			level;
	short int		total;
	struct s_flags	*flags;
	off_t			size;
	time_t			time_mod;
	time_t			a_time;
	nlink_t			nlink;
	mode_t			mode;
	uid_t			uid;
	gid_t			gid;
	uint8_t			files;
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
t_flags			*read_flags(char **argv, uint8_t *i);
char			check_open(DIR *dir, char *name);
void			check_close(int nb);
t_dir			*make_list(char **arr, uint8_t level, uint8_t *i);
t_dir			*reading(t_dir *list, short int level, t_flags *flags);
void			check_flag(t_flags *flags, char flag);
uint8_t			double_arr_len(char **d_names);
t_dir			*sort_tree(t_dir *list, t_dir *(*sort)(t_dir *));
t_dir			*sort_one_list(t_dir *list);
t_dir			*swap_list(t_dir *cur, t_dir *next);
t_dir			*ft_list(void);
t_dir			*flag_r_big(t_dir *request, t_flags *flags);
t_dir			*flaging_r_big(t_dir *request, t_flags *flags);
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
void			print_cols(t_dir *request, ushort ws_col, t_flags *flags);
t_prt			get_print_prm(t_dir *request, ushort ws_col);
void			print_elem(char *str, uint8_t max);
t_dir			*next_elem(t_dir *request, t_prt pprm);
void			print_line(t_dir  *request, t_prt pprm);
void			print_all_rek(t_dir *request, ushort size, void (f)(t_dir *, ushort, t_flags *), t_flags *flags);
t_dir			*print_files(t_dir *request, ushort size);
t_dir			*sort_list_point(t_dir *list);
t_dir			*print_files(t_dir *request, ushort ws_col);
void			print_rows(t_dir *request, ushort ws_cols, t_flags *flags);
t_prt_r			get_print_prm_r(t_dir *request, ushort ws_col, t_flags *flags);
uint8_t			get_bit(int nlink);
void			print_line_rows(t_dir *request, t_flags *flags, ushort ws_cols, t_prt_r pprm);
void			print_type(mode_t mode);
void			print_mode_bits(mode_t mode);
void			cheak_usr(mode_t mode, char *str);
void			cheak_grp(mode_t mode, char *str);
void			cheak_oth(mode_t mode, char *str);
void			print_number(long int num, long int max);
void			print_gu_ids(t_dir *request, t_prt_r pprm, t_flags *flags);
void			print_time(time_t time);
t_flags			*flags_init(void);
void			print_usage(char c);
#endif
