/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rows3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:30:21 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/13 21:42:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_gu_ids(t_dir *request, t_prt_rows pprm, ushort flags)
{
	if (!is_flags(flags, 'g'))
	{
		print_elem(getpwuid(request->uid)->pw_name, pprm.max_uid);
		ft_putstr("  ");
	}
	print_elem(getgrgid(request->gid)->gr_name, pprm.max_gid);
	ft_putstr("  ");
}

void		print_time(time_t time)
{
	char	*str_time;

	str_time = ctime(&time);
	str_time[16] = '\0';
	ft_putstr(str_time + 4);
	ft_putchar(' ');
}

void		print_link(t_dir *request)
{
	char	buf[100];
	size_t	size;

	size = readlink((*request).path, buf, 100);
	buf[size] = '\0';
	ft_putstr(" -> ");
	ft_putstr(buf);
}

void		print_attr_full(t_dir *request, ushort flags)
{
	char		list[NAME_SATTR];
	ssize_t		size_list;
	ssize_t		i;
	u_int8_t	size_val;
	char		value[SIZE_VATTR];

	size_list = listxattr(request->path, list, NAME_SATTR, 0);
	if (is_flags(flags, '@') && size_list)
	{
		i = -1;
		while (++i < size_list)
		{
			ft_putchar('\t');
			ft_putstr(list + i);
			size_val = getxattr(request->path,
			list + i, value, SIZE_VATTR, 0, 0);
			ft_putstr("\t   ");
			print_number(size_val, 2, 0);
			ft_putchar('\n');
			i += ft_strlen(list + i);
		}
	}
}

void		get_data_max(t_prt_rows *pprm, t_dir *request)
{
	u_int8_t	bit;
	ushort		len;

	pprm->total += request->total;
	if ((bit = get_bit(request->nlink)) > pprm->max_nlink)
		pprm->max_nlink = bit;
	if (get_type(request->mode) == 'b' || get_type(request->mode) == 'c')
	{
		if ((bit = get_bit(major(request->st_rdev))) > pprm->max_major)
			pprm->max_major = bit;
		if ((bit = get_bit(minor(request->st_rdev))) > pprm->max_minor)
			pprm->max_minor = bit;
	}
	else
	{
		if ((bit = get_bit(request->size)) > pprm->max_size)
			pprm->max_size = bit;
	}
	if ((len = ft_strlen(getpwuid(request->uid)->pw_name)) > pprm->max_uid)
		pprm->max_uid = len;
	if ((len = ft_strlen(getgrgid(request->gid)->gr_name)) > pprm->max_gid)
		pprm->max_gid = len;
}
