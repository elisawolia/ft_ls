/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/07/11 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	merge_sort_dir(t_dir **h, double (*f)(t_dir *a, t_dir *b), int flag)
{
	t_dir	*head;
	t_dir	*a;
	t_dir	*b;

	head = *h;
	a = NULL;
	b = NULL;
	if ((head == NULL) || (flag && head->next == NULL)
		|| (!flag && head->mult == NULL))
		return ;
	front_back_split_dir(head, &a, &b, flag);
	merge_sort_dir(&a, f, flag);
	merge_sort_dir(&b, f, flag);
	*h = sorted_merge_dir(a, b, f, flag);
}

t_dir	*sorted_merge_dir(t_dir *a, t_dir *b,
					double (*f)(t_dir *a, t_dir *b), int flag)
{
	t_dir *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((*f)(a, b) <= 0)
	{
		result = a;
		if (flag)
			result->next = sorted_merge_dir(a->next, b, f, flag);
		else
			result->mult = sorted_merge_dir(a->mult, b, f, flag);
	}
	else
	{
		result = b;
		if (flag)
			result->next = sorted_merge_dir(a, b->next, f, flag);
		else
			result->mult = sorted_merge_dir(a, b->mult, f, flag);
	}
	return (result);
}

void	front_back_split_dir_help(t_dir **fast, t_dir **slow, int flag)
{
	while (*fast != NULL)
	{
		if (flag)
		{
			*fast = (*fast)->next;
			if (*fast != NULL)
			{
				*slow = (*slow)->next;
				*fast = (*fast)->next;
			}
		}
		else
		{
			*fast = (*fast)->mult;
			if (*fast != NULL)
			{
				*slow = (*slow)->mult;
				*fast = (*fast)->mult;
			}
		}
	}
}

void	front_back_split_dir(t_dir *src, t_dir **front, t_dir **back, int flag)
{
	t_dir	*fast;
	t_dir	*slow;

	slow = src;
	fast = NULL;
	if (flag)
		fast = src->next;
	else
		fast = src->mult;
	front_back_split_dir_help(&fast, &slow, flag);
	*front = src;
	if (flag)
	{
		*back = slow->next;
		slow->next = NULL;
	}
	else
	{
		*back = slow->mult;
		slow->mult = NULL;
	}
}

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
