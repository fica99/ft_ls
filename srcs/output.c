/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 22:02:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/02/15 22:02:48 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void                print(t_dir *request)
{
    struct winsize  size;
	t_flags			*flags;

    if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
        printf("TIOCGWINSZ error");
	flags = (*request).flags;
	request = request->f_names;
	request = print_files(request, size.ws_col);
	print_rows(request->f_names, size.ws_col, flags);
}

t_dir	*print_files(t_dir *request, ushort ws_cols)
{
	t_dir			*files;
	t_dir			*dir;

	files = request;
	dir = request;
	request = sort_list_f_d(request);
	while (request)
	{
		if (!(*request).f_names && (*((*request).next)).f_names)
		{
			dir = (*request).next;
			(*request).next = NULL;
		}
		request = (*request).next;
	}
	if (files != dir)
	{
		print_cols(files, ws_cols, NULL);
		ft_putchar('\n');
	}
	return (dir);
}

void	print_all_rek(t_dir *request, ushort size, t_flags *flags)
{
	uint8_t	i;

	i = -1;
	while(request)
	{
		if ((++i != 0 || request->next) && request->f_names)
    	{
			if (i != 0)
				ft_putchar('\n');
			ft_putstr(request->path + 2);
			ft_putstr(":\n");
		}
		if (request->f_names)
		{
			if ((request->name)[0] != '.' || request->level == 1)
			{
				print_cols((*request).f_names, size, flags);
				if (flags && flags->r_big)
					print_all_rek(request->f_names, size, flags);
			}
		}
		request = request->next;
	}
}

t_prt_c                get_print_prm_c(t_dir *request, ushort ws_col, t_flags *flags)
{
	uint8_t	len;
	ushort	f_rows;
	ushort	r_rows;
    t_prt_c	pprm;

    pprm.max = 0;
    pprm.cnt_elems = 0;
    while (request)
    {
        len = ft_strlen((*request).name);
		if (len > pprm.max)
       		pprm.max = len;
    	pprm.cnt_elems++;
        request = (*request).next;
    }
    pprm.cols = pprm.cnt_elems;
    while((pprm.max + 2) * pprm.cols > ws_col)
        pprm.cols--;
    f_rows = pprm.cnt_elems / pprm.cols;
    r_rows = (pprm.cnt_elems % pprm.cols > 0) ? 1 : 0;
    pprm.rows = f_rows + r_rows;
    return (pprm);
}

void                print_cols(t_dir *request, ushort ws_col, t_flags *flags)
{
    t_prt_c           pprm;

    pprm = get_print_prm_c(request, ws_col, flags);
    pprm.cur_row = 0;
    while (++pprm.cur_row <= pprm.rows)
    {
        print_line(request, pprm, flags);
        request = (*request).next;
    }
}

void            print_elem(char *str, uint8_t max)
{
	uint8_t	str_len;
	
	str_len = ft_strlen(str);
    ft_putstr(str);
    while (++str_len <= max)
        ft_putchar(' ');
}

t_dir           *next_elem(t_dir *request, t_prt_c pprm)
{
    ushort	i;
    ushort	offset;

    i = 0;
    offset = (pprm.cur_col + ((pprm.rows - 1) * pprm.cols)
            <= pprm.cnt_elems) ? pprm.rows : pprm.rows - 1;
    while (++i <= offset && request)
        request = (*request).next;
    return (request);
}

void           print_line(t_dir  *request, t_prt_c pprm, t_flags *flags)
{
    pprm.cur_col = 0;
    while (++pprm.cur_col <= pprm.cols && request)
    {
       	print_elem((*request).name, pprm.max);
        if (pprm.cur_col == pprm.cols)
           ft_putchar('\n');
        else
            ft_putstr("  ");
        request = next_elem(request, pprm);
		if (!request && pprm.cur_col != pprm.cols)
				ft_putchar('\n');
    }
}