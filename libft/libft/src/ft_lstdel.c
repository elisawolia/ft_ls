/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:49:14 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/17 15:54:45 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (alst == NULL || del == NULL)
		return ;
	(*del)((*alst)->content, (*alst)->content_size);
	if ((*alst)->next != NULL)
		ft_lstdel(&(*alst)->next, (*del));
	free(*alst);
	*alst = NULL;
}
