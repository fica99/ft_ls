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

void	print(t_dir *request)
{
	struct winsize	size;
	t_flags			*flags;
	t_dir			*dir;

	if (!request || ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
		exit(-1);
	flags = (*request).flags;
	request = request->f_names;
	if (!(flags->d))
	{
		request = sort_list_f_d(request);
		dir = print_files(request, size.ws_col);
		if (dir != request)
			dir->files = 1;
	}
	else
		dir = request;	
	print_all_rek(dir, size.ws_col, ((*flags).l) ? print_rows : print_cols, flags);
}

t_dir	*print_files(t_dir *request, ushort size)
{
	t_dir	*files;
	t_dir	*dir;

	if (!request)
		return (NULL);;
	files = request;
	dir = request;
	while (request)
	{
		if (!request->f_names && request->next && (request->next)->f_names)
		{
			dir = request->next;
			request->next = NULL;
		}	
		request = request->next;
	}
	if (files != dir)
	{
		print_cols(files, size, NULL);
		ft_putchar('\n');
	}
	return (dir);
}

void	print_all_rek(t_dir *request, ushort size, void (f)(t_dir *, ushort, t_flags *), t_flags *flags)
{
	uint8_t	i;

	i = -1;
	while(request)
	{
		if (!flags->d)
		{
			if (request->f_names)
			{
				if (++i != 0 || request->files || request->next || request->level != 1)
    			{
					if (i != 0 || request->level != 1)
						ft_putchar('\n');
					ft_putstr(request->path + 2);
					ft_putstr(":\n");
				}
				f(request->f_names, size, flags);
				print_all_rek(request->f_names, size, f, flags);
			}
		}
		else
		{
			f(request, size, flags);
			exit (1);
		}		
		request = request->next;
	}
}

t_dir           *next_elem(t_dir *request, t_prt pprm)
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