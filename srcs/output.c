

#include <ft_ls.h>

void                print(t_dir *request)
{
    struct winsize  size;

    if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
        printf("TIOCGWINSZ error");
    request = (*request).f_names;
    request = (*request).f_names;
    print_lvl(request, size.ws_col);

}

t_prt                get_print_prm(t_dir *request)
{
    int             len;
    t_prt           print_prm;

    print_prm.max = 0;
    print_prm.count = 0;
    while (request)
    {
        len = ft_strlen((*request).name);
        if (len > print_prm.max)
            print_prm.max = len;
        print_prm.count++;
        request = (*request).next;
    }
    return (print_prm);
}

void                print_lvl(t_dir *request, int col_len)
{
    t_prt           print_prm;
    int             elems_brk;
    int             elem;
    int             elem_lost;

    print_prm = get_print_prm(request);
    elems_brk = print_prm.count;
    while(print_prm.max * elems_brk > col_len)
        elems_brk /= 2;
    elem = -1;
    elem_lost = 0;
    while (++elem < print_prm.count)
    {
        print_elem((*request).name, print_prm.max);
        elem_lost = print_end_elem(elem_lost, elems_brk);
        request = (*request).next;
    }
}

void            print_elem(char *str, int elem_size)
{
    int         i;
    int         str_len;

    i = -1;
    str_len = ft_strlen(str);
    while (++i < elem_size)
    {
        if (i < str_len)
            ft_putchar(str[i]);
        else
            ft_putchar(' ');
    }
}
int            print_end_elem(int elem_lost, int elems_brk)
{
    if (++elem_lost == elems_brk)
    {
        ft_putchar('\n');
        elem_lost = 0;
    }
    else
        ft_putchar(' ');
    return (elem_lost);
}