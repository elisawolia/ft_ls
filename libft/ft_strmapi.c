/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:08:38 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/16 17:33:37 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*buf;
	unsigned	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	buf = (char*)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (buf == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		buf[i] = (f)(i, s[i]);
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
