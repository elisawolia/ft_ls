/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:29:13 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/07 14:33:36 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hayst, const char *need, size_t l)
{
	char		*str;
	unsigned	i;
	unsigned	j;

	i = 0;
	j = 0;
	if (!(str = (char *)malloc(sizeof(char *) * ft_strlen(hayst))))
		return (str);
	str = (char *)hayst;
	while (str[i] != '\0' && i < l)
	{
		j = 0;
		while (str[i + j] == need[j] && need[j] != '\0' && i + j < l)
			j++;
		if (need[j] == '\0' && j != 0)
			return (&str[i]);
		i++;
	}
	if (need[0] == '\0')
		return (&str[0]);
	return (NULL);
}
