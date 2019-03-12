/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 23:06:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/12 14:11:50 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_rows(t_dir *request, ushort ws_cols, ushort flags, uint8_t i)
{
	t_prt_rows	pprm;

	ws_cols = 0;
	pprm = get_print_prm_r(request);
	if (i)
	{
		ft_putstr("total ");
		ft_putnbr(pprm.total);
		ft_putchar('\n');
	}
	while (request)
	{
		print_line_rows(request, flags, pprm);
		request = request->next;
	}
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

void		print_line_rows(t_dir *request, ushort flags, t_prt_rows pprm)
{
	ft_putchar(get_type(request->mode));
	print_mode_bits(request->mode);
	print_label_attr(request, flags);
	print_number((long int)request->nlink, (long int)pprm.max_nlink);
	print_gu_ids(request, pprm, flags);
	print_number((long int)request->size, (long int)pprm.max_size);
	print_time(request->time_mod);
	ft_putstr(request->name);
	if (get_type(request->mode) == 'l')
		print_link(request);
	ft_putchar('\n');
	if (get_type(request->mode) != 'l')
		print_attr_full(request, flags);
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

void		print_mode_bits(mode_t mode)
{
	char	str[10];
	uint8_t	i;

	i = 0;
	while (i < 8)
	{
		str[i++] = 'r';
		str[i++] = 'w';
		str[i++] = 'x';
	}
	str[9] = '\0';
	cheak_usr(mode, str);
	cheak_grp(mode, str);
	cheak_oth(mode, str);
	ft_putstr(str);
}
