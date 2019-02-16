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

#include <ft_ls.h>

void	print_rows(t_dir *request, ushort ws_cols, t_flags *flags)
{
	t_prt_r	pprm;

	pprm = get_print_prm_r(request, ws_cols, flags);
	ft_putstr("total ");
	ft_putnbr((int)pprm.total / 1024);
	ft_putchar('\n');
	while (request)
	{
		print_line_rows(request, flags, ws_cols, pprm);
		request = request->next;
	}
}

t_prt_r	get_print_prm_r(t_dir *request, ushort ws_col, t_flags *flags)
{
	ushort		len;
	t_prt_r		pprm;
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

uint8_t	get_bit(int nlink)
{
	uint8_t	bit;

	bit = 1;
	if (!nlink)
		return (bit);
	while (nlink /= 10)
		bit++;
	return (bit);
}

void	print_line_rows(t_dir   *request, t_flags *flags, ushort ws_cols, t_prt_r pprm)
{
	print_type((*request).mode);
	print_mode_bits((*request).mode);
	print_number((long int)(*request).nlink, (long int)pprm.max_nlink);
	print_gu_ids(request, pprm, flags);
	print_number((long int)(*request).size, (long int)pprm.max_size);
	print_time((*request).a_time);
	ft_putstr((*request).name);
	ft_putchar('\n');
}

void	print_type(mode_t mode)
{
	if (S_ISLNK(mode))
		ft_putchar('l');
	else if (S_ISREG(mode))
		ft_putchar('-');
	else if (S_ISDIR(mode))
		ft_putchar('d');
	else if (S_ISCHR(mode))
		ft_putchar('c');
	else if (S_ISBLK(mode))
		ft_putchar('b');
	else if (S_ISFIFO(mode))
		ft_putchar('p');
	else if (S_ISSOCK(mode))
		ft_putchar('s');
	else
		ft_putchar('?');
}

void	print_mode_bits(mode_t mode)
{
	char str[] = "rwxrwxrwx";

	cheak_usr(mode, str);
	cheak_grp(mode, str);
	cheak_oth(mode, str);
	ft_putstr(str);
	ft_putstr("  ");
}

void	cheak_usr(mode_t mode, char *str)
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

void	cheak_grp(mode_t mode, char *str)
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

void	cheak_oth(mode_t mode, char *str)
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

void	print_number(long int num, long int max)
{
	long int	i;

	i = get_bit(num);
	while (i++ < max)
		ft_putchar(' ');
	ft_putnbr(num);
	ft_putchar(' ');
}

void	print_gu_ids(t_dir *request, t_prt_r pprm, t_flags *flags)
{
	if (!(*flags).g)
	{
		print_elem((*getpwuid((*request).uid)).pw_name, pprm.max_uid);
		ft_putstr("  ");
	}
	print_elem((*getgrgid((*request).gid)).gr_name, pprm.max_gid);
	ft_putstr("  ");
}

void	print_time(time_t time)
{
    char	*str_time;

	str_time = ctime(&time);
	str_time[16] = '\0';
	ft_putstr(str_time + 4);
	ft_putchar(' ');
}
