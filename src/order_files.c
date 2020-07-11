/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reverse(t_file **lst)
{
	t_file	*head;
	t_file	*cur;
	t_file	*prev;
	t_file	*next;

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

void	merge_sort(t_file **h, double (*f)(t_file *a, t_file *b))
{
	t_file	*head;
	t_file	*a;
	t_file	*b;

	head = *h;
	a = NULL;
	b = NULL;
	if ((head == NULL) || (head->next == NULL))
		return ;
	front_back_split(head, &a, &b);
	merge_sort(&a, f);
	merge_sort(&b, f);
	*h = sorted_merge(a, b, f);
}

t_file	*sorted_merge(t_file *a, t_file *b, double (*f)(t_file *a, t_file *b))
{
	t_file	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((*f)(a, b) <= 0)
	{
		result = a;
		result->next = sorted_merge(a->next, b, f);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next, f);
	}
	return (result);
}

void	front_back_split(t_file *src, t_file **front, t_file **back)
{
	t_file	*fast;
	t_file	*slow;

	slow = src;
	fast = src->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = src;
	*back = slow->next;
	slow->next = NULL;
}
