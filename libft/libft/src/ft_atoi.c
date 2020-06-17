/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 09:23:40 by rlintill          #+#    #+#             */
/*   Updated: 2019/09/18 11:56:20 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	sign(char **s, int *z)
{
	if (*(*s) == '-' || *(*s) == '+')
	{
		if (*(*s) == '-')
			*z = -1;
		(*s)++;
	}
}

int				ft_atoi(const char *str)
{
	unsigned long long	nb;
	int					z;
	char				*s;

	s = (char *)malloc(sizeof(char *) * ft_strlen(str) + 1);
	if (s == NULL)
		return (0);
	nb = 0;
	s = (char *)str;
	z = 1;
	while (*s == ' ' || *s == '\t' || *s == '\n' ||
			*s == '\v' || *s == '\f' || *s == '\r')
		s++;
	sign(&s, &z);
	while (*s >= '0' && *s <= '9')
	{
		nb = nb * 10 + (*s - '0');
		s++;
	}
	if (nb >= 9223372036854775807)
		return (z == -1 ? 0 : -1);
	return (nb * z);
}
