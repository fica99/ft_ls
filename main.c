/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:00:30 by aashara-          #+#    #+#             */
/*   Updated: 2019/01/22 13:00:32 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_dir	*request;
	t_flags	*flags;

	request = opening(argc, argv);
	flags = request->flags;
	if ((!(flags->t) && !(flags->r) && !(flags->u) && !(flags->f)
	&& !(flags->s_big)))
		request->f_names = sort_tree_list(request->f_names, sort_one_list);
	print(request);
	return (0);
}
