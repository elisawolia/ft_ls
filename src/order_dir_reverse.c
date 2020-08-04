/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_dir_reverse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 17:07:46 by rlintill          #+#    #+#             */
/*   Updated: 2020/07/25 17:08:04 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reverse_dir_next(t_dir **lst)
{
	t_dir	*head;
	t_dir	*cur;
	t_dir	*prev;
	t_dir	*next;

	prev = NULL;
	head = *lst;
	if (head == NULL || head->next == NULL)
		return ;
	cur = head;
	next = cur->next;
	while (cur != NULL)
	{
		cur->next = prev;
		prev = cur;
		cur = next;
		if (cur != NULL)
			next = cur->next;
	}
	*lst = prev;
}

void	reverse_dir_mult(t_dir **lst)
{
	t_dir	*head;
	t_dir	*cur;
	t_dir	*prev;
	t_dir	*next;

	prev = NULL;
	head = *lst;
	if (head == NULL || head->mult == NULL)
		return ;
	cur = head;
	next = cur->mult;
	while (cur != NULL)
	{
		cur->mult = prev;
		prev = cur;
		cur = next;
		if (cur != NULL)
			next = cur->mult;
	}
	*lst = prev;
}

void	reverse_dir_sub(t_dir **lst)
{
	t_dir	*head;
	t_dir	*cur;
	t_dir	*prev;
	t_dir	*next;

	prev = NULL;
	head = *lst;
	if (head == NULL || head->sub == NULL)
		return ;
	cur = head;
	next = cur->sub;
	while (cur != NULL)
	{
		cur->sub = prev;
		prev = cur;
		cur = next;
		if (cur != NULL)
			next = cur->sub;
	}
	*lst = prev;
}
