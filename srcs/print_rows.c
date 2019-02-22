/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 23:06:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/16 23:10:53 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_rows(t_dir *request, ushort ws_cols, ushort flags)
{
	t_prt_rows	pprm;

	ws_cols = 0;
	pprm = get_print_prm_r(request);
	ft_putstr("total ");
	ft_putnbr(pprm.total);
	ft_putchar('\n');
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
		pprm.total += request->total;
		if ((bit = get_bit((*request).nlink)) > pprm.max_nlink)
			pprm.max_nlink = bit;
		if ((bit = get_bit((*request).size)) > pprm.max_size)
			pprm.max_size = bit;
		if ((len = ft_strlen((*getpwuid((*request).uid)).pw_name)) > pprm.max_uid)
			pprm.max_uid = len;
		if ((len = ft_strlen((*getgrgid((*request).gid)).gr_name)) > pprm.max_gid)
			pprm.max_gid = len;
		request = (*request).next;
	}
	return (pprm);
}

uint8_t		get_bit(int nlink)
{
	uint8_t	bit;

	bit = 1;
	if (!nlink)
		return (bit);
	while (nlink /= 10)
		bit++;
	return (bit);
}

void		print_line_rows(t_dir *request, ushort flags, t_prt_rows pprm)
{
	ft_putchar(get_type((*request).mode));
	print_mode_bits((*request).mode);
	print_label_attr(request, flags);
	print_number((long int)(*request).nlink, (long int)pprm.max_nlink);
	print_gu_ids(request, pprm, flags);
	print_number((long int)(*request).size, (long int)pprm.max_size);
	print_time((*request).time_mod);
	ft_putstr((*request).name);
	if (get_type((*request).mode) == 'l')
		print_link(request);
	ft_putchar('\n');
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
	char str[] = "rwxrwxrwx";

	cheak_usr(mode, str);
	cheak_grp(mode, str);
	cheak_oth(mode, str);
	ft_putstr(str);
}

void		cheak_usr(mode_t mode, char *str)
{
	if ((S_IRWXU & mode) != S_IRWXU)
	{
		if ((S_IRUSR & mode) != S_IRUSR)
			str[0] = '-';
		if ((S_IWUSR & mode) != S_IWUSR)
			str[1] = '-';
		if ((S_IXUSR & mode) != S_IXUSR)
			str[2] = '-';
	}
}

void		cheak_grp(mode_t mode, char *str)
{
	if ((S_IRWXG & mode) != S_IRWXG)
	{
		if ((S_IRGRP & mode) != S_IRGRP)
			str[3] = '-';
		if ((S_IWGRP & mode) != S_IWGRP)
			str[4] = '-';
		if ((S_IXGRP & mode) != S_IXGRP)
			str[5] = '-';
	}
}

void		cheak_oth(mode_t mode, char *str)
{
	if ((S_IRWXO & mode) != S_IRWXO)
	{
		if ((S_IROTH & mode) != S_IROTH)
			str[6] = '-';
		if ((S_IWOTH & mode) != S_IWOTH)
			str[7] = '-';
		if ((S_IXOTH & mode) != S_IXOTH)
			str[8] = '-';
	}
}

void		print_label_attr(t_dir *request, ushort flags)
{
	ssize_t	size_list;

	size_list = listxattr((*request).path + 2, NULL, 0, 0); // обработать ошибки
	if (is_flags(flags, '@') && size_list)
		ft_putstr("@ ");
	else
		ft_putstr("  ");
}

void		print_attr_full(t_dir *request, ushort flags)
{
	char		list[100];
	ssize_t		size_list;
	u_int8_t	i;
	u_int8_t	len;
	u_int8_t	size_val;
	char		value[50];

	size_list = listxattr((*request).path + 2, list, 100, 0); // обработать ошибки
	if (is_flags(flags, '@') && size_list)
	{
		i = -1;
		while (++i < size_list)
		{
			ft_putstr("\t");
			ft_putstr(list + i);
			len = ft_strlen(list);
			size_val = getxattr((*request).path + 2, list + i, value, 50, 0, 0);
			ft_putstr("\t  ");
			ft_putnbr((int)size_val);
			ft_putchar('\n');
			i += len;
		}
	}
}

void		print_number(long int num, long int max)
{
	long int	i;

	i = get_bit(num);
	while (i++ < max)
		ft_putchar(' ');
	ft_putnbr(num);
	ft_putchar(' ');
}

void		print_gu_ids(t_dir *request, t_prt_rows pprm, ushort flags)
{
	if (!is_flags(flags, 'g'))
	{
		print_elem((*getpwuid((*request).uid)).pw_name, pprm.max_uid);
		ft_putstr("  ");
	}
	print_elem((*getgrgid((*request).gid)).gr_name, pprm.max_gid);
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
	char buf[100];
	size_t size;

	size = readlink((*request).path + 2, buf, 100); //обработать ошибки
	buf[size] = '\0';
	ft_putstr(" -> ");
	ft_putstr(buf);
}
