/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:35:12 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/08 09:52:34 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int symb)
{
	int		i;
	char	*new;

	i = 0;
	new = (char *)str;
	while (*new != '\0' && *new != (char)symb)
		new++;
	if (*new == '\0' && *new != (char)symb)
		new = NULL;
	return (new);
}
