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
	frontback_split_dir(head, &a, &b, flag);
	merge_sort_dir(&a, f, flag);
	merge_sort_dir(&b, f, flag);
	*h = sm_dir(a, b, f, flag);
}

t_dir	*sm_dir(t_dir *a, t_dir *b,
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
			result->next = sm_dir(a->next, b, f, flag);
		else
			result->mult = sm_dir(a->mult, b, f, flag);
	}
	else
	{
		result = b;
		if (flag)
			result->next = sm_dir(a, b->next, f, flag);
		else
			result->mult = sm_dir(a, b->mult, f, flag);
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

void	frontback_split_dir(t_dir *src, t_dir **front, t_dir **back, int flag)
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
