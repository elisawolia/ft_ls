/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 13:48:35 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/07 14:26:33 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *hayst, const char *need)
{
	char		*str;
	unsigned	i;
	unsigned	j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char *) * ft_strlen(hayst));
	if (str == NULL)
		return (str);
	str = (char *)hayst;
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == need[j] && need[j] != '\0')
			j++;
		if (need[j] == '\0' && j != 0)
			return (&str[i]);
		i++;
	}
	if (need[0] == '\0')
		return (&str[0]);
	return (NULL);
}
