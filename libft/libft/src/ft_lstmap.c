/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:05:20 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/18 10:52:55 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*list;

	if (lst == NULL || f == NULL)
		return (NULL);
	list = (t_list*)malloc(sizeof(lst));
	if (list == NULL)
	{
		free(list);
		return (NULL);
	}
	list = (f)(lst);
	if (lst->next)
		list->next = ft_lstmap(lst->next, f);
	else
		list->next = NULL;
	return (list);
}
