/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:54:47 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/18 14:08:46 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && i < n - 1 && s2[i])
		i++;
	if (n < 1)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
