/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:33:48 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/17 17:56:46 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*buf;
	unsigned		i;

	i = 0;
	buf = (unsigned char*)s;
	while (i < n)
	{
		if (buf[i] == (unsigned char)c)
			return ((void*)&buf[i]);
		i++;
	}
	return (NULL);
}
