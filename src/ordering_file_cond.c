/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ordering_file_cond.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

double	def_sort(t_file *a, t_file *b)
{
	return (ft_strcmp(a->file_name, b->file_name));
}

double	time_sort(t_file *a, t_file *b)
{
	return (b->time - a->time);
}

double	time_sort_sec(t_file *a, t_file *b)
{
	return ((double)(b->sec - a->sec));
}

double	time_sort_nsec(t_file *a, t_file *b)
{
	return ((double)(b->nsec - a->nsec));
}

double	size_sort(t_file *a, t_file *b)
{
	return ((double)(b->size - a->size));
}
