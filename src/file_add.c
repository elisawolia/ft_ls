/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		file_add(t_file **alst, t_file *new)
{
	if (new == NULL)
		return ;
	new->next = (*alst);
	(*alst) = new;
}

void		file_add_full(t_file **alst, t_file *new)
{
	t_file *new_start;

	if (new == NULL)
		return ;
	new_start = new;
	while (new->next != NULL)
		new = new->next;
	new->next = (*alst);
	(*alst) = new_start;
}
