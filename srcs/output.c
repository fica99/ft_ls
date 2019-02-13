

#include <ft_ls.h>

void                print(t_dir *request)
{
    struct winsize  size;
    t_flags         *flags;

    if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
        printf("TIOCGWINSZ error");
    flags = (*request).flags;
    request = (*request).f_names;
    print_cols((*request).f_names, size.ws_col);

}

t_prt                get_print_prm(t_dir *request, int ws_col)
{
    int             len;
    int             f_rows;
    int             r_rows;
    t_prt           pprm;

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
    while(pprm.max * pprm.cols + (pprm.cols * 2) > ws_col)
        pprm.cols /= 2;
    f_rows = pprm.cnt_elems / pprm.cols;
    r_rows = (pprm.cnt_elems - f_rows * pprm.cols > 0) ? 1 : 0;
    pprm.rows = f_rows + r_rows;
    return (pprm);
}

void                print_cols(t_dir *request, int ws_col)
{
    t_prt           pprm;

    pprm = get_print_prm(request, ws_col);
    pprm.cur_row = 0;
    while (++pprm.cur_row <= pprm.rows)
    {
        print_line(request, pprm);
        request = (*request).next;
    }
}

void            print_elem(char *str, t_prt pprm)
{
    int         str_len;

    str_len = ft_strlen(str);
    ft_putstr(str);
    while (++str_len <= pprm.max)
        ft_putchar(' ');
}

t_dir           *next_elem(t_dir *request, t_prt pprm)
{
    int         i;
    int         offset;

    i = -1;
    offset = (pprm.cur_col + ((pprm.rows - 1) * pprm.cols)
            <= pprm.cnt_elems) ? pprm.rows : pprm.rows - 1;
    while (++i < offset && request)
        request = (*request).next;
    return (request);
}

void           print_line(t_dir  *request, t_prt pprm)
{
    pprm.cur_col = 0;
    while (++pprm.cur_col <= pprm.cols && request)
    {
        print_elem((*request).name, pprm);
        if (pprm.cur_col == pprm.cols || !request)
            ft_putchar('\n');
        else
            ft_putstr("  ");
        request = next_elem(request, pprm);
    }
}