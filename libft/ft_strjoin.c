/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:08:21 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/16 16:25:34 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*buf;
	unsigned	i;
	unsigned	j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	buf = (char *)malloc(sizeof(char*) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (buf == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		buf[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		buf[i] = s2[j];
		i++;
		j++;
	}
	buf[i] = '\0';
	return (buf);
}
