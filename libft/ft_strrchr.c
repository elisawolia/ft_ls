/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 13:10:45 by rlintill          #+#    #+#             */
/*   Updated: 2019/10/12 15:21:43 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char		*s;
	unsigned	i;

	i = ft_strlen(str);
	s = (char*)str;
	while (i != 0 && (char)c != s[i])
		i--;
	if (i == 0 && s[i] != (char)c)
		s = NULL;
	return (&s[i]);
}
