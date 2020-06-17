/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 11:00:42 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/08 12:39:10 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned	l1;
	unsigned	l2;
	unsigned	i;
	unsigned	j;
	long		s;

	l1 = ft_strlen(dst);
	l2 = ft_strlen(src);
	i = 0;
	j = 0;
	s = size - l1;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && j < s - 1)
	{
		dst[i + j] = (char)src[j];
		j++;
	}
	dst[i + j] = '\0';
	if (s < 0)
		return (l2 + size);
	return (l1 + l2);
}
