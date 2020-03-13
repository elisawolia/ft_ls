/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:30:59 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/16 16:36:46 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*buf;
	unsigned	i;
	unsigned	j;

	j = 0;
	i = start;
	if (s == NULL)
		return (NULL);
	buf = (char*)malloc(sizeof(char) * len + 1);
	if (buf == NULL)
		return (NULL);
	while (j < len)
	{
		buf[j] = s[i];
		j++;
		i++;
	}
	buf[j] = '\0';
	return (buf);
}
