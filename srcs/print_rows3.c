/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rows3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:30:21 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/13 21:54:53 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_gu_ids(t_dir *request, t_prt_rows pprm, ushort flags, char *buf)
{
	int i;

	i = 0;
	if (!is_flags(flags, 'g'))
		i += putuid(getpwuid(request->uid)->pw_name, pprm.max_uid, buf + i);
	i += putgid(getgrgid(request->gid)->gr_name, pprm.max_gid, buf + i);
	return (i);
}

int		print_time(time_t time, time_t cur_time, char *buf)
{
	char	*str_time;
	int i;
	int j;

	i = 0;
	str_time = ctime(&time);
	j = 4;

	while (j < 11)
		buf[i++] = str_time[j++];
	if (difftime(cur_time, time) > (double)(86400 * 182))
	{
		buf[i++] = ' ';
		j = 20;
		while (j < 24)
			buf[i++] = str_time[j++];
	}
	else
	{
		while (j < 16)
			buf[i++] = str_time[j++];
	}
	buf[i++] = ' ';
	return (i);
}

int		print_link(t_dir *request, char *buf)
{
	char	buf_l[100];
	char	row[] = " -> ";
	size_t	size;
	int i;
	int j;

	i = 0;
	j = 0;
	size = readlink((*request).path, buf_l, 100);
	buf_l[size] = '\0';
	while (row[j])
		buf[i++] = row[j++];
	j = 0;
	while (buf_l[j])
		buf[i++] = buf_l[j++];
	return (i);
}

/*void		print_attr_full(t_dir *request, ushort flags)
{
	char		list[NAME_SATTR];
	ssize_t		size_list;
	ssize_t		i;
	u_int8_t	size_val;
	char		value[SIZE_VATTR];

	if (get_type(request->mode) == 'l')
		size_list = listxattr(request->path, list, NAME_SATTR, XATTR_NOFOLLOW);
	else
		size_list = listxattr(request->path, list, NAME_SATTR, 0);
	if (is_flags(flags, '@') && size_list)
	{
		i = -1;
		while (++i < size_list)
		{
			ft_putchar('\t');
			ft_putstr(list + i);
			if (get_type(request->mode) == 'l')
				size_val = getxattr(request->path,
				list + i, value, SIZE_VATTR, 0, XATTR_NOFOLLOW);
			else
				size_val = getxattr(request->path,
				list + i, value, SIZE_VATTR, 0, 0);
			ft_putstr("\t   ");
			print_number(size_val, 3, 0);
			ft_putchar('\n');
			i += ft_strlen(list + i);
		}
	}
}*/

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

int putuid(char *uid, ushort max, char *buf)
{
	int i;

	i = 0;
	while (uid[i])
	{
		buf[i] = uid[i];
		i++;
	}
	while (i < max + 2)
		buf[i++] = ' ';
	return (i);
}

int putgid(char *gid, ushort max, char *buf)
{
	int i;

	i = 0;
	while (gid[i])
	{
		buf[i] = gid[i];
		i++;
	}
	while (i < max + 2)
		buf[i++] = ' ';
	return (i);
}
