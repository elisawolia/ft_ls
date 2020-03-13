/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:55:54 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/14 17:17:26 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*buf;
	unsigned char	*s;
	unsigned		i;

	i = 0;
	buf = (unsigned char*)dst;
	s = (unsigned char*)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		buf[i] = s[i];
		i++;
	}
	return (buf);
}
