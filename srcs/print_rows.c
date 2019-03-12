/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 23:06:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/09 19:21:39 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_rows(t_dir *request, ushort ws_cols, ushort flags)
{
	char buf[BUFFOUT];
	t_prt_rows	pprm;
	u_int16_t i;

	ws_cols = 0;
	i = 0;
	pprm = get_print_prm_r(request);
	ft_putstr("total ");
	ft_putnbr(pprm.total);
	ft_putchar('\n');
	while (request)
	{
		if (i + SIZELINE >= BUFFOUT)
		{
			write(1, buf, i);
			i = 0;
		}
		i += print_line_rows(request, flags, pprm, buf + i);
		request = request->next;
	}
	write(1, buf, i);
}

t_prt_rows	get_print_prm_r(t_dir *request)
{
	ushort		len;
	t_prt_rows	pprm;
	u_int8_t	bit;

	pprm.total = 0;
	pprm.max_nlink = 1;
	pprm.max_size = 1;
	pprm.max_uid = 0;
	pprm.max_gid = 0;
	while (request)
	{
		if (!(request->mode))
			exit(-1);
		pprm.total += request->total;
		if ((bit = get_bit(request->nlink)) > pprm.max_nlink)
			pprm.max_nlink = bit;
		if ((bit = get_bit(request->size)) > pprm.max_size)
			pprm.max_size = bit;
		if ((len = ft_strlen(getpwuid(request->uid)->pw_name)) > pprm.max_uid)
			pprm.max_uid = len;
		if ((len = ft_strlen(getgrgid(request->gid)->gr_name)) > pprm.max_gid)
			pprm.max_gid = len;
		request = request->next;
	}
	return (pprm);
}

u_int16_t		print_line_rows(t_dir *request, ushort flags, t_prt_rows pprm, char *buf)
{
	u_int16_t i;

	i = 0;
	buf[i++] = get_type(request->mode);
	i += print_mode_bits(request->mode, buf + i);
	i += print_label_attr(request, flags, buf + i);
	i += print_number((long int)request->nlink, (long int)pprm.max_nlink, buf + i);
	i += print_gu_ids(request, pprm, flags, buf + i);
	i += print_number((long int)request->size, (long int)pprm.max_size, buf + i);
	/*print_time(request->time_mod);
	ft_putstr(request->name);
	if (get_type(request->mode) == 'l')
		print_link(request);
	ft_putchar('\n');
	if (get_type(request->mode) != 'l')
		print_attr_full(request, flags);*/
	buf[i++] = '\n';
	return (i);
}

char		get_type(mode_t mode)
{
	if (S_ISLNK(mode))
		return ('l');
	else if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('?');
}

u_int16_t		print_mode_bits(mode_t mode, char *buf)
{
	u_int16_t	i;

	i = 0;
	while (i < 8)
	{
		buf[i++] = 'r';
		buf[i++] = 'w';
		buf[i++] = 'x';
	}
	cheak_usr(mode, buf);
	cheak_grp(mode, buf);
	cheak_oth(mode, buf);
	return (9);
}
