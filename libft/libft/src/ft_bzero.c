/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:47:22 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/08 13:54:30 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned		i;
	unsigned char	*buf;

	buf = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		buf[i] = 0;
		i++;
	}
}
