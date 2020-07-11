/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ordering_dir_cond.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/07/11 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

double	def_sort_dir(t_dir *a, t_dir *b)
{
	return (ft_strcmp(a->name, b->name));
}

double	time_sort_dir(t_dir *a, t_dir *b)
{
	return (b->time - a->time);
}

double	size_sort_dir(t_dir *a, t_dir *b)
{
	return ((double)(b->size - a->size));
}
