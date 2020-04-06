/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:58:41 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/13 16:29:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

double		defSort(t_file *a, t_file *b)
{
	return (ft_strcmp(a->file_name, b->file_name));
}

double		timeSort(t_file *a, t_file *b)
{
	return (b->time - a->time);
}

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

void	mergeSort(t_file **h, double (*f)(t_file *a, t_file *b))
{
	t_file	*head; 
	t_file	*a;
	t_file	*b; 

	head = *h;
	a = NULL;
	b = NULL;
	if ((head == NULL) || (head->next == NULL))
		return ;
	frontBackSplit(head, &a, &b); 
	mergeSort(&a, f);
	mergeSort(&b, f);
	*h = sortedMerge(a, b, f); 
}

t_file	*sortedMerge(t_file *a, t_file *b, double (*f)(t_file *a, t_file *b))
{
	t_file *result; 

	result = NULL;
	if (a == NULL) 
		return (b); 
	else if (b == NULL)
		return (a);
	if ((*f)(a, b) <= 0)
	{ 
		result = a;
		result->next = sortedMerge(a->next, b, f); 
	}
	else
	{
		result = b;
		result->next = sortedMerge(a, b->next, f);
	}
	return (result); 
}

void frontBackSplit(t_file *src, t_file **front, t_file **back)
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

double		defSortDir(t_dir *a, t_dir *b)
{
	return (ft_strcmp(a->name, b->name));
}

void	mergeSortDir(t_dir **h, double (*f)(t_dir *a, t_dir *b))
{
	t_dir	*head; 
	t_dir	*a;
	t_dir	*b; 

	head = *h;
	a = NULL;
	b = NULL;
	if ((head == NULL) || (head->next == NULL))
		return ;
	frontBackSplitDir(head, &a, &b); 
	mergeSortDir(&a, f);
	mergeSortDir(&b, f);
	*h = sortedMergeDir(a, b, f); 
}

t_dir	*sortedMergeDir(t_dir *a, t_dir *b, double (*f)(t_dir *a, t_dir *b))
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
		result->next = sortedMergeDir(a->next, b, f); 
	}
	else
	{
		result = b;
		result->next = sortedMergeDir(a, b->next, f);
	}
	return (result); 
}

void frontBackSplitDir(t_dir *src, t_dir **front, t_dir **back)
{
	t_dir	*fast; 
	t_dir	*slow; 

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