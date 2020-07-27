/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/07/23 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	printing(t_dir *direct, t_opt **opt)
{
	if ((*opt)->rec == 1)
		print_r(direct, opt);
	else if ((*opt)->l == 1)
	{
		if (!(*opt)->d)
			ft_printf("total %lld\n", direct->total);
		print_list_l(direct, (*opt)->g);
	}
	else if ((*opt)->one == 1)
		print_one(direct, (*opt)->g);
	else if ((*opt)->m == 1)
		print_m(direct, (*opt)->g);
	else
		print_list(direct, (*opt)->g);
}

/*
** col_width = ближайшей число кратное 8 (по табу)
*/

int		rows_print(t_dir *dir)
{
	int				col_width;
	int				files_count;
	struct winsize	w;
	int				numcols;
	int				numrows;

	files_count = count_files(dir->files);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	col_width = (dir->max_name + 8) & ~7;
	numcols = (w.ws_col / col_width > 0) ? w.ws_col / col_width : 1;
	numrows = files_count / numcols;
	if (files_count % numcols)
		++numrows;
	return (numrows);
}