/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:09:36 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/07 18:45:13 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *str, size_t len)
{
	unsigned	i;
	unsigned	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (str[j] != '\0' && j < len)
	{
		dest[i + j] = str[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
