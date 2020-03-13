/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:37:15 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/17 18:09:38 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*so;
	unsigned char	*st;
	unsigned		i;

	i = 0;
	so = (unsigned char*)s1;
	st = (unsigned char*)s2;
	if (n == 0)
		return (0);
	while (so[i] == st[i] && i < n - 1)
		i++;
	return (so[i] - st[i]);
}
