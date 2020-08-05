/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/07/23 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	sorting_dir_r(t_dir *dir, t_opt **opt)
{
	merge_sort_dir(&(dir->sub), &def_sort_dir, 1);
	merge_sort_dir(&(dir->next), &def_sort_dir, 1);
	if ((*opt)->t)
	{
		merge_sort_dir(&(dir->sub), &time_sort_dir, 1);
		merge_sort_dir(&(dir->next), &time_sort_dir, 1);
	}
	if ((*opt)->s)
	{
		merge_sort_dir(&(dir->sub), &size_sort_dir, 1);
		merge_sort_dir(&(dir->next), &size_sort_dir, 1);
	}
	if ((*opt)->r)
	{
		reverse_dir_next(&(dir->sub));
		reverse_dir_next(&(dir->next));
		reverse_dir_sub(&(dir->sub));
		reverse_dir_sub(&(dir->next));
	}
}

void		print_r(t_dir *dir, t_opt **opt, int num_mult)
{
	if ((*opt)->r_output == 1 || num_mult > 1)
	{
		if ((*opt)->r_output == 1)
			ft_putchar('\n');
		if (dir->file_added == 0)
			ft_printf("%s:\n", dir->name);
	}
	(*opt)->r_output = 1;
	if ((*opt)->l == 1)
	{
		if (dir->files != NULL)
			ft_printf("total %lld\n", dir->total);
		print_list_l(dir, (*opt)->g);
	}
	else if ((*opt)->one == 1)
		print_one(dir, (*opt)->g);
	else
		print_list(dir, (*opt)->g);
	sorting_dir_r(dir, opt);
	if (dir->sub)
		read_dir(dir->sub->name, opt, dir->sub, 0);
	if (dir->next)
		read_dir(dir->next->name, opt, dir->next, 0);
}
