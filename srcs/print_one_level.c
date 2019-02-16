#include "ft_ls.h"

t_prt                get_print_prm(t_dir *request, ushort ws_col)
{
	uint8_t	len;
	ushort	f_rows;
	ushort	r_rows;
    t_prt	pprm;

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
    while((pprm.max + 1) * pprm.cols > ws_col)
        pprm.cols--;
    f_rows = pprm.cnt_elems / pprm.cols;
    r_rows = (pprm.cnt_elems % pprm.cols > 0) ? 1 : 0;
    pprm.rows = f_rows + r_rows;
    return (pprm);
}

void                print_cols(t_dir *request, ushort ws_col, t_flags *flags)
{
    t_prt           pprm;

    flags = NULL;
    pprm = get_print_prm(request, ws_col);
    pprm.cur_row = 0;
    while (++pprm.cur_row <= pprm.rows)
    {
        print_line(request, pprm);
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

void           print_line(t_dir  *request, t_prt pprm)
{
    pprm.cur_col = 0;
    while (++pprm.cur_col <= pprm.cols && request)
    {
       	print_elem((*request).name, pprm.max);
        if (pprm.cur_col == pprm.cols)
           ft_putchar('\n');
        else
            ft_putchar(' ');
        request = next_elem(request, pprm);
		if (!request && pprm.cur_col != pprm.cols)
				ft_putchar('\n');
    }
}