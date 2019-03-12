/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cols.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:59:43 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/12 15:15:41 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_prt_cols	get_print_prm_c(t_dir *request, ushort ws_col)
{
	t_prt_cols	pprm;

	pprm.max = 0;
	pprm.cnt_elems = 0;

	while (request)
	{
		if (request->len > pprm.max)
			pprm.max = request->len;
		pprm.cnt_elems++;
		request = request->next;
	}
	pprm.cols = pprm.cnt_elems;
	pprm.rows = 1;
	if (pprm.max >= ws_col)
	{
		pprm.cols = 1;
		pprm.rows = pprm.cnt_elems;
		return (pprm);
	}
	while (((pprm.max + 1) * pprm.cnt_elems) / pprm.rows > ws_col)
		pprm.rows++;
	pprm.cols = (pprm.cnt_elems % pprm.rows == 0) ? pprm.cnt_elems / pprm.rows
			: (pprm.cnt_elems / pprm.rows) + 1;
	while (pprm.cols * (pprm.max + 1) > ws_col)
	{
		pprm.cols = (pprm.cnt_elems % (++pprm.rows) == 0)
		? pprm.cnt_elems / pprm.rows : (pprm.cnt_elems / pprm.rows) + 1;
	}
	return (pprm);
}

void		print_cols(t_dir *request, ushort ws_col, ushort flags, uint8_t j)
{
	t_prt_cols	pprm;
	int i;
	char buf[BUFFOUT];

	if (!request)
		exit(-1);
	flags = 0;
	i = 0;
	pprm = get_print_prm_c(request, ws_col);
	pprm.cur_row = 0;
	while (++pprm.cur_row <= pprm.rows)
	{
		print_line(request, pprm, buf, &i);
		request = request->next;
	}
	write(1, buf, i);
}

void		print_elem(char *str, uint8_t max)
{
	uint8_t	str_len;

	str_len = ft_strlen(str);
	ft_putstr(str);
	while (++str_len <= max)
		ft_putchar(' ');
}

void		print_line(t_dir *request, t_prt_cols pprm, char *buf, int *i)
{
	int j;

	pprm.cur_col = 0;
	while (++pprm.cur_col <= pprm.cols && request)
	{
		j = 0;
		while (request->name[j])
		{
			if (*i == BUFFOUT)
			{
				write(1, buf, *i);
				*i = 0;
			}
			buf[(*i)++] = request->name[j++];
		}
		while (j++ <= pprm.max && pprm.cur_col != pprm.cols)
		{
			if (*i == BUFFOUT)
			{
				write(1, buf, *i);
				*i = 0;
			}
			buf[(*i)++] = ' ';
		}
		request = next_elem(request, pprm);
	}
	if (*i == BUFFOUT)
	{
		write(1, buf, *i);
		*i = 0;
	}
	buf[(*i)++] = '\n';
}