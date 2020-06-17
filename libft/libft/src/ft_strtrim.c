/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:14:44 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/18 13:48:17 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	unsigned	i;
	char		*buf;
	unsigned	j;
	unsigned	l;
	unsigned	dif;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	l = ft_strlen(s);
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
				|| s[i] == '\0') && i < l)
		i++;
	while ((s[l] == ' ' || s[l] == '\t' || s[l] == '\n'
				|| s[l] == '\0') && l > i)
		l--;
	dif = l - i;
	if (!(buf = ft_memalloc(sizeof(char const) * (dif + 2))))
		return (NULL);
	while (i <= l)
		buf[j++] = s[i++];
	buf[j] = '\0';
	return (buf);
}
