/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 17:49:28 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/19 15:08:25 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_clear(char **buf, int w)
{
	while (w >= 0)
	{
		ft_strdel(&buf[w]);
		w--;
	}
	free(*buf);
	return (0);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t		w;
	char		**buf;
	unsigned	i;

	i = 0;
	if ((s == NULL) ||
		!(buf = (char **)malloc(sizeof(char*) * ft_cwords((char*)s, c))))
		return (NULL);
	w = 0;
	while (s[i] != '\0')
	{
		if (USLOVIE1 || USLOVIE2)
		{
			while (s[i] == c)
				i++;
			if (!(buf[w] = (char*)malloc(sizeof(char) * ft_l((char*)s, c, i))))
				if (!ft_clear(buf, w))
					return (NULL);
			buf[w] = ft_putw(s, buf[w], c, i);
			w++;
		}
		i++;
	}
	buf[w] = NULL;
	return (buf);
}
