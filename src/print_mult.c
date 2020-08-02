/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/07/23 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	printing_mult_dir_continue(t_dir **tmp, t_opt **opt)
{ 
	if ((*opt)->rec == 1)
		print_r(*tmp, opt);
	else if ((*opt)->l == 1)
	{
		if ((*tmp)->file_added == 0)
			ft_printf("total %lld\n", (*tmp)->total);
		print_list_l(*tmp, (*opt)->g);
	}
	else if ((*opt)->one == 1)
		print_one(*tmp, (*opt)->g);
	else if ((*opt)->m == 1)
		print_m(*tmp, (*opt)->g);
	else
		print_list(*tmp, (*opt)->g);
}

void		printing_mult_dir(t_dir *direct, int i, int argc, t_opt **opt)
{
	t_dir	*tmp;

	tmp = direct;
	while (tmp != NULL)
	{
		if ((*opt)->d)
		{
			print_d(*opt, tmp);
			break ;
		}
		if ((*opt)->rec == 0 && argc != i + 1 && tmp->file_added == 0)
			ft_printf("%s:\n", tmp->name);
		printing_mult_dir_continue(&tmp, opt);
		//  эта конструкция сеет хаус в вывод ошибок
		if (tmp->mult != NULL) 
			ft_putchar('\n');
		tmp = tmp->mult;
	}
}
