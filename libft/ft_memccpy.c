/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 14:03:04 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/18 10:31:43 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src,
		int c, size_t n)
{
	unsigned char	*buf;
	unsigned char	*str;
	unsigned		i;

	i = 0;
	buf = (unsigned char*)dst;
	str = (unsigned char*)src;
	while (i < n)
	{
		buf[i] = str[i];
		if (str[i] == (unsigned char)c)
			return ((void*)&buf[i + 1]);
		i++;
	}
	return (NULL);
}
