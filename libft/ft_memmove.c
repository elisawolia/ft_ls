/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:45:39 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/14 15:59:53 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned	i;
	char		*d;
	char		*s;

	d = (char*)dst;
	s = (char*)src;
	i = 0;
	if (len == 0)
		return (dst);
	if (src > dst)
		return (ft_memcpy(dst, src, len));
	else if (src < dst)
	{
		i = len - 1;
		while (i > 0)
		{
			d[i] = s[i];
			i--;
		}
		d[i] = s[i];
	}
	dst = d;
	return (dst);
}
