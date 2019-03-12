/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rows3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:30:21 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/08 17:29:14 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

u_int16_t		print_gu_ids(t_dir *request, t_prt_rows pprm, ushort flags, char *buf)
{
	u_int16_t i;

	i = 0;
	if (!is_flags(flags, 'g'))
		i += putuid(getpwuid(request->uid)->pw_name, pprm.max_uid, buf + i);
	i += putgid(getgrgid(request->gid)->gr_name, pprm.max_gid, buf + i);
	return (i);
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
			ft_putnbr((int)size_val);
			ft_putchar('\n');
			i += ft_strlen(list + i);
		}
	}
}

u_int16_t putuid(char *uid, ushort max, char *buf)
{
	u_int16_t i;

	i = 0;
	while (uid[i])
	{
		buf[i] = uid[i];
		i++;
	}
	while (i++ < max + 2)
		buf[i++] = ' ';
	return (i);
}

u_int16_t putgid(char *gid, ushort max, char *buf)
{
	u_int16_t i;

	i = 0;
	while (gid[i])
	{
		buf[i] = gid[i];
		i++;
	}
	while (i++ < max + 2)
		buf[i++] = ' ';
	return (i);
}
