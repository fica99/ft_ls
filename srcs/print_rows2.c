/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rows2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:25:36 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/13 21:26:48 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

int		print_label_attr(t_dir *request, char *buf)
{
	ssize_t	size_list;
	acl_t	tmp;

	if (get_type(request->mode) != 'b' && get_type(request->mode) != 'c')
	{
		if (get_type(request->mode) == 'l')
			size_list = listxattr(request->path, NULL, 0, XATTR_NOFOLLOW);
		else
			size_list = listxattr(request->path, NULL, 0, 0);
		tmp = acl_get_link_np(request->path, ACL_TYPE_EXTENDED);
		if (size_list)
			buf[0] = '@';
		else if (tmp)
		{
			buf[0] = '+';
			acl_free(tmp);
		}
		else
			buf[0] = ' ';
	}
	else
		buf[0] = ' ';
	buf[1] = ' ';
	return (2);
}

int		print_number(long int num, long int max, char *buf, uint8_t j)
{
	long int	bit;
	int	i;

	i = 0;
	bit = get_bit(num);
	while (i + bit < max)
		buf[i++] = ' ';
	max = (j) ? max + 2 : max;
	putnum(num, i + bit - 1, buf);
	if (j)
		buf[i++ + bit] = ',';
	buf[i + bit] = ' ';
	return ((int)max + 1);
}

void	putnum(long int n, int i, char *buf)
{
	if (n >= 10)
		putnum(n / 10, i - 1, buf);
	buf[i] = n % 10 + '0';
}
